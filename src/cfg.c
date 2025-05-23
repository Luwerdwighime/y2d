#include "cfg.h"

// Выделяем память под опции из командной строки
// и обнуляем все показатели (настройки по умолчаню)
Options options = {false, NULL, 0, NULL};

void getTermOpts(int argc, char *argv[]) {
  // Короткие опции
  static const char* shOpts = "12345c:h";

  // Длинные опции
  static const struct option lOpts[] = {
    {"config", required_argument, 0, 'c'},
    {"help",   no_argument,       0, 'h'},
    {0, 0, 0, 0}
  };

  // Читаем опции поштучно
  int opt;
  int oEnabl = 0;
  while(true) {
    opt = getopt_long(argc, argv, shOpts, lOpts, NULL); // Анализим
    if (opt == -1) break; // Нет больше опций в строке

    // Разбираем ответы
    switch (opt) {
      case '1': options.mode = opt; oEnabl++; break;
      case '2': options.mode = opt; oEnabl++; break;
      case '3': options.mode = opt; oEnabl++; break;
      case '4': options.mode = opt; oEnabl++; break;
      case '5': options.mode = opt; oEnabl++; break;
      case 'c': options.config = optarg; break;
      case 'h': options.mode = opt; oEnabl++; break;
      default: options.bug = true;
    }
  }

  // Все опции режимные, их может быть не больше одной штуки
  if (oEnabl > 1) options.bug = true;

  // Проверяем, есть ли неопционный аргумент (URL)
  if (optind < argc) options.url = argv[optind];
}

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

void loadIni(char* file) {
  if (ini_parse(file, analyser, &config) < 0) {
    printf("Не могу загрузить '%s'\n", file);
    exit(ERR_INI);
  }
}

