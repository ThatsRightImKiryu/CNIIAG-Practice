#ifndef SETTINGS_H
#define SETTINGS_H

#include <QHostAddress>

//NETWORK SETTINGS
int SERVER_PORT = 4335;
int CLIENT_PORT = 4336;
QHostAddress ADDRESS = QHostAddress::LocalHost;

//SIZES
const short CMD_SIZE = 4;

//REQUESTS
char ASK[CMD_SIZE] ="ask";
char INIT[CMD_SIZE] ="ini";
char STAT[CMD_SIZE] ="sta";
char END[CMD_SIZE] = "end";


#endif // SETTINGS_H
