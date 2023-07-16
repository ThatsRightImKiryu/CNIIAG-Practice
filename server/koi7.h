#ifndef KOI7_H
#define KOI7_H
#include <string>


class KOI7
{
public:
    KOI7();
    char *koi7_str = new char[49];
//    char *utf8_str = new char[100];
    KOI7(char * charStr);
    char* charSetConverter(char * charStr, char *resStr, const char* toCharSet, const char* fromCharSet);
    char* toUtf8(char * str);

};

#endif // KOI7_H
