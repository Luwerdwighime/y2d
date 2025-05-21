/**
 * @file main.c
 * @brief Прога для комфортного кача с YouTube
 */

#include <stdio.h>  // Для printf()
#include <string.h> // Для strcpy()
#include "config.h" // Конфигурация
#include "fs.h"     // Для initDirs()
#include "user.h"   // Для типа Options, getTermOpts(), menu(), getUrl(), help()
#include "yt_dlp.h" // Для yt_dlp()

/**
 * @brief Точка входа в программу
 *
 * @param argc Число параметров командной строки
 * @param argv Массив с параметрами
 *
 * @return Числовые коды ошибок или 0 при успехе
 */
int main(int argc, char* argv[]) {
  initDirs(); // Создаем директории, если надо

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

  yt_dlp(url, mode); // Работаем
  return 0;          // Profit!
}

