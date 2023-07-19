#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QUdpSocket>
#include "iostream"
#include "string"
#include <QObject>
#include <QHostAddress>
#include <vector>
#include <QNetworkDatagram>

typedef struct {
    uint16_t id;
    char command[];
} cmdStruct;

typedef struct {
    int checkSum;
    char command[];
} ServerStruct;

#pragma pack(push, 1)

typedef struct {
    int checkSum;
    time_t currentTime;
    uint16_t cmdCount;
    uint64_t fullTime;
    char command[];
} StatStruct;

#pragma pack(pop)


QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE


class Server: public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();


public:
    void initSocket(QHostAddress address, int port);
    void readPendingDatagrams();
    void sendDatagram(int checkSum, const char command[],
                      const QHostAddress address, const int port);
    void sendDatagram(int checkSum, const char command[],  std::time_t currentTime,
                      std::time_t fullTime, const QHostAddress address, const int port);

public:
    void chooseCmd(QNetworkDatagram &datagram, cmdStruct *readData);
    void sendInit(QNetworkDatagram &datagram, cmdStruct *readData, int checkSum);
    void sendStat(QNetworkDatagram &datagram, int checkSum);
    void readEnd(cmdStruct *readData);

public:
    bool isInit(int id);
    void addSession(uint16_t id);

private:
    char togglesToByte();
    int makeCheckSum(QByteArray &datagram);
    void makeErrorsPackage(char * charStr);
    inline std::time_t workingTime(std::time_t currentTime,
                                   std::time_t startTime);

private:
    Ui::Server *ui;

private:
    char byteToggles = 0;
    std::time_t startTime = std::time(nullptr);

private:
    uint16_t cmdCount = 0;
    QSet<int> sessions;


};

#endif // SERVER_H
