#include "fs.h"

void mkdir_p(char *path) {
  // Просим у ядра создать папку
  int err = mkdir(path, DIR_RIGHTS);

  // Анализируем ошибку, если err не 0, то ошибка не должна быть
  // "file exist", иначе это нормальное поведение
  if (err && errno != EEXIST) {
    perror("Ошибка создания директории: ");
    perror(path); // Покажем юзеру путь ошибки
    exit(1); // Критический выход, возвращаем 1
  }
}

void initDirs() {
  mkdir_p(VIDEO_DIR);
  mkdir_p(AUDIO_DIR);
  mkdir_p(DRAY_DIR);
}

char* drayLogPath() {
  char path[BUF_LEN];
  snprintf(path, BUF_LEN, "%s/%s", DRAY_DIR, DRAY_LOG);
  return path;
}

void log_video_id(char *video_id) {
  // Открываем лог
  FILE *log = fopen(drayLogPath(), "a");
  if (!log) {
    perror("Ошибка открытия и создания лога Дмитрия Рея");
    exit(2); // Критический выход, возвращаем 2
  }

  fprintf(log, "%s\n", video_id); // Пишем
  fclose(log); // Закрываем лог
}

int is_video_downloaded(char *video_id) {
  // Открываем лог
  FILE *log = fopen(drayLogPath(), "r");
  if (!log) return 0; // Лог не существует, считаем, что видео не скачано

  char line[BUF_LEN]; // Память под строчку из лога
  // Читаем в line построчечно, пока fgets() не вернёт EOF
  while (fgets(line, BUF_LEN, log)) {
    line[strcspn(line, "\n")] = '\0'; // Отбрасываем всё за первым \n включительно
    if (strcmp(line, video_id) == 0) { // Нашли!
      fclose(log); // Закрываем лог
      return 1; // Видео уже скачано
    }
  }

  fclose(log); // Закрываем лог
  return 0; // Ни чего не нашли
}
