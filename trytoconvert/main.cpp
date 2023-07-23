#include <iostream>
#include <bitset>
#include <string.h>
using namespace std;

int main()
{
    char convStr[] = "O[IBKAO[IBKAO[IBKAO[IBKAO[IBKAO[IBKAO[IBKAO[IBKA";
    bitset<8> bits;

    for(size_t i = 0; i < strlen((char*)convStr); i++)
    {
        for( int j = 0; j < 8; j++)
        {
            bits.set(j, convStr[i] & (1<<j));
        }
        cout<<i<<" "<<convStr[i]<<" "<<bits<<"="<<(int)convStr[i]<<endl;
    }
    cout<<"==================================================================="<<endl;
    int oldInd = 0;
    int newLen = strlen(convStr) - strlen(convStr) / 7;
    unsigned char buf[100]{'\0'};

    for(int newInd = 0; newInd < newLen; newInd++)
    {
        buf[newInd] = convStr[oldInd] << (newInd % 7 + 1);
        buf[newInd] |= convStr[oldInd + 1] >> (6 - newInd % 7);

        if((newInd+1)%7 == 0)
            oldInd++;
        oldInd++;


    }
    for(size_t i = 0; i < strlen((char*)buf); i++)
    {
        for( int j = 0; j < 8; j++)
        {
            bits.set(j, buf[i] & (1<<j));
        }
        cout<<i<<" "<<buf[i]<<" "<<bits<<"="<<(int)buf[i]<<endl;
    }
    cout<<strlen((char*)buf)<<" "<<strlen(convStr)<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    unsigned char newbuf[100]{'\0'};
    int newnewInd = 0;

    for(size_t newoldInd = 0; newoldInd < strlen((char*)buf); newoldInd++)
    {
        newbuf[newnewInd] |= buf[newoldInd] >> (newoldInd % 7 + 1);
        newbuf[++newnewInd] |= (buf[newoldInd] & (1<<(newoldInd % 7 + 1))-1) << (6 - newoldInd % 7);
        if((newoldInd+1)%7 == 0)
            newnewInd++;
    }

    for(size_t i = 0; i < strlen((char*)newbuf); i++)
    {
        for( int j = 0; j < 8; j++)
        {
            bits.set(j, newbuf[i] & (1<<j));
        }
        cout<<i<<" "<<newbuf[i]<<" "<<bits<<"="<<(int)newbuf[i]<<endl;
    }

    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<newbuf<<" "<<strlen((char*)buf)<<strlen((char*)newbuf)<<endl;
    return 0;
}
