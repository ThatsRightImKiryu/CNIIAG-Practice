#include "charsetconv.h"
#include <QDebug>
#include <iconv.h>
#include <codecvt>
#include <set>

namespace charsets{
    const char* KOI7_CHARSET= "koi-7";
    const char* UTF8_CHARSET= "utf-8";
}

charSetConv::charSetConv(char * charStr)
{
    this->charStr = new char[100];
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
    char buf[49] = "";
    charSetConverter(charStr, buf, charsets::KOI7_CHARSET, charsets::UTF8_CHARSET);
    qstrcpy(charStr, buf);
    return charStr;
}

char* charSetConv::toUTF8()
{
    char buf[100] = "";
    charSetConverter(charStr, buf, charsets::UTF8_CHARSET, charsets::KOI7_CHARSET);
    qstrcpy(charStr, buf);
    return charStr;
}

charSetConv::~charSetConv()
{
    if(!charStr) delete[] charStr;
}
