#include "yt_dlp.h"

char* getOpts(char mode) {
  char opts[BUF_LEN];
  switch (mode) {
    case '1': return MODE1;
    case '2': return MODE2;
    case '3':
      snprintf(opts, BUF_LEN, "%s %s", MODE1, MODEP);
      return opts;
    case '4':
      snprintf(opts, BUF_LEN, "%s %s", MODE2, MODEP);
      return opts;
    case '5': return MODE2;
  }
}

void yt_dlp(char* url, char mode) {
  switch (mode) {
    case '1': run_yt_dlp(url, getOpts(mode), VIDEO_DIR, FNAME); return;
    case '2': run_yt_dlp(url, getOpts(mode), AUDIO_DIR, FNAME); return;
    case '3': run_yt_dlp(url, getOpts(mode), VIDEO_DIR, PNAME); return;
    case '4': run_yt_dlp(url, getOpts(mode), AUDIO_DIR, PNAME); return;
    case '5': process_playlist_ids(url); return;
  }
}

void run_yt_dlp(char *url, char *opts, char *out_dir, char *out_tmpl) {
  // Создаём команду
  char cmd[BUF_LEN];
  snprintf(cmd, BUF_LEN, YTCMD, opts, out_dir, out_tmpl, url);

  // Пробуем в цикле
  int retries = RETR;
  while (retries--) {
    if (system(cmd) == 0) {
      printf("Готово, файлы в %s\n", out_dir);
      return;
    }
    // TODO: fprintf() в stderr?
    printf("Ошибка скачивания, повтор через 10 секунд. Попыток осталось: %d\n", retries);
    sleep(10);
  }
  // TODO: fprintf() в stderr?
  printf("Не удалось скачать после %d попыток url: %s\n", RETR, url);
}

void process_playlist_ids(char *url) {
  // Создаём команду
  char cmd[BUF_LEN];
  snprintf(cmd, BUF_LEN, YTIDS, url);

  // Запускаем команду и читаем её stdout построчечно
  FILE *fp = popen(cmd, "r");
  if (!fp) {
    perror("Ошибка получения ID видео");
    exit(3); // Критический выход, возвращаем 3
  }
  char video_id[BUF_LEN]; // Память под id
  while (fgets(video_id, BUF_LEN, fp)) { // Читаем строки плейлиста
    video_id[strcspn(video_id, "\n")] = '\0';  // Отбрасываем всё за первым \n включительно
    if (!is_video_downloaded(video_id)) {
      // Видео не найдено в логе, создам его url
      char video_url[BUF_LEN]; // Память под url
      snprintf(video_url, BUF_LEN, "https://www.youtube.com/watch?v=%s", video_id);

      run_yt_dlp(video_url, MODE2, DRAY_DIR, FNAME); // Качаем
      log_video_id(video_id); // Логируем
      sleep(5); // Спим (вместо задержки в опциях yt-dlp)
    }
  }
  pclose(fp);
}
