#include "charsetconv.h"
#include <QDebug>

FromKOI7ToUTF8Converter::FromKOI7ToUTF8Converter()
{
    const char* toCharSet = chooseCharSetById(charSets::UTF8);
    const char* fromCharSet = chooseCharSetById(charSets::KOI7);

    cd = iconv_open(toCharSet, fromCharSet);
    if (cd == (iconv_t)(-1))
        qWarning()<<"Cannot open converter from"<<toCharSet<<"to"<<fromCharSet;
}

FromKOI7ToUTF8Converter::~FromKOI7ToUTF8Converter()
{
    iconv_close(cd);
}
/*!
 * \brief charSetConv::charSetConverter
 * using src and dst string to convert src from
 * one encoding to another.
 * \param src - which string to convert
 * \param dst == converting result
 * \param toCharSetId is int from enum charSets from convert to
 * \param fromCharSetId is int from enum charSets to convert to
 * \return
 */
char *FromKOI7ToUTF8Converter::convertFromKOI7ToUTF8(char *src, char *dst)
{
    size_t inleft = strlen(src) + 1;
    size_t outleft = MAX_DST_SIZE;

    char   *inptr = src;
    char   *outptr = dst;

    int rc = iconv(cd, &inptr, &inleft, &outptr, &outleft);
    if (rc == -1) {
        fprintf(stderr, "Error in converting characters\n");
        exit(8);
    }

    return dst;

};


/*!
 * \brief charSetConv::compress8To7bits
 * via moving 8 bits to left and erase last 8th bit.
 * result_len = strlen(src) - strlen(src) / 7;
 * maxStrLen(src) == 114, maxStrLen(dst) == 100.
 * \return
 */
char* FromKOI7ToUTF8Converter::compress8To7bits(char *src, char *dst)
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

/*!
 * \brief charSetConv::decompress7To7bits
 * via moving 7 bits to right and restore initial values of bytes.
 * result_len = strlen(src) + strlen(src) / 7 + 1;
 * maxStrLen(src) == 85, maxStrLen(dst) == 100.
 * \return
 */
char* FromKOI7ToUTF8Converter::decompress7To8bits(char *src, char *dst)
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

/*!
 * \brief charSetConv::chooseCharSetById
 * using charSetId from charSets enum
 * to set encoding using string literals.
 * Example: chooseCharSetById(charSets::KOI7) returns "koi-7"
 * while charSets::KOI7 == 0.
 * \return
 */
const char* FromKOI7ToUTF8Converter::chooseCharSetById(charSets charSetId)
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
