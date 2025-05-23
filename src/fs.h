/**
 * @file fs.h
 * @brief Модуль для работы с файловой системой
 */

#pragma once
#include <stdio.h>    // Для perror(), FILE, fopen(), fclose(), printf(), fprintf(), snprintf()
#include <stdlib.h>   // Для exit(), malloc(), free(), system()
#include <string.h>   // Для strcspn(), strcmp()
#include "cfg.h"      // Для config
#include "config.h"   // Константы

/**
 * @brief Создаёт папку, если её ещё нет
 *
 * @param path Путь до папки
 */
void mkdir_p(char *path);

/**
 * @brief Создаёт нужные папки
 */
void initDirs();

/**
 * @brief Возвращает указатель на путь к DRAY_LOG
 *
 * @return Указатель на полный путь к DRAY_LOG
 */
char* drayLogPath();

/**
 * @brief Запись ID видео в лог
 */
void log_video_id(char *video_id);

/**
 * @brief Проверка, есть ли ID видео в логе
 *
 * @param video_id
 * @return 0 если нет, 1 если да
 */
int is_video_downloaded(char *video_id);

