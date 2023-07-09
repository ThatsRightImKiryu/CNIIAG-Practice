#include <QCoreApplication>
#include <server.h>

int main(int argc, char *argv[])
{    
    QCoreApplication a(argc, argv);

    Server server(QHostAddress::LocalHost, 4335);

    return a.exec();
}
