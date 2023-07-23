#ifndef CHARSETCONV_H
#define CHARSETCONV_H
#include <string>

enum class charSets : int
{
    KOI7 = 0,
    UTF8 = 1
};


class charSetConv
{
public:
    charSetConv(){};
    char* charSetConverter(char *src, char *dst, charSets toCharSetId, charSets fromCharSetId);
    char* toKOI7(char *src, char *dst);
    char* toUTF8(char *src, char *dst);
    char* compress8To7bits(char *src, char *dst);
    char* decompress7To8bits(char *src, char *dst);
    const char* chooseCharSetById(charSets charSetId);
    ~charSetConv(){};
};

#endif // CHARSETCONV_H
