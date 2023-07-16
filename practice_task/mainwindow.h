#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QUdpSocket>
#include <QMainWindow>
#include <QNetworkDatagram>
#include "iostream"
#include "string"


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

    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_statBtn_clicked();

    void on_endSessionBtn_clicked();

    void on_sessionTable_cellDoubleClicked(int row);

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
    void byteToToggles(uint8_t byteToggles);
    void clearWindow();
};
#endif // MAINWINDOW_H
