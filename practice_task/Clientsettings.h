#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include <QHostAddress>

//NETWORK SETTINGS
int SERVER_PORT = 4335;
int CLIENT_PORT = 4336;
QHostAddress ADDRESS = QHostAddress::LocalHost;

//SIZES
const short CMD_SIZE = 4;
const short PORT_SIZE = 5;
const short ADDRESS_SIZE = 17 + PORT_SIZE; //255.255.255.255:65535 + '\0' == 22 symbols

//REQUESTS
char ASK[CMD_SIZE] ="ask";
char INIT[CMD_SIZE] ="ini";
char STAT[CMD_SIZE] ="sta";
char END[CMD_SIZE] = "end";

#endif // SERVERSETTINGS_H
