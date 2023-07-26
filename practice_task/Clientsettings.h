#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H


#include <QHostAddress>

namespace networkSettings
{
//RUNNING SERVER SETTINGS
    const int SERVER_PORT = 4335;
    const int CLIENT_PORT = 4336;
    const QHostAddress ADDRESS = QHostAddress::LocalHost;
}

namespace cmdSettings
{
//SIZES
    const short PORT_SIZE = 5;
    const short ADDRESS_SIZE = 17 + PORT_SIZE; //255.255.255.255:65535 + '\0' == 22 symbols
//REQUESTS
    const char ASK[] ="ask";
    const char INIT[] ="ini";
    const char STAT[] ="sta";
    const char END[] = "end";
}


#endif // SERVERSETTINGS_H
