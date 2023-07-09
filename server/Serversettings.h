#ifndef SETTINGS_H
#define SETTINGS_H

#include <QHostAddress>

//NETWORK SETTINGS
int SERVER_PORT = 4335;
int CLIENT_PORT = 4336;
QHostAddress ADDRESS = QHostAddress::LocalHost;

//REQUESTS
char ASK[4] ="ask";
char INIT[4] ="ini";
char STAT[4] ="sta";

#endif // SETTINGS_H
