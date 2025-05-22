/**
 * @file user.h
 * @brief Модуль для работы с юзером
 */

#pragma once
#include <getopt.h>  // Для getopt_long()
#include <stdbool.h> // Для типа bool
#include <stdio.h>   // Для getchar(), fgets(), printf()
#include <string.h>  // Для strcspn(), strcpy()
#include "config.h"  // Константы

/**
 * @brief Структура для опций командной строки
 */
typedef struct {
  bool bug;  // Флаг встречи бага при анализе
  char mode; // Режим работы
  char* url; // URL
} Options;

/**
 * @brief Анализирует опции командной строки
 *
 * @return Структура с опциями
 */
Options getTermOpts(int argc, char *argv[]);

/**
 * @brief Показывает главное меню и копирует выбор юзера в указатель
 *
 * @param mode Указатель на символ выбранного режима
 */
void menu(char* mode);

/**
 * @brief Вытряхивает url с юзера и сохраняет его в указатель
 *
 * @param url Указатель на URL
 */
void getUrl(char* url);

/**
 * @brief Выводит хэлп
 */
void help();

