#include "charsetconv.h"
#include <QDebug>
#include <iconv.h>
#include <codecvt>
#include <set>
#include <iostream>



char *charSetConv::charSetConverter(char *src, char *dst, charSets toCharSetId, charSets fromCharSetId)
{

    iconv_t cd;
    size_t inleft = strlen(src)+1;
    size_t outleft = 100;
    int rc;
    const char* toCharSet = chooseCharSetById(toCharSetId);
    const char* fromCharSet = chooseCharSetById(fromCharSetId);

    if ((cd = iconv_open(toCharSet, fromCharSet)) == (iconv_t)(-1)) {
        fprintf(stderr, "Cannot open converter from %s to %s\n",
                                           toCharSet, fromCharSet);
        exit(8);
    }

    char   *inptr = src;
    char   *outptr = dst;

    rc = iconv(cd, &inptr, &inleft, &outptr, &outleft);
    if (rc == -1) {
        fprintf(stderr, "Error in converting characters\n");
        exit(8);
    }
    iconv_close(cd);
    qstrcpy(dst, dst);

    return dst;

};

char* charSetConv::toKOI7(char *src, char *dst)
{
    charSetConverter(src, dst, charSets::KOI7, charSets::UTF8);
    return dst;
}

char* charSetConv::toUTF8(char *src, char *dst)
{
    charSetConverter(src, dst, charSets::UTF8, charSets::KOI7);
    return dst;
}

char* charSetConv::compress8To7bits(char *src, char *dst)
{
    int oldInd = 0;
    int newLen = strlen(src) - strlen(src) / 7;
    unsigned char buf[100]{'\0'};

    for(int newInd = 0; newInd < newLen; newInd++)
    {
        buf[newInd] = src[oldInd] << (newInd % 7 + 1);
        buf[newInd] |= src[oldInd + 1] >> (6 - newInd % 7);

        if((newInd + 1) % 7 == 0) oldInd++;

        oldInd++;
    }

    qstrcpy(dst, (char*)buf);
    return dst;
}

char* charSetConv::decompress7To8bits(char *src, char *dst)
{
    unsigned char buf[100]{'\0'};
    int newInd = 0;
    size_t newLen = strlen(src) + strlen(src) / 7 + 1;
    for(size_t oldInd = 0; oldInd < newLen; oldInd++)
    {
        unsigned char currentChar = src[oldInd];
        buf[newInd] |= currentChar >> (oldInd % 7 + 1);
        buf[++newInd] |= (currentChar & (1<<(oldInd % 7 + 1))-1) << (6 - oldInd % 7);
        if((oldInd + 1) % 7 == 0)
            newInd++;
    }
    qstrcpy(dst, (char*)buf);

    return dst;
}

const char* charSetConv::chooseCharSetById(charSets charSetId)
{
    switch( charSetId)
    {
        case charSets::KOI7:
            return "koi-7";
            break;
        case charSets::UTF8:
            return "utf-8";
            break;
        default:
            return nullptr;
    }
};
