/**
 * @file user.h
 * @brief Модуль для работы с юзером
 */

#pragma once
#include <stdio.h>  // Для getchar(), fgets()
#include "config.h" // Конфигурация

/**
 * @brief Показывает главное меню
 *
 * @return Символ юзерского выбора
 */
char menu();

/**
 * @brief Вытряхивает url с юзера
 *
 * @return Строка юзерского ввода
 */
char* getUrl();

