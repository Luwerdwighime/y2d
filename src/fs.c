#include "fs.h"

void mkdir_p(char *path) {
  char* cmd = malloc(BUF_LEN); // Память под команду
  snprintf(cmd, BUF_LEN, "mkdir -p %s", path); // Собираем команду
  if (system(cmd)) { // Выполняем команду
    fprintf(stderr, "Ошибка создания папки: %s", path);
    exit(ERR_DIR); // Критический выход
  }
}

void initDirs() {
  mkdir_p(config.fsVideo_dir);
  mkdir_p(config.fsAudio_dir);
  mkdir_p(config.fsDray_dir);
}

char* drayLogPath() {
  char* path = malloc(BUF_LEN); // Память под путь
  snprintf(
    path, BUF_LEN, "%s/%s",
    config.fsDray_dir, config.fsDray_log
  );
  return path;
}

void log_video_id(char *video_id) {
  char* path = drayLogPath(); // Вычисление пути
  FILE *log = fopen(path, "a"); // Открываем лог
  free(path); // Освобождаем память
  if (!log) {
    perror("Ошибка открытия и создания лога Дмитрия Рея");
    exit(ERR_DRAYLOG); // Критический выход
  }

  fprintf(log, "%s\n", video_id); // Пишем
  fclose(log); // Закрываем лог
}

int is_video_downloaded(char *video_id) {
  char* path = drayLogPath(); // Вычисление пути
  FILE *log = fopen(path, "r"); // Открываем лог
  free(path); // Освобождаем память
  if (!log) return 0; // Лог не существует, считаем, что видео не скачано

  char line[BUF_LEN]; // Память под строчку из лога
  // Читаем в line построчечно, пока fgets() не вернёт EOF
  while (fgets(line, BUF_LEN, log)) {
    line[strcspn(line, "\n")] = '\0'; // Отбрасываем \n
    if (strcmp(line, video_id) == 0) { // Нашли!
      fclose(log); // Закрываем лог
      return 1; // Видео уже скачано
    }
  }

  fclose(log); // Закрываем лог
  return 0; // Ни чего не нашли
}
