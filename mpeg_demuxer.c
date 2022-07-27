#include <stdlib.h>
#include <stdio.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>

typedef struct {
    AVFormatContext *ctx;
    int video_index;
    AVBSFContext *bsf_ctx;
} DEMUXER_T;

int mp4toannexb(DEMUXER_T *demuxer, AVPacket *pkt)
{
    int ret;

    ret = av_bsf_send_packet(demuxer->bsf_ctx, pkt);
    if (ret < 0) {
        printf("bsf send packet failed, errno: %d \n", ret);
        return -1;
    }

    for(;;) {
        ret = av_bsf_receive_packet(demuxer->bsf_ctx, pkt);
        if (AVERROR_EOF == ret || AVERROR(EAGAIN) == ret) {
            return 0;
        }
        if (ret < 0) {
            printf("Could not receive packet, errno: %d \n", ret);
            return -1;
        }
    }
}

int create_filter(DEMUXER_T *demuxer) {
    int ret, codec_id = demuxer->ctx->streams[demuxer->video_index]->codecpar->codec_id;
    const AVBitStreamFilter *filter;

    switch (codec_id) {
    case AV_CODEC_ID_H264:
        filter = av_bsf_get_by_name("h264_mp4toannexb");
        break;
    case AV_CODEC_ID_HEVC:
        filter = av_bsf_get_by_name("hevc_mp4toannexb");
        break;
    default:
        printf("Unspport Codec id: %d \n", codec_id);
        return -1;
    }

    if (NULL == filter) {
        printf("Could not create filter \n");
        return -1;
    }

    ret = av_bsf_alloc(filter, &demuxer->bsf_ctx);
    if (ret < 0) {
        printf("Could not alloc bitstream filter \n");
        return -1;
    }

    // avcodec_parameters_from_context
    ret = avcodec_parameters_copy(demuxer->bsf_ctx->par_in, demuxer->ctx->streams[demuxer->video_index]->codecpar);
    if (ret < 0) {
        printf("Parameter copy filed, errno: %d \n", ret);
        goto L_ERR_PARAMETERS_COPY;
    }

    ret = av_bsf_init(demuxer->bsf_ctx);
    if (ret < 0) {
        printf("BSF init failed, errno: %d \n", ret);
        goto L_ERR_BSF_INIT;
    }

    return 0;

L_ERR_BSF_INIT:
L_ERR_PARAMETERS_COPY:
    av_bsf_free(&demuxer->bsf_ctx);
    return ret;
}

void destroy_filter(DEMUXER_T *demuxer)
{
    av_bsf_free(&demuxer->bsf_ctx);
}

int main(int argc, const char* argv[])
{
    const char* file_name_in = argv[1];
    const char* file_name_out = argv[2];
    DEMUXER_T demuxer = {0};
    int ret;

    ret = avformat_open_input(&demuxer.ctx, file_name_in, NULL, NULL);
    if (ret < 0) {
        printf("Can nt open input file: %s \n", file_name_in);
        goto L_ERR_OPEN_INPUT;
    }

    ret = avformat_find_stream_info(demuxer.ctx, NULL);
    if (ret > 0) {
        printf("Can not fine stream info. \n");
        goto L_ERR_FIND_STREAM_INFO;
    }

    demuxer.video_index = av_find_best_stream(demuxer.ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    av_dump_format(demuxer.ctx, demuxer.video_index, file_name_in, 0);

    // printf("Video info, iformat: %s, codec: %u, w: %d, h: %d, bps: %ld, nb_frames: %ld\n",
    //          demuxer.ctx->iformat->name,
    //          demuxer.ctx->streams[video_stream_index]->codecpar->codec_id,
    //          demuxer.ctx->streams[video_stream_index]->codecpar->width,
    //          demuxer.ctx->streams[video_stream_index]->codecpar->height,
    //          demuxer.ctx->streams[video_stream_index]->codecpar->bit_rate,
    //          demuxer.ctx->streams[video_stream_index]->nb_frames);

    ret = create_filter(&demuxer);
    if (ret < 0) {
        printf("create filter failed.\n");
        goto L_ERR_CREATE_FILTER;
    }
    AVPacket *pkt = av_packet_alloc();
    FILE *fp_out = fopen(file_name_out, "w");

    for (;;) {
        ret = av_read_frame(demuxer.ctx, pkt);
        if (AVERROR_EOF == ret) {
            printf("\nEnd of pipe \n");
            break;
        } else if (ret < 0) {
            printf("\nread frame, errno: %d \n", ret);
            break;
        }
        printf("%d", pkt->stream_index);

        if (pkt->stream_index != demuxer.video_index) {
            continue;
        }
        mp4toannexb(&demuxer, pkt);

        fwrite(pkt->data, pkt->size, 1, fp_out);
        av_packet_unref(pkt);
    }
    printf("Done. \n");
    printf("Output file: %s \n", file_name_out);
    fflush(fp_out);
    fclose(fp_out);
    av_packet_free(&pkt);
    destroy_filter(&demuxer);

L_ERR_CREATE_FILTER:
L_ERR_ALLOC_OUTPUT_CONTEXT:
L_ERR_FIND_STREAM_INFO:
    avformat_close_input(&demuxer.ctx);
L_ERR_OPEN_INPUT:
    return 0;
}
