#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <QCryptographicHash>
#include <Clientsettings.h>
typedef struct {
    char command[4];
    int checkSum;
} ServerStruct;


short session_id;
QUdpSocket *udpSocket;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(nullptr));
    clientId = rand()%65536;
    qInfo()<<"Client was init with id="<<clientId;
    initSocket(ADDRESS, CLIENT_PORT);
}

MainWindow::~MainWindow()
{
    udpSocket->close();
    delete udpSocket;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString LEText = ui->lineEdit->text();
    QStringList slist = LEText.split(":");

    QHostAddress address = QHostAddress(slist.value(0));
    int port = slist.value(1).toInt();
    qDebug()<<"HSOT"<<address<<port;
    sendDatagram("ini", clientId, address, port);
}


//-----------Socket Methods-----------//

void MainWindow::initSocket(QHostAddress address, int port){
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(address, port);
    connect(udpSocket, &QUdpSocket::readyRead,
                this, &MainWindow::readPendingDatagrams);
    std::cout<<"Listening"<<std::endl;
}

void MainWindow::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;// = udpSocket->receiveDatagram();
        QHostAddress* address = new QHostAddress();

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), address);

        ServerStruct readData = *(ServerStruct *)datagram.data();
        std::cout<<"Read successfully "<<readData.command<<std::endl;
        if(!strcmp(readData.command, "ask")){
            qDebug()<<"ASK package";
            if(readData.checkSum==checkSum){
                qDebug()<<"Package got successfully";
            }
            else qDebug()<<"Package sending FAILED";

        }
    }

}

void MainWindow::sendDatagram(char command[], uint16_t id, QHostAddress address, int port){

    QByteArray datagram;
    char *idBytes = reinterpret_cast<char*>(&id);

    datagram.append(idBytes, 2);
    datagram.append(command, 4);

    if(!strcmp(command, "ini") && checkSum == 0)
        checkSum = makeCheckSum(datagram);
    qInfo()<<checkSum<<"Check sum is";

    udpSocket->writeDatagram(datagram, address, port);
    std::cout<<"Sent successfully"<<std::endl;

}

int MainWindow::makeCheckSum(QByteArray datagram){
    datagram = QCryptographicHash::hash(datagram, QCryptographicHash::Md5);
    return *(int*)datagram.data();
}
