/**
 * @file main.c
 * @brief Прога для комфортного кача с YouTube
 */

#include "config.h" // Константы
#include "cfg.h"    // Для getTermOpts(), loadIni(), options, config
#include "fs.h"     // Для initDirs()
#include "user.h"   // Для menu(), getUrl(), help()
#include "yt_dlp.h" // Для yt_dlp()

#include <stdio.h>  // Debug

/**
 * @brief Точка входа в программу
 *
 * @param argc Число параметров командной строки
 * @param argv Массив указателей на строки с параметрами
 *
 * @return Числовые коды ошибок или 0 при успехе
 */
int main(int argc, char* argv[]) {
  char  mode; // Режим работы
  char* url;  // Указатель на URL

  // Получаем опции из параметров командной строки
  getTermOpts(argc, argv);

  // Загружаем ini конфиг в структуру
  if (options.config) loadIni(options.config);
  else                loadIni(INI_CFG);

  initDirs(); // Создаем директории, если надо

  // Доспрашиваем необходимое
  if (options.bug) {
    help(); // Юзер ошибся с опциями
    return ERR_OPTS; // Критический выход
  }
  if (options.mode == 'h') {
    help(); // Юзер хочет хэлп
    return 0; // Просто выход
  }
  if (!options.mode) mode = menu(); // Юзер не указал режим, спрашиваем
  else mode = options.mode;
  if (!options.url) url = getUrl(); // Юзер не указал URL, спрашиваем
  else url = options.url;

  yt_dlp(url, mode); // Работаем
  return 0;          // Profit!
}

