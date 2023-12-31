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


/*!
\brief Device emulator
   Class for emulating device due to protocol(init and status).

  - initializing client == read client: (uint16_t random_id, const char* "ini")
  -> send client (uint32_t crcpkg, char * "ask"):

- statistics of server == read client: (uint16_t id, const char* "sta") - >
  -> send client (uint32_t crcpkg, uint16_t cmdCount, uint16_t current_time, uint64_t worktime,  char * "ask") +

  + byte of 8 toggle states(0 - off; 1 - on) and its 8 errors ("ошибка" - invalid, "испр.№" - correct);

  Error list includes KOI7 encoding then compressing 8 bits to 7(8 toggles = 42 bytes): charsetconv.h
*/
class Server: public QMainWindow
{

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
    void sendEnd(QNetworkDatagram &datagram, int checkSum);
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
