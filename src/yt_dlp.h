/**
 * @file yt_dlp.h
 * @brief Модуль для работы с yt-dlp
 */

#pragma once
#include <stdio.h>  // Для printf(), snprintf(), popen(), perror()
#include <stdlib.h> // Для system()
#include <string.h> // Для strcpy(), strcspn()
#include <unistd.h> // Для sleep()
#include "cfg.h"    // Для config
#include "config.h" // Константы
#include "fs.h"     // Для is_video_downloaded()

/**
 * @brief Скачка url с запрошенным режимом
 *
 * @param url  Строка с url
 * @param mode Один из пяти режимов работы, букво-цифрами от '1' до '5'
 */
void yt_dlp(char* url, char mode);

/**
 * @brief Обёртка вокруг консольной команды yt-dlp
 *
 * @param url      Что качать
 * @param opts     С какими опциями
 * @param out_dir  Куда складывать
 * @param out_tmpl Как называть
 */
void run_yt_dlp(char *url, char *opts, char *out_dir, char *out_tmpl);

/**
 * @brief Получение и обработка ID видео из плейлиста
 *
 * @param url Url плейлиста
 */
void process_playlist_ids(char *url);

