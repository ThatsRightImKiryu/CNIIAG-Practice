#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QUdpSocket>
#include <QMainWindow>
#include <QNetworkDatagram>
#include "iostream"
#include "string"

typedef struct {
    int checkSum;
    char command[];
} cmdStruct;

#pragma pack(push, 1)

typedef struct {
    int checkSum;
    time_t currentTime;
    uint16_t cmdCount;
    uint64_t fullTime;
    uint8_t byteToggles;
    char errorList[42];
    char command[];
} StatStruct;

#pragma pack(pop)


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    uint16_t clientId;
    QSet<QString> addresses;

public:
    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();


public:
    void initSocket(QHostAddress address, int port);
    void readPendingDatagrams();
    void sendDatagram(const char command[], const uint16_t id,
                      const QHostAddress address, const int port);

public:
    bool isInit(QString address);
    bool isInit(QHostAddress address, int port);
    void addAddress(QHostAddress address, int port);
    void removeAddress(QHostAddress address, int port);

public:
    int makeCheckSum(QByteArray &datagram);
    void byteToToggles(uint8_t byteToggles);
    QHostAddress getAddressFromQStr(QString fullAddress);
    int getPortFromQStr(QString fullAddress);

public:
    void chooseCmd(QNetworkDatagram &datagram, cmdStruct *readData);
    void readStat(StatStruct readStatData);
    void readAsk(QNetworkDatagram &datagram, cmdStruct *readData);
    void sendEnd();

private:
    Ui::MainWindow *ui;

private:
    int checkSum = 0;

private:
    void fillTable();
    void clearWindow();
    void setErrors(char errorList[]);
private slots:
    void on_pushButton_clicked();
    void on_statBtn_clicked();
    void on_endSessionBtn_clicked();
    void on_sessionTable_cellDoubleClicked(int row);
};
#endif // MAINWINDOW_H
