# mpeg_demuxer
## system requirement
```bash
sudo apt install libavformat-dev
sudo apt install libavcodec-dev
```
## How to use
```bash
./mpeg_demuxer [inputfile] [outputfile]
```

```bash
$ ./mpeg_demuxer video-h265.mkv video-h265.mkv.h265
Input #0, matroska,webm, from 'video-h265.mkv':
  Metadata:
    ENCODER         : Lavf55.12.0
  Duration: 00:00:16.16, start: 0.099000, bitrate: 2619 kb/s
    Stream #0:0: Video: hevc (Main), yuv420p(tv, bt709), 1920x960 [SAR 1:1 DAR 2:1], 25 fps, 25 tbr, 1k tbn, 25 tbc (default)
    Stream #0:1(eng): Audio: aac (LC), 48000 Hz, stereo, fltp (default)
    Metadata:
      title           : Stereo
      LANGUAGE        : eng
00101111011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110110101101101101101101101101011011011011011011011010110110110110110110111
End of pipe
Done.
Output file: video-h265.mkv.h265

$
$ ffprobe video-h265.mkv
ffprobe version 4.2.7-0ubuntu0.1 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 9 (Ubuntu 9.4.0-1ubuntu1~20.04.1)
  configuration: --prefix=/usr --extra-version=0ubuntu0.1 --toolchain=hardened --libdir=/usr/lib/x86_64-linux-gnu --incdir=/usr/include/x86_64-linux-gnu --arch=amd64 --enable-gpl --disable-stripping --enable-avresample --disable-filter=resample --enable-avisynth --enable-gnutls --enable-ladspa --enable-libaom --enable-libass --enable-libbluray --enable-libbs2b --enable-libcaca --enable-libcdio --enable-libcodec2 --enable-libflite --enable-libfontconfig --enable-libfreetype --enable-libfribidi --enable-libgme --enable-libgsm --enable-libjack --enable-libmp3lame --enable-libmysofa --enable-libopenjpeg --enable-libopenmpt --enable-libopus --enable-libpulse --enable-librsvg --enable-librubberband --enable-libshine --enable-libsnappy --enable-libsoxr --enable-libspeex --enable-libssh --enable-libtheora --enable-libtwolame --enable-libvidstab --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libwebp --enable-libx265 --enable-libxml2 --enable-libxvid --enable-libzmq --enable-libzvbi --enable-lv2 --enable-omx --enable-openal --enable-opencl --enable-opengl --enable-sdl2 --enable-libdc1394 --enable-libdrm --enable-libiec61883 --enable-nvenc --enable-chromaprint --enable-frei0r --enable-libx264 --enable-shared
  libavutil      56. 31.100 / 56. 31.100
  libavcodec     58. 54.100 / 58. 54.100
  libavformat    58. 29.100 / 58. 29.100
  libavdevice    58.  8.100 / 58.  8.100
  libavfilter     7. 57.100 /  7. 57.100
  libavresample   4.  0.  0 /  4.  0.  0
  libswscale      5.  5.100 /  5.  5.100
  libswresample   3.  5.100 /  3.  5.100
  libpostproc    55.  5.100 / 55.  5.100
Input #0, matroska,webm, from 'video-h265.mkv':
  Metadata:
    ENCODER         : Lavf55.12.0
  Duration: 00:00:16.16, start: 0.099000, bitrate: 2619 kb/s
    Stream #0:0: Video: hevc (Main), yuv420p(tv, bt709), 1920x960 [SAR 1:1 DAR 2:1], 25 fps, 25 tbr, 1k tbn, 25 tbc (default)
    Stream #0:1(eng): Audio: aac (LC), 48000 Hz, stereo, fltp (default)
    Metadata:
      title           : Stereo
      LANGUAGE        : eng
$
$
$ ffprobe video-h265.mkv.h265
ffprobe version 4.2.7-0ubuntu0.1 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 9 (Ubuntu 9.4.0-1ubuntu1~20.04.1)
  configuration: --prefix=/usr --extra-version=0ubuntu0.1 --toolchain=hardened --libdir=/usr/lib/x86_64-linux-gnu --incdir=/usr/include/x86_64-linux-gnu --arch=amd64 --enable-gpl --disable-stripping --enable-avresample --disable-filter=resample --enable-avisynth --enable-gnutls --enable-ladspa --enable-libaom --enable-libass --enable-libbluray --enable-libbs2b --enable-libcaca --enable-libcdio --enable-libcodec2 --enable-libflite --enable-libfontconfig --enable-libfreetype --enable-libfribidi --enable-libgme --enable-libgsm --enable-libjack --enable-libmp3lame --enable-libmysofa --enable-libopenjpeg --enable-libopenmpt --enable-libopus --enable-libpulse --enable-librsvg --enable-librubberband --enable-libshine --enable-libsnappy --enable-libsoxr --enable-libspeex --enable-libssh --enable-libtheora --enable-libtwolame --enable-libvidstab --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libwebp --enable-libx265 --enable-libxml2 --enable-libxvid --enable-libzmq --enable-libzvbi --enable-lv2 --enable-omx --enable-openal --enable-opencl --enable-opengl --enable-sdl2 --enable-libdc1394 --enable-libdrm --enable-libiec61883 --enable-nvenc --enable-chromaprint --enable-frei0r --enable-libx264 --enable-shared
  libavutil      56. 31.100 / 56. 31.100
  libavcodec     58. 54.100 / 58. 54.100
  libavformat    58. 29.100 / 58. 29.100
  libavdevice    58.  8.100 / 58.  8.100
  libavfilter     7. 57.100 /  7. 57.100
  libavresample   4.  0.  0 /  4.  0.  0
  libswscale      5.  5.100 /  5.  5.100
  libswresample   3.  5.100 /  3.  5.100
  libpostproc    55.  5.100 / 55.  5.100
Input #0, hevc, from 'video-h265.mkv.h265':
  Duration: N/A, bitrate: N/A
    Stream #0:0: Video: hevc (Main), yuv420p(tv, bt709), 1920x960 [SAR 1:1 DAR 2:1], 25 fps, 25 tbr, 1200k tbn, 25 tbc


```