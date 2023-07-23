#ifndef CHARSETCONV_H
#define CHARSETCONV_H
#include <string>


class charSetConv
{
public:
    charSetConv(){};
    char* charSetConverter(char * src, char *dst, const char* toCharSet, const char* fromCharSet);
    char* toKOI7();
    char* toUTF8(char *src, char *dst);
    char* compress8To7bits(char *src, char *dst);
    char* uncompress7To8bits(char *src, char *dst);
    ~charSetConv(){};
};

#endif // CHARSETCONV_H
