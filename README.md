<div align="center">
  <img width=200 height=200 src="assets/ayumi.png" />
  <br />
  Lively Wallpapers made with SDL2 and FFmpeg
  <hr />
</div>
To run this software, you need the dynamic link libraries (DLLs) for FFmpeg and SDL2. Make sure to have these DLLs available in the system before executing the program.

# Execution

When running the program from the console, it is necessary to provide a specific argument to indicate the path of the file that will be used as wallpaper. Use the following format:
```
./Lively.exe --path file_path
```
Replace `file_path` with the full path to the file you want to use as wallpaper.

# Required DLLs

- **SDL2.dll**
  - **SDL2** is a cross-platform development library designed to provide low-level access to audio, keyboard, mouse, and display functions.

- **avcodec-xx.dll**
  - Part of the FFmpeg library, **avcodec** handles audio and video encoding and decoding.

- **avformat-xx.dll**
  - Another component of the FFmpeg library, **avformat** deals with multimedia container formats.

- **avutil-xx.dll**
  - The **avutil** DLL is part of FFmpeg and provides various utility functions used by other components of the library. It includes helper functions for common tasks in multimedia processing.