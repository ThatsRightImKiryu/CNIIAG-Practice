#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <QCryptographicHash>
#include <Clientsettings.h>
typedef struct {
    char command[CMD_SIZE];
    int checkSum;
} ServerStruct;

typedef struct {
    char command[CMD_SIZE];
    int checkSum;
    time_t currentTime;
    uint64_t fullTime;
} StatStruct;

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

    sendDatagram(INIT, clientId, address, port);
}

void MainWindow::on_statBtn_clicked()
{
    QString LEText = ui->lineEdit->text();
    QStringList slist = LEText.split(":");

    QHostAddress address = QHostAddress(slist.value(0));
    int port = slist.value(1).toInt();

    sendDatagram(STAT, clientId, address, port);
}


//-----------Socket Methods-----------//

void MainWindow::initSocket(QHostAddress address, int port){
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(address, port);
    connect(udpSocket, &QUdpSocket::readyRead,
                this, &MainWindow::readPendingDatagrams);
    qInfo()<<"Listening client on "<<address<<port;
}

void MainWindow::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;// = udpSocket->receiveDatagram();
        QHostAddress* address = new QHostAddress();

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), address);

        ServerStruct readData = *reinterpret_cast<ServerStruct *>(datagram.data());
        std::cout<<"Read successfully "<<readData.command<<std::endl;
        if(!strcmp(readData.command, ASK)){
            qDebug()<<"ASK package";
            if(readData.checkSum==checkSum){
                qDebug()<<"Package got successfully";
            }
            else qDebug()<<"Package sending FAILED";
        }

        if(!strcmp(readData.command, STAT)){
            StatStruct readData = *reinterpret_cast<StatStruct *>(datagram.data());
            ui->currentTimeLE->setText(std::asctime(std::localtime(&readData.currentTime)));
            ui->workingTimeLE->setText(QString::number(readData.fullTime));

            qDebug()<<"STAT package"<<readData.currentTime<<readData.fullTime<<datagram.data();
        }
    }

}

void MainWindow::sendDatagram(char command[], uint16_t id, QHostAddress address, int port){

    QByteArray datagram;
    char *idBytes = reinterpret_cast<char*>(&id);

    datagram.append(idBytes, sizeof(id));
    datagram.append(command, CMD_SIZE);

    if(!strcmp(command, INIT) && !checkSum)
        checkSum = makeCheckSum(datagram);

    udpSocket->writeDatagram(datagram, address, port);
    std::cout<<"Sent successfully "<<command<<std::endl;

}

int MainWindow::makeCheckSum(QByteArray datagram){
    datagram = QCryptographicHash::hash(datagram, QCryptographicHash::Md5);
    return *reinterpret_cast<int*>(datagram.data());
}


