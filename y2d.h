#ifndef Y2D_H
#define Y2D_H

#include <stdio.h>
#include <stdlib.h>

// Directory paths
#define VIDEO_DIR "/storage/emulated/0/Documents/tmp/video"
#define AUDIO_DIR "/storage/emulated/0/Documents/tmp/audio"
#define DRAY_DIR "/storage/emulated/0/Documents/usr/luwerdwighime/abok"
#define MAX_LEN 2048
#define COOKIE_PATH "/data/data/com.termux/files/home/cookies_y2d.txt"

// Function declarations
void mkdir_p(const char *path);
void log_error(const char *url, const char *error);
void run_yt_dlp(const char *url, const char *opts, const char *out_dir, const char *out_tmpl);
int is_video_downloaded(const char *video_id);
void log_video_id(const char *video_id);
void process_playlist_ids(const char *url, const char *base_opts, const char *out_dir, const char *out_tmpl);

#endif // Y2D_H
