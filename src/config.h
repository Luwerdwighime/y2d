/**
 * @file config.h 
 * @brief Константы
 */

#define BUF_LEN 2048 // 2Кб буффер под каждую строковую переменную (там url и команды с его участием, может быть много)
#define INI_CFG "config.ini" // Путь до конфига

// Коды ошибок, которые мы возвращаем в консоль
#define ERR_OPTS    1
#define ERR_INI     2
#define ERR_DIR     3
#define ERR_DRAYLOG 4
#define ERR_YTID    5
