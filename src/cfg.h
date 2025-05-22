/**
 * @file cfg.h
 * @brief Анализирует конфигурацию в config.ini
 */

#pragma once
#include <stdio.h>   // Для printf()
#include <stdlib.h>  // Для atoi(), strtol()
#include <string.h>  // Для strdup()
#include "config.h"  // Константы
#include "ini.h"     // Анализатор ini-шек

/**
 * @brief Структура для хранения конфигурации вычитанной из config.ini
 */
typedef struct {
  int   fsDir_rights;
  char* fsVideo_dir;
  char* fsAudio_dir;
  char* fsDray_dir;
  char* fsDray_log;
  char* fsCookie_path;
  char* ytYtids;
  char* ytYtcmd;
  char* ytMode1;
  char* ytMode2;
  char* ytModep;
  char* ytFname;
  char* ytPname;
  int   ytRetr;
} Config;

/**
 * @brief Память под конфиг из ini
 */
extern Config config;

/**
 * @brief middle-ware функция для ini_parse(), анализирующая параметры из ini
 *
 * @param mainConf Указатель на структуру системного конфига
 * @param section  Указатель на строку с именем секции в ini
 * @param name     Указатель на строку с именем параметра в ini
 * @param value    Указатель на строку со значением параметра в ini
 *
 * @return Была ли ошибка при анализе
 */
static int analyser(void* mainConf, const char* section, const char* name, const char* value);

/**
 * @brief Загружает ini в config
 */
void loadIni();

