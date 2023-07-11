#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <QCryptographicHash>
#include <Clientsettings.h>

typedef struct {
    char command[CMD_SIZE];
    int checkSum;
} ServerStruct;

#pragma pack(push, 1)

typedef struct {
    char command[CMD_SIZE];
    int checkSum;
    time_t currentTime;
    uint16_t cmdCount;
    uint64_t fullTime;
} StatStruct;

#pragma pack(pop)


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
    for(auto a: addresses)
    {
        QStringList slist = a.split(":");
        QHostAddress address = QHostAddress(slist.value(0));
        int port = slist.value(1).toInt();

        removeAddress(address, port);
        sendDatagram(END, clientId, address, port);
    }
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

void MainWindow::on_endSessionBtn_clicked()
{
    QString LEText = ui->lineEdit->text();
    QStringList slist = LEText.split(":");

    QHostAddress address = QHostAddress(slist.value(0));
    int port = slist.value(1).toInt();
    removeAddress(address, port);
    fillTable();
    sendDatagram(END, clientId, address, port);
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
        uint16_t* port = new uint16_t;

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), address, port);

        ServerStruct readData = *reinterpret_cast<ServerStruct *>(datagram.data());
        std::cout<<"Read successfully "<<readData.command<<std::endl;
        if(!strcmp(readData.command, ASK)){
            qDebug()<<"ASK package";
            if(readData.checkSum==checkSum && !isInit(address, port)){
                addAddress(address, port);
                fillTable();
                qDebug()<<"Package got successfully";
            }
            else qDebug()<<"Package sending FAILED";
        }

        if(!strcmp(readData.command, STAT)){
            StatStruct readData = *reinterpret_cast<StatStruct *>(datagram.data());
            ui->currentTimeLE->setText(std::asctime(std::localtime(&readData.currentTime)));
            ui->workingTimeLE->setText(QString::number(readData.fullTime));
            ui->commandLE->setText(QString::number(readData.cmdCount));
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

void MainWindow::addAddress(QHostAddress* address, uint16_t* port){
    QString fullAddress = address->toString() + ":" + QString::number(*port);

    if(!isInit(fullAddress))
        addresses.push_back(fullAddress);
}

void MainWindow::removeAddress(QHostAddress address, uint16_t port){
    QString fullAddress = address.toString() + ":" + QString::number(port);

    for(uint64_t i = 0; i < addresses.size(); i++){
        if(fullAddress == addresses[i]){
            addresses.erase(addresses.begin()+i);
            return;
        }
    }
}

bool MainWindow::isInit(QString address){

    for(auto x: addresses){
        if(address == x){
            return true;
        }
    }
    return false;
}

bool MainWindow::isInit(QHostAddress* address, uint16_t* port){
    QString fullAddress = address->toString() + ":" + QString::number(*port);
    for(auto x: addresses){
        if(fullAddress == x){
            return true;
        }
    }
    return false;
}

void MainWindow::fillTable(){
    QTableWidget *table = ui->sessionTable;
    table->clear(); table->setRowCount(0);
    for(auto address: addresses)
    {
        int rowCount = table->rowCount();
        table->insertRow(rowCount);
        ui->sessionTable->setItem(rowCount, 0, new QTableWidgetItem(QString::number(clientId)));
        ui->sessionTable->setItem(rowCount, 1, new QTableWidgetItem(address));
    }
}

