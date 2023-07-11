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

private:
    Ui::MainWindow *ui;

    void initSocket(QHostAddress address, int port);
    void readPendingDatagrams();
    void sendDatagram(char command[], uint16_t id,QHostAddress address, int port);
    int makeCheckSum(QByteArray datagram);
    void addAddress(QHostAddress* address, uint16_t* port);
    void removeAddress(QHostAddress address, uint16_t port);

    bool isInit(QString address);
    bool isInit(QHostAddress* address, uint16_t* port);
    void fillTable();
};
#endif // MAINWINDOW_H
