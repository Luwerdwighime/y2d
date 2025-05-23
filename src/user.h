/**
 * @file user.h
 * @brief Модуль для работы с юзером
 */

#pragma once
#include <stdio.h>   // Для getchar(), fgets(), printf()
#include <stdlib.h>  // Для malloc()
#include <string.h>  // Для strcspn()
#include "config.h"  // Константы

/**
 * @brief Показывает главное меню и копирует выбор юзера в указатель
 *
 * @return Символ выбранного режима
 */
char menu();

/**
 * @brief Вытряхивает url с юзера и сохраняет его в указатель
 *
 * @return Указатель на URL
 */
char* getUrl();

/**
 * @brief Выводит хэлп
 */
void help();

