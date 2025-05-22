/**
 * @file main.c
 * @brief Прога для комфортного кача с YouTube
 */

#include <string.h> // Для strcpy()
#include "config.h" // Константы
#include "cfg.h"    // Для loadIni()
#include "fs.h"     // Для initDirs()
#include "user.h"   // Для типа Options, getTermOpts(), menu(), getUrl(), help()
#include "yt_dlp.h" // Для yt_dlp()

#include <stdio.h>  // Debug

/**
 * @brief Точка входа в программу
 *
 * @param argc Число параметров командной строки
 * @param argv Массив с параметрами
 *
 * @return Числовые коды ошибок или 0 при успехе
 */
int main(int argc, char* argv[]) {
  
  loadIni(); // Загружаем ini конфиг в структуру
  // Временный код для дебага
  printf("Debug ini:\n"
    "dir_rights: %04o\n" "video_dir: %s\n"
    "audio_dir:  %s\n"   "dray_dir:  %s\n"
    "dray_log: %s\n"     "cookie_path: %s\n"
    "ytids: %s\n"        "ytcmd: %s\n"
    "mode1: %s\n"        "mode2: %s\n"
    "modep: %s\n"        "fname: %s\n"
    "pname: %s\n"        "retr: %i\n",
    config.fsDir_rights, config.fsVideo_dir,
    config.fsAudio_dir,  config.fsDray_dir,
    config.fsDray_log,   config.fsCookie_path,
    config.ytYtids,      config.ytYtcmd,
    config.ytMode1,      config.ytMode2,
    config.ytModep,      config.ytFname,
    config.ytPname,      config.ytRetr
  );

//  initDirs(); // Создаем директории, если надо

  // Анализируем параметры, доспрашиваем необходимое
  char mode; // Режим работы
  char url[BUF_LEN]; // Память под URL
  Options opts = getTermOpts(argc, argv); // Получаем опции из параметров командной строки
  if (opts.bug) { // Юзер ошибся с опциями
    help();
    return ERR_OPTS; // Критический выход
  }
  if (opts.mode == 'h') { // Юзер хочет хэлп
    help();
    return 0; // Просто выход
  }
  if (!opts.mode) menu(&mode); // Юзер не указал режим, спрашиваем
  else mode = opts.mode;
  if (!opts.url) getUrl(url); // Юзер не указал URL, спрашиваем
  else strcpy(url, opts.url);

  printf("mode: '%c'\nurl: %s\n", mode, url);
 // yt_dlp(url, mode); // Работаем
  return 0;          // Profit!
}

