#include "user.h"

char menu() {
  // Цикл меню (бесконечный)
  while (1) {
    printf("Что скачать?\n");
    printf("(1) Видео\n");
    printf("(2) Аудио\n");
    printf("(3) Плейлист видео\n");
    printf("(4) Плейлист аудио\n");
    printf("(5) Дмитрия Рея\n");
    printf("Выбери (1-5): ");
    char choice = getchar(); // Читаем один символ с stdin
    getchar(); // Пропускаем символ \n от кнопки Enter

    // Проверяем юзера
    if (choice >= '1' && choice <= '5') return choice; // Умный юзер покидает цикл
    else printf("Неверный выбор\n"); // Глупый юзер уходит на следуюший круг
  }
}

char* getUrl() {
  // Запрашиваем URL (так же упорно)
  char url[BUF_LEN]; // Память под длинную строку
  while (1) {
    printf("Вставь ссылку: ");
    // Читаем из stdin не больше нашего буффера
    if (fgets(url, BUF_LEN, stdin)) return url; // Если не NULL, то успешно
  }
}

