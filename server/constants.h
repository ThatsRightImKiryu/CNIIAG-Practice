#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <time.h>
#include <stdint.h>

namespace cmdSettings
{
    const char ASK[] ="ask_";
    const char INIT[] ="init";
    const char STAT[] ="stat";
    const char END[] = "end_";
}

namespace errorSettings
{
    char ERROR_WORD[] = "ошибка";
    char OK_WORD[] =  "испр.#";
    #define ERROR_BLOCK_SIZE 6
    #define ERROR_LIST_MAXSIZE 100
    #define KOI7_STR_MAXSIZE ERROR_LIST_MAXSIZE / 2
}


#endif // CONSTANTS_H
