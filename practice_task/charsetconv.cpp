#include "charsetconv.h"
#include <QDebug>
#include <iconv.h>
#include <codecvt>
#include <set>
#include <iostream>
namespace charsets
{
    const char* charSetConv_CHARSET= "koi-7";
    const char* UTF8_CHARSET= "utf-8";
}

charSetConv::charSetConv(char * charStr)
{
    this->charStr = new char[strlen(charStr)+1];
    qstrcpy(this->charStr, charStr);
}

char *charSetConv::charSetConverter(char *charStr, char *resStr, const char* toCharSet, const char* fromCharSet)
{
    iconv_t cd;
    size_t inleft = strlen(charStr) + 1;
    size_t outleft = inleft * 2;
    int rc;

    if ((cd = iconv_open(toCharSet, fromCharSet)) == (iconv_t)(-1)) {
        fprintf(stderr, "Cannot open converter from %s to %s\n",
                                           fromCharSet, toCharSet);
        exit(8);
    }

    char   *inptr = charStr;
    char   *outptr = resStr;

    rc = iconv(cd, &inptr, &inleft, &outptr, &outleft);
    if (rc == -1) {
        fprintf(stderr, "Error in converting characters\n");
        exit(8);
    }
    iconv_close(cd);
    return resStr;
};

char* charSetConv::toKOI7()
{
    char *buf = new char[100]{'\0'};
    charSetConverter(charStr, buf, charsets::charSetConv_CHARSET, charsets::UTF8_CHARSET);
    qstrcpy(charStr, buf);
    if(!buf) delete[] buf;

    return charStr;
}

char* charSetConv::toUTF8()
{
    char *buf = new char[100]{'\0'};
    charSetConverter(charStr, buf, charsets::UTF8_CHARSET, charsets::charSetConv_CHARSET);
    qstrcpy(charStr, buf);
    if(!buf) delete[] buf;
    return charStr;
}

char* charSetConv::compress8To7bits()
{
    unsigned char *buf = new unsigned char[100]{'\0'};
    for(uint16_t wordInd = 0; wordInd < strlen(charStr) - strlen(charStr) / 7; wordInd++)
    {
        buf[wordInd] = charStr[wordInd] << (wordInd % 7 + 1);
       // char s = charStr[wordInd + 1] >> (6 - wordInd % 7);
        buf[wordInd] |= (charStr[wordInd + 1] >> (6 - wordInd % 7));
    }
    return (char*)buf;
}

char* charSetConv::uncompress7To8bits()
{
    unsigned char *buf = new unsigned char[100]{'\0'};

    for(uint16_t wordInd = 0; wordInd < strlen(charStr); wordInd++)
    {
        int byteInd = wordInd + wordInd / 7;
        unsigned char bit = charStr[byteInd];
        buf[byteInd] |= (bit >> (wordInd % 7 + 1));
        char firstNBytes = (bit & ((1 << (wordInd % 7 + 1))-1));
        buf[byteInd + 1] |= (firstNBytes << (6 - wordInd % 7));
    }
    return (char*)buf;
}
charSetConv::~charSetConv()
{
    if(!charStr) delete[] charStr;
}
