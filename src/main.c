/**
 * @file main.c
 * @brief Прога для комфортного кача с YouTube
 */

#include "fs.h"     // Для initDirs()
#include "user.h"   // Для menu(), getUrl()
#include "yt_dlp.h" // Для yt_dlp()

int main(int argc, char* argv[]) {
  initDirs(); // Создаем директории, если надо

  // Анализируем параметры, доспрашиваем необходимое
  char mode;
  char* url;
  if (argc == 3) { // Всё указано
    mode = argv[1][0];
    url  = argv[2];
  } 
  if (argc == 2) { // Не указан режим
    mode = menu(); // Главное меню
    url  = argv[1];
  }
  if (argc == 1) { // Ни чего не указано
    mode = menu();   // Главное меню
    url  = getUrl(); // Получение url
  }

  yt_dlp(url, mode); // Работаем
  return 0;          // Profit!
}

