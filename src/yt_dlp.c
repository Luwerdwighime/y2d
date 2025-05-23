#include "yt_dlp.h"

void yt_dlp(char* url, char mode) {
  char opts[BUF_LEN]; // Память под опции
  switch (mode) {
    case '1': // Качаем видео
      run_yt_dlp(url, config.ytMode1, config.fsVideo_dir, config.ytFname);
      return;
    case '2': // Качаем аудио
      run_yt_dlp(url, config.ytMode2, config.fsAudio_dir, config.ytFname);
      return;
    case '3': // Качаем видеоплейлист
      snprintf(opts, BUF_LEN, "%s %s", config.ytMode1, config.ytModep);
      run_yt_dlp(url, opts, config.fsVideo_dir, config.ytPname);
      return;
    case '4': // Качаем аудиоплейлист
      snprintf(opts, BUF_LEN, "%s %s", config.ytMode2, config.ytModep);
      run_yt_dlp(url, opts, config.fsAudio_dir, config.ytPname);
      return;
    case '5': // Докачиваем Дмитрия Рея
      process_playlist_ids(url);
      return;
  }
}

void run_yt_dlp(char *url, char *opts, char *out_dir, char *out_tmpl) {
  // Создаём команду
  char cmd[BUF_LEN];
  snprintf(cmd, BUF_LEN, config.ytYtcmd, opts, out_dir, out_tmpl, url);

  // Пробуем в цикле
  int retries = config.ytRetr;
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
  printf("Не удалось скачать после %d попыток url: %s\n", config.ytRetr, url);
}

void process_playlist_ids(char *url) {
  // Создаём команду
  char cmd[BUF_LEN];
  snprintf(cmd, BUF_LEN, config.ytYtids, url);

  // Запускаем команду и читаем её stdout построчечно
  FILE *fp = popen(cmd, "r");
  if (!fp) {
    perror("Ошибка получения ID видео");
    exit(ERR_YTID); // Критический выход
  }
  char video_id[BUF_LEN]; // Память под id
  while (fgets(video_id, BUF_LEN, fp)) { // Читаем строки плейлиста
    video_id[strcspn(video_id, "\n")] = '\0';  // Отбрасываем \n
    if (!is_video_downloaded(video_id)) {
      // Видео не найдено в логе, создам его url
      char video_url[BUF_LEN]; // Память под url
      snprintf(video_url, BUF_LEN, "https://www.youtube.com/watch?v=%s", video_id);

      run_yt_dlp(video_url, config.ytMode2, config.fsDray_dir, config.ytFname); // Качаем
      log_video_id(video_id); // Логируем
      sleep(5); // Спим (вместо задержки в опциях yt-dlp)
    }
  }
  pclose(fp);
}
