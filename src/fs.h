/**
 * @file fs.h
 * @brief Модуль для работы с файловой системой
 */

#pragma once
#include <errno.h>    // Для errno и EEXIST
#include <stdio.h>    // Для perror(), FILE, fopen(), fclose(), fprintf(), snprintf()
#include <stdlib.h>   // Для exit()
#include <string.h>   // Для strcspn(), strcmp()
#include <sys/stat.h> // Для mkdir()


#include "config.h"   // Конфигурация

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
 * @brief Вычисляет путь к DRAY_LOG и копирует его в указатель
 *
 * @param path Указатель на полный путь к DRAY_LOG
 */
void drayLogPath(char* path);

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

