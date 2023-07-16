#ifndef KOI7_H
#define KOI7_H
#include <string>


class KOI7
{
public:
    KOI7();
    char* charStr = nullptr;
    KOI7(char * charStr);
    char* charSetConverter(char * charStr, char *resStr, const char* toCharSet, const char* fromCharSet);
    char* toKOI7();
    char* toUTF8();
    ~KOI7();
};

#endif // KOI7_H
