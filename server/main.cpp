#include <QCoreApplication>
#include <server.h>

int main(int argc, char *argv[])
{    
    QCoreApplication a(argc, argv);
//QHostAddress::LocalHost, 4335

    Server server;

    return a.exec();
}
