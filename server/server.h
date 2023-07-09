#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QHostAddress>
#include <vector>
class Server: public QObject
{
    Q_OBJECT

public:
    std::vector<int> sessions;
    Server();
    Server(QHostAddress address, int port);
    ~Server();

private:

    void initSocket(QHostAddress address, int port);
    void readPendingDatagrams();
    void sendDatagram(int checkSum, char command[], QHostAddress address, int port);
    void addSession(int checkSum);
    int makeCheckSum(QByteArray datagram);
};

#endif // SERVER_H
