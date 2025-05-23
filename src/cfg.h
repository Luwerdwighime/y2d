/**
 * @file cfg.h
 * @brief Анализирует конфигурацию в config.ini
 */

#pragma once
#include <stdbool.h> // Для типа bool
#include <getopt.h>  // Для getopt_long(), optarg, optind
#include <stdio.h>   // Для printf()
#include <stdlib.h>  // Для atoi(), strtol()
#include <string.h>  // Для strdup()
#include "config.h"  // Константы
#include "ini.h"     // Анализатор ini-шек

/**
 * @brief Структура для опций командной строки
 */
typedef struct {
  bool  bug;    /// Флаг встречи бага при анализе
  char* config; /// Указатель на путь до ini конфига
  char  mode;   /// Режим работы
  char* url;    /// Указатель на URL
} Options;

/**
 * @brief Память под опции из командной строки
 */
extern Options options;

/**
 * @brief Анализирует опции командной строки
 *
 * @param argc Количество параметров командной строки
 * @param argv Массив указателей на строки с параметрами
 */
void getTermOpts(int argc, char* argv[]);

/**
 * @brief Структура для хранения конфигурации вычитанной из config.ini
 */
typedef struct {
  int   fsDir_rights;  /// Права доступа к создаваемым папкам, 9 бит
  char* fsVideo_dir;   /// Указатель на строку с путём к папке для видео
  char* fsAudio_dir;   /// Указатель на строку с путём к папке для аудио
  char* fsDray_dir;    /// Указатель на строку с путём к папке для Дмитрия Рея
  char* fsDray_log;    /// Указатель на строку с именем файла лога Дмитрия Рея
  char* fsCookie_path; /// Указатель на строку с путём к куке YouTube
  char* ytYtids;       /// Указатель на строку с командой для списка плейлиста
  char* ytYtcmd;       /// Указатель на строку с командой для скачки
  char* ytMode1;       /// Указатель на строку с опциями режима 1/3
  char* ytMode2;       /// Указатель на строку с опциями режима 2/4
  char* ytModep;       /// Указатель на строку с допопциями плейлистовых режимов 3/4
  char* ytFname;       /// Указатель на строку с шаблоном имени файла
  char* ytPname;       /// Указатель на строку с шаблоном папки и файлов для плейлиста
  int   ytRetr;        /// Число попыток закачки 
} Config;

/**
 * @brief Память под конфиг из ini
 */
extern Config config;

/**
 * @brief middle-ware функция для ini_parse(), анализирующая параметры из ini
 *
 * @param mainConf Указатель на структуру системного конфига (требование ini_parse(), у нас конфиг глобален - не обязательно)
 * @param section  Указатель на строку с именем секции в ini
 * @param name     Указатель на строку с именем параметра в ini
 * @param value    Указатель на строку со значением параметра в ini
 *
 * @return Была ли ошибка при анализе
 */
static int analyser(void* mainConf, const char* section, const char* name, const char* value);

/**
 * @brief Загружает ini в переменную config
 *
 * @param file Указатель на строку с именем файла ini
 */
void loadIni(char* file);

