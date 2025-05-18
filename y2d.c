#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h> // Для sleep

#define VIDEO_DIR "/storage/emulated/0/Documents/tmp/video"
#define AUDIO_DIR "/storage/emulated/0/Documents/tmp/audio"
#define DRAY_DIR "/storage/emulated/0/Documents/usr/luwerdwighime/abok"
#define MAX_LEN 2048

// Создание директории
void mkdir_p(const char *path) {
    if (mkdir(path, 0755) && errno != EEXIST) {
        perror("Ошибка создания директории");
        exit(1);
    }
}

// Формирование и выполнение команды yt-dlp с повторными попытками
void run_yt_dlp(const char *url, const char *opts, const char *out_dir, const char *out_tmpl) {
    char cmd[MAX_LEN];
    int retries = 3;
    snprintf(cmd, sizeof(cmd), "yt-dlp --no-check-formats %s -o \"%s/%s\" \"%s\"",
             opts, out_dir, out_tmpl, url);
    while (retries--) {
        if (system(cmd) == 0) {
            printf("Готово, файлы в %s/%s\n", out_dir, out_tmpl[0] == '%' ? "%(playlist_title)s" : "");
            return;
        }
        printf("Ошибка скачивания, повтор через 10 секунд (%d попыток осталось)...\n", retries);
        sleep(10);
    }
    printf("Не удалось скачать после 3 попыток: %s\n", url);
    // Не завершаем программу, чтобы продолжить с другими видео
}

// Проверка, есть ли ID видео в логе
int is_video_downloaded(const char *video_id) {
    FILE *log = fopen(DRAY_DIR "/dray_log.txt", "r");
    if (!log) return 0; // Лог не существует, считаем, что видео не скачано
    char line[MAX_LEN];
    while (fgets(line, sizeof(line), log)) {
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, video_id) == 0) {
            fclose(log);
            return 1; // Видео уже скачано
        }
    }
    fclose(log);
    return 0;
}

// Запись ID видео в лог
void log_video_id(const char *video_id) {
    FILE *log = fopen(DRAY_DIR "/dray_log.txt", "a");
    if (!log) {
        perror("Ошибка открытия лога");
        return;
    }
    fprintf(log, "%s\n", video_id);
    fclose(log);
}

// Получение и обработка ID видео из плейлиста
void process_playlist_ids(const char *url, const char *base_opts, const char *out_dir, const char *out_tmpl) {
    char cmd[MAX_LEN], video_id[MAX_LEN], opts[MAX_LEN];
    FILE *fp;
    snprintf(cmd, sizeof(cmd), "yt-dlp --get-id \"%s\"", url);
    fp = popen(cmd, "r");
    if (!fp) {
        perror("Ошибка получения ID видео");
        exit(1);
    }
    snprintf(opts, sizeof(opts), "%s --sleep-interval 5 --sleep-requests 1", base_opts); // Увеличенная задержка
    while (fgets(video_id, sizeof(video_id), fp)) {
        video_id[strcspn(video_id, "\n")] = '\0';
        if (!is_video_downloaded(video_id)) {
            char video_url[MAX_LEN]; // Исправлено: MAX_NUMERIC -> MAX_LEN, добавлены квадратные скобки
            snprintf(video_url, sizeof(video_url), "https://www.youtube.com/watch?v=%s", video_id);
            run_yt_dlp(video_url, opts, out_dir, out_tmpl);
            log_video_id(video_id);
        }
    }
    pclose(fp);
}

int main() {
    char choice, url[MAX_LEN], numbering_choice;

    // Создаем директории
    mkdir_p(VIDEO_DIR);
    mkdir_p(AUDIO_DIR);
    mkdir_p(DRAY_DIR);

    // Меню
    printf("Что скачать?\n(1) Видео\n(2) Аудио\n(3) Плейлист видео\n(4) Плейлист аудио\n");
    printf("Выбери (1-4): ");
    choice = getchar();
    getchar(); // Поглощаем \n

    if (choice < '1' || choice > '4') {
        printf("Неверный выбор\n");
        return 1;
    }

    // Запрашиваем URL
    printf("Вставь ссылку: ");
    if (!fgets(url, sizeof(url), stdin)) return 1;
    url[strcspn(url, "\n")] = '\0';

    // Выбор команды
    switch (choice) {
    case '1':
        run_yt_dlp(url, "-f \"bestvideo[height<=480]+bestaudio\" --merge-output-format webm",
                   VIDEO_DIR, "%(title)s.%(ext)s");
        break;
    case '2':
        run_yt_dlp(url, "-x --audio-format opus --audio-quality 128k --no-part --no-keep-video",
                   AUDIO_DIR, "%(title)s.%(ext)s");
        break;
    case '3':
        run_yt_dlp(url, "-f \"bestvideo[height<=480][vcodec=vp9]+bestaudio[acodec=opus]\" "
                   "--merge-output-format webm --yes-playlist",
                   VIDEO_DIR, "%(playlist_title)s/%(playlist_index)05d_%(title)s.%(ext)s");
        break;
    case '4': {
        const char *base_opts = "-x --audio-format opus --audio-quality 128k --yes-playlist --no-part --no-keep-video";
        printf("Убрать нумерацию в именах файлов? (y/n): ");
        numbering_choice = getchar();
        getchar(); // Поглощаем \n
        if (numbering_choice == 'y' || numbering_choice == 'Y') {
            process_playlist_ids(url, base_opts, DRAY_DIR, "%(title)s.%(ext)s");
            printf("Готово, файлы в %s\n", DRAY_DIR);
        } else {
            run_yt_dlp(url, base_opts, AUDIO_DIR, "%(playlist_title)s/%(playlist_index)05d_%(title)s.%(ext)s");
        }
        break;
    }
    }

    return 0;
}
