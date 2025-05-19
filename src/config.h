/**
 * @brief Конфигурация
 *
 * Пока мы ленимся сделать нормальный конфиг, вся конфигурация
 * будет собрана здесь и намертво вшита в бинарник
 */

#define BUF_LEN 2048 // 2Кб буффер под каждую строковую переменную (там url и команды с его участием, может быть много)

// Папки, пути, права
#define DIR_RIGHTS  0755
#define VIDEO_DIR   "/storage/emulated/0/Documents/tmp/video"
#define AUDIO_DIR   "/storage/emulated/0/Documents/tmp/audio"
#define DRAY_DIR    "/storage/emulated/0/Documents/usr/luwerdwighime/abok/"
#define DRAY_LOG    "dray_log.txt"
#define COOKIE_PATH "/data/data/com.termux/files/home/cookies_y2d.txt"

// Опции для yt-dlp
#define YTIDS "yt-dlp --get-id \"%s\"" // %s - это url
#define YTCMD "yt-dlp --no-check-formats %s -o \"%s/%s\" \"%s\"" // 4 %s будут подставлены (opts, out_dir, out_tmpl, url)
#define MODE1 "-f \"bestvideo[height<=480][vcodec=vp9]+bestaudio[acodec=opus]\" --merge-output-format webm"
#define MODE2 "-x --audio-format opus --audio-quality 128k --no-part --no-keep-video"
#define MODEP "--yes-playlist" // Добавка про плейлисты (MODE3 и MODE4)
#define FNAME "%(title)s.%(ext)s" // Шаблон названия для одиночных файлов
#define PNAME "%(playlist_title)s/%(playlist_index)05d_%(title)s.%(ext)s" // Шаблон названия для групп из плейлиста
#define RETR  3 // Число попыток скачки

