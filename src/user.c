#include "user.h"

Options getTermOpts(int argc, char *argv[]) {
  // Пустая таблица опций (настройки по умолчаню)
  Options opts = {false, 0, NULL};

  // Короткие опции
  static const char* shOpts = "12345h";

  // Длинные опции
  static const struct option lOpts[] = {
    {"help", no_argument, 0, 'h'},
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
      case '1': opts.mode = opt; oEnabl++; break;
      case '2': opts.mode = opt; oEnabl++; break;
      case '3': opts.mode = opt; oEnabl++; break;
      case '4': opts.mode = opt; oEnabl++; break;
      case '5': opts.mode = opt; oEnabl++; break;
      case 'h': opts.mode = opt; oEnabl++; break;
      default: opts.bug = true;
    }
  }

  // Все опции режимные, их может быть не больше одной штуки
  if (oEnabl > 1) opts.bug = true;

  // Проверяем, есть ли неопционный аргумент (URL)
  if (optind < argc) opts.url = argv[optind];

  return opts;
}

void menu(char* mode) {
  char* text = "Что скачать?\n"
               "(1) Видео\n"
               "(2) Аудио\n"
               "(3) Плейлист видео\n"
               "(4) Плейлист аудио\n"
               "(5) Дмитрия Рея\n"
               "Выбери (1-5): ";

  // Цикл меню (бесконечный)
  char choice;
  while (1) {
    printf("%s", text);
    choice = getchar(); // Читаем один символ с stdin
    getchar(); // Пропускаем символ \n от кнопки Enter

    // Проверяем юзера
    if (choice >= '1' && choice <= '5') break; // Умный юзер покидает цикл
    else printf("Неверный выбор\n"); // Глупый юзер уходит на следуюший круг
  }

  *mode = choice;
}

void getUrl(char* url) {
  char newUrl[BUF_LEN]; // Память под url
  // Запрашиваем URL (так же упорно)
  while (1) {
    printf("Вставь ссылку: ");
    // Читаем из stdin не больше нашего буффера
    if (fgets(newUrl, BUF_LEN, stdin)) { // Если не NULL, то успешно
      newUrl[strcspn(newUrl, "\n")] = '\0'; // Отбрасываем \n
      strcpy(url, newUrl); // Сохраняем
      return; // Покидаем цикл
    }
  }
}

void help() {
  // Компиллятор C11 и выше умеет склеивать подряд идущие через пробел строковые константы
  char* text = "y2d [-1] [-2] [-3] [-4] [-5] [-h|--help] [url]\n"
               "y2d можно выполнить в одном из режимов:\n"
               "-1 - закачка видео\n"
               "-2 - закачка аудио\n"
               "-3 - закачка видеоплейлиста\n"
               "-4 - закачка аудиоплейлиста\n"
               "-5 - докачка Дмитрия Рея\n"
               "-h | --help - этот хэлп\n"
               "Если режим не указан, то программа его интерактивно спросит\n"
               "\n"
               "url - тоже необязательный параметр с интерактивом\n";

  printf("%s", text);
}

