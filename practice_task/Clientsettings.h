#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include <QHostAddress>

//NETWORK SETTINGS
int SERVER_PORT = 4335;
int CLIENT_PORT = 4336;
QHostAddress ADDRESS = QHostAddress::LocalHost;

//REQUESTS
char ASK[4] ="ask";
char INIT[4] ="ini";
char STAT[4] ="sta";

//SIZES
const short CMD_SIZE = 4;
const short PORT_SIZE = 5;
const short ADDRESS_SIZE = 17 + PORT_SIZE; //255.255.255.255:65535 + '\0' == 22 symbols

#endif // SERVERSETTINGS_H
