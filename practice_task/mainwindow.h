#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QUdpSocket>
#include <QMainWindow>
#include <QGroupBox>
#include <QTableWidget>
#include <QNetworkDatagram>
#include "iostream"
#include "string"

typedef struct {
    uint16_t checkSum;
    char command[];
} cmdStruct;


#define ERROR_LIST_SIZE 42
#define ERROR_DECOMPRESSED_SIZE 48
#define ERROR_CONVERTED_SIZE 100
#pragma pack(push, 1)

typedef struct {
    uint16_t checkSum;
    time_t currentTime;
    uint16_t cmdCount;
    uint64_t fullTime;
    uint8_t byteToggles;
    char errorList[ERROR_LIST_SIZE];
    char command[];
} StatStruct;

#pragma pack(pop)


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

public:
    void setClientId();
    void initSocket(QHostAddress address, int port);
    void readPendingDatagrams();
    void sendDatagram(QByteArray datagramByte,
                      const QHostAddress address, const int port);

public:
    bool isInit(QString address);
    bool isInit(QHostAddress address, int port);
    void addAddress(QHostAddress address, int port);
    void destroyAllSessions();
    void removeAddress(QHostAddress address, int port);
    void removeAddress(QString fullAdress);

public:
    QByteArray prepareDatagram(const char command[], uint16_t id);
    uint16_t makeCheckSum(QByteArray &datagram);
    void setByteToToggles(uint8_t byteToggles);
    inline QString makeFullAddress(QHostAddress address, int port);
    void setAddressAndPortFromLineEdit(QHostAddress &address, int &port);
    QHostAddress getAddressFromQStr(QString fullAddress);
    int getPortFromQStr(QString fullAddress);

public:
    void chooseCmd(QHostAddress address, int port, cmdStruct *readData);
    void readStat(StatStruct &readStatData);
    void readAsk(QHostAddress address, int port, uint16_t pkgCheckSum);
    void readEnd(QString fullAddress);
    void sendEnd(QHostAddress address, int port);



private:
    uint16_t clientId;
    uint16_t checkSum = 0;
    QSet<QString> addresses;
    QUdpSocket *udpSocket;

private:
    Ui::MainWindow *ui;

private:
    void setAddressTableToDefault(QTableWidget *table);
    void fillAddressTable();
    void clearWindow();
    void clearQLineEditsFromGroupBox(QGroupBox * groupBox);
    void setProcessedToggles(char *errorList, char byteToggles);
    void setErrors(char errorList[]);
    void setMajorData(uint16_t cmdCount, time_t currentTime, uint64_t fullTime);
    inline char* prepareErrorList(char* errorList);



private slots:
    void on_initPushButton_clicked();
    void on_statBtn_clicked();
    void on_endSessionBtn_clicked();
    void on_sessionTable_cellDoubleClicked(int row);
};
#endif // MAINWINDOW_H
