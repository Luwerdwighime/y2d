project(y2d LANGUAGES C)

set(H_FILES
  src/fs.h
  src/user.h
  src/yt-dlp.h
)
set(C_FILES
  src/fs.c
  src/user.c
  src/yt-dlp.c
  src/main.c
)
add_executable(y2d ${H_FILES} ${C_FILES})

