# ffaudio

ffaudio is a audio encoder built on ffmpeg

## Build ffmpeg

First, make sure you have built the ffmpeg vendor libraries.

### Windows platform

1.Install Visual Studio 2019.

2.Install [<font color=blue>mysy2</font>](https://www.msys2.org/)

3.Install some dependencies

```
pacman -S make gcc diffutils mingw-w64-{i686,x86_64}-pkg-config mingw-w64-i686-nasm mingw-w64-i686-yasm
```

4.Rename msys64/usr/bin/link.exe to msys64/usr/bin/link.bak, to avoid conflict with MSVC's link.exe

5.Run "VS2019 x86 Native Tools Command Prompt" (Run "VS2019 x86_x64 Native Tools Command Prompt"
   for 64-bit.)

6.Go to the mingw installation directory and run, (usually located in C:\workspace\windows\msys64):

```
msys2_shell.cmd -mingw32 -use-full-path (-mingw64 for 64-bit)
```

7.Finally, go to the root directory of ffaudio project, run:

```
build_ffmpeg.sh
```
### macOS platforms

Go to the root directory of ffaudio project, run:

```
build_ffmpeg.sh
```

The script will generate ffmpeg libraries to `vendor/ffmpeg` directory.

## Build ffaudio

```
depsync
```

After ffmpeg libraries are built, you can open this project by CLion to build, or simply build it
with the cmake command-line tool.