#include "cfg.h"

// Выделяем память под конфиг из ini с глобальной видимостью
Config config;

static int analyser(
  void* mainConf,   const char* section,
  const char* name, const char* value
) {
  #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
  if        (MATCH("fs",     "dir_rights")) {
    config.fsDir_rights  = strtol(value, NULL, 8);
  } else if (MATCH("fs",     "video_dir")) {
    config.fsVideo_dir   = strdup(value);
  } else if (MATCH("fs",     "audio_dir")) {
    config.fsAudio_dir   = strdup(value);
  } else if (MATCH("fs",     "dray_dir")) {
    config.fsDray_dir    = strdup(value);
  } else if (MATCH("fs",     "dray_log")) {
    config.fsDray_log    = strdup(value);
  } else if (MATCH("fs",     "cookie_path")) {
    config.fsCookie_path = strdup(value);
  } else if (MATCH("yt-dlp", "ytids")) {
    config.ytYtids       = strdup(value);
  } else if (MATCH("yt-dlp", "ytcmd")) {
    config.ytYtcmd       = strdup(value);
  } else if (MATCH("yt-dlp", "mode1")) {
    config.ytMode1       = strdup(value);
  } else if (MATCH("yt-dlp", "mode2")) {
    config.ytMode2       = strdup(value);
  } else if (MATCH("yt-dlp", "modep")) {
    config.ytModep       = strdup(value);
  } else if (MATCH("yt-dlp", "fname")) {
    config.ytFname       = strdup(value);
  } else if (MATCH("yt-dlp", "pname")) {
    config.ytPname       = strdup(value);
  } else if (MATCH("yt-dlp", "retr")) {
    config.ytRetr        = atoi(value);
  } else {
    return 0; // Unknown section/name, error
  }
  return 1;
}

void loadIni() {
  if (ini_parse(INI_CFG, analyser, &config) < 0) {
    printf("Не могу загрузить '%s'\n", INI_CFG);
    exit(ERR_INI);
  }
}

