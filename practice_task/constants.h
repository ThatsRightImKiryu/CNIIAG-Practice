#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string.h>


namespace cmdSettings
{
const char ASK[] ="ask_";
const char INIT[] ="init";
const char STAT[] ="stat";
const char END[] = "end_";
}

namespace labels
{
    const char *TOGGLE_ON = "ON";
    const char *TOGGLE_OFF = "OFF";
    const char *TOGGLE_OK = "Correct";
    const char *TOGGLE_INVALID = "INVALID";
}

namespace deviceStates
{
//STATES
    const char *TOGGLE_OK = "испр.#";
    const char *TOGGLE_INVALID = "ошибка";
//SIZES
    const int TOGGLE_OK_SIZE = strlen(TOGGLE_OK);
    const int TOGGLE_INVALID_SIZE = strlen(TOGGLE_INVALID);
    const int MAX_STATE_SIZE = 13;
}


#endif // CONSTANTS_H
