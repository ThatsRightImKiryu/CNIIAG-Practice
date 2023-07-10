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
    int cmdCount = 0;
    std::time_t startTime = std::time(nullptr);
    Server();
    Server(QHostAddress address, int port);
    ~Server();

private:

    void initSocket(QHostAddress address, int port);
    void readPendingDatagrams();
    void sendDatagram(int checkSum, char command[], QHostAddress address, int port);
    void sendDatagram(int checkSum, char command[],  std::time_t currentTime,
                      std::time_t fullTime, QHostAddress address, int port);
    void addSession(int id);
    int makeCheckSum(QByteArray datagram);
    bool isInit(int id);
};

#endif // SERVER_H
