#ifndef CHARSETCONV_H
#define CHARSETCONV_H
#include <string>


class charSetConv
{
public:
    charSetConv();
    char* charStr = nullptr;
    charSetConv(char * charStr);
    char* charSetConverter(char * charStr, char *resStr, const char* toCharSet, const char* fromCharSet);
    char* toKOI7();
    char* toUTF8();
    ~charSetConv();
};

#endif // CHARSETCONV_H
