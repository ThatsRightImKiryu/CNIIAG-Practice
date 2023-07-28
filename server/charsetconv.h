#ifndef CHARSETCONV_H
#define CHARSETCONV_H
#include <iconv.h>


#define MAX_DST_SIZE 100
#define MAX_COMPRESSED_SIZE 86

enum class charSets : int
{
    KOI7 = 0,
    UTF8 = 1
};

/*!
 * \brief The charSetConv class
 * use to convert chars from of encoding to another
 * and compressing-decompressing bytes
 */
class FromUTF8ToKOI7Converter
{
public:
    FromUTF8ToKOI7Converter();
    char* convertFromUTF8ToKOI7(char *src, char *dst);
    char* compress8To7bits(char *src, char *dst);
    char* decompress7To8bits(char *src, char *dst);
    ~FromUTF8ToKOI7Converter();

private:
    const char* chooseCharSetById(charSets charSetId);

private:
    iconv_t cd;
};

#endif // CHARSETCONV_H
