cmake_minimum_required(VERSION 3.10)
project(y2d LANGUAGES C)

set(H_FILES
  src/config.h
  src/fs.h
  src/user.h
  src/yt_dlp.h
)
set(C_FILES
  src/main.c
  src/fs.c
  src/user.c
  src/yt_dlp.c
)
add_executable(y2d ${H_FILES} ${C_FILES})

