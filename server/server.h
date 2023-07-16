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



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    uint16_t clientId;
    int checkSum = 0;
    int tableSize = 0;
    std::vector<QString> addresses;

//private slots:
//    void on_pushButton_clicked();

//    void on_statBtn_clicked();

//    void on_endSessionBtn_clicked();

//    void on_sessionTable_cellDoubleClicked(int row);

private:
    Ui::MainWindow *ui;

    void initSocket(QHostAddress address, int port);
    void readPendingDatagrams();
    void sendDatagram(const char command[], const uint16_t id, const QHostAddress address, const int port);
    int makeCheckSum(QByteArray &datagram);
    void addAddress(QHostAddress address, int port);
    void removeAddress(QHostAddress address, int port);

    bool isInit(QString address);
    bool isInit(QHostAddress address, int port);
    void fillTable();
};


QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE


class Server: public QMainWindow
{
    Q_OBJECT


public:

    std::vector<int> sessions;
    uint16_t cmdCount = 0;
    std::time_t startTime = std::time(nullptr);
    char byteToggles = 0;
    char toggleError = 0;

    Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void on_toggleErrorCheckBox_toggled(bool checked);

private:
    Ui::Server *ui;

    void initSocket(QHostAddress address, int port);
    void readPendingDatagrams();
    void sendDatagram(int checkSum, const char command[],
                      const QHostAddress address, const int port);
    void sendDatagram(int checkSum, const char command[],  std::time_t currentTime,
                      std::time_t fullTime, const QHostAddress address, const int port);

    void addSession(uint16_t id);
    int makeCheckSum(QByteArray &datagram);
    bool isInit(int id);
    inline std::time_t workingTime(std::time_t currentTime,
                                   std::time_t startTime);

    void chooseCmd(QNetworkDatagram &datagram, cmdStruct *readData);
    void sendInit(QNetworkDatagram &datagram, cmdStruct *readData, int checkSum);
    void sendStat(QNetworkDatagram &datagram, int checkSum);
    void sendEnd(cmdStruct *readData);
    char togglesToByte();
    void makeErrorsPackage(char * charStr);
};

#endif // SERVER_H
