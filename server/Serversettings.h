#ifndef SETTINGS_H
#define SETTINGS_H

#include <QHostAddress>

namespace networkSettings
{
//RUNNING SERVER SETTINGS
    const int SERVER_PORT = 4335;
    const int CLIENT_PORT = 4336;
    const QHostAddress ADDRESS = QHostAddress::LocalHost;
}


#endif // SETTINGS_H
