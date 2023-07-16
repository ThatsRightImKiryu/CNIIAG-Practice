#include "server.h"
#include "ui_server.h"
#include <QUdpSocket>
#include <QNetworkDatagram>
#include "iostream"
#include "string"
#include <QCryptographicHash>
#include <Serversettings.h>


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


short session_id;
QUdpSocket *udpSocket;

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    initSocket(networkSettings::ADDRESS,
               networkSettings::SERVER_PORT);
}

Server::~Server()
{
    delete ui;
    udpSocket->close();
    delete udpSocket;
}


//-----------Socket Methods-----------//

void Server::initSocket(QHostAddress address, int port){
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(address, port);

    connect(udpSocket, &QUdpSocket::readyRead,
                this, &Server::readPendingDatagrams);

    qDebug()<<"Server Listening on address="<<address<<":"<<port;
}

void Server::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {

        cmdCount++;

        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray datagramByte = datagram.data();

        cmdStruct  *readData = reinterpret_cast<cmdStruct *>(datagramByte.data());

        qDebug()<<"Read successfully "<<readData->command;
        for(auto x: sessions){
            qDebug()<<"SEssions"<<x;
        }

        chooseCmd(datagram, readData);

    }

}

void Server::sendDatagram(int checkSum, const char command[],
                          const QHostAddress address, const int port){
    //For STAT command
    QByteArray datagram;
    char *intBytes = reinterpret_cast<char*>(&checkSum);

    datagram.append(intBytes, sizeof(checkSum));
    datagram.append(command, strlen(command) + 1);

    udpSocket->writeDatagram(datagram, address, port);
    qDebug()<<"Sent successfully"<<command;
}

void Server::sendDatagram(int checkSum, const char command[],
                          std::time_t currentTime, std::time_t fullTime,
                          const QHostAddress address, const int port){
    //For other regular commands
    QByteArray datagram;

    char *intBytes = reinterpret_cast<char*>(&checkSum);
    datagram.append(intBytes, sizeof(checkSum));

    char *timeBytes = reinterpret_cast<char*>(&currentTime);
    datagram.append(timeBytes, sizeof(currentTime));

    char *cmdBytes = reinterpret_cast<char*>(&cmdCount);
    datagram.append(cmdBytes, sizeof(cmdCount));

    timeBytes = reinterpret_cast<char*>(&fullTime);
    datagram.append(timeBytes, sizeof(fullTime));

    datagram.append(togglesToByte());

    datagram.append(command, strlen(command) + 1);

    udpSocket->writeDatagram(datagram, address, port);
    qDebug()<<"Sent successfully "<<command;
}

//-----------Session Methods-----------//

void Server::addSession(uint16_t id){
    if(isInit(id)){
        qDebug()<<"Session WAS ALREADY inClientStructit";
    }
    else
    {
        sessions.push_back(id);
        qDebug()<<"Session IS init successfully";
    }
}

bool Server::isInit(int id){
    for(auto x: sessions){
        if(x == id){
            return true;
        }
    }
    return false;
}

//-----------Computing Methods-----------//

int Server::makeCheckSum(QByteArray &datagram){
    QByteArray hashedDatagram = QCryptographicHash::hash(datagram, QCryptographicHash::Md5);
    return *reinterpret_cast<int*>(hashedDatagram.data());
}



inline std::time_t Server::workingTime(std::time_t currentTime,
                               std::time_t startTime)
{
    return currentTime - startTime;
}

void Server::chooseCmd(QNetworkDatagram &datagram, cmdStruct *readData)
{
    QByteArray datagamBytes = datagram.data();
    int checkSum = makeCheckSum(datagamBytes);

    if(!qstrcmp(readData->command,     cmdSettings::INIT)){
        operateInit(datagram, readData, checkSum);
    }

    if(isInit(readData->id)){
        if(!qstrcmp(readData->command, cmdSettings::STAT)){
            operateStat(datagram, checkSum);
        }

        if(!qstrcmp(readData->command, cmdSettings::END)){
            operateEnd(readData);
        }
    }

}

void Server::operateInit(QNetworkDatagram &datagram, cmdStruct *readData, int checkSum)
{
    addSession(readData->id);
    sendDatagram(checkSum, cmdSettings::ASK, datagram.senderAddress(),
                 networkSettings::CLIENT_PORT);
}

void Server::operateStat(QNetworkDatagram &datagram, int checkSum)
{
    std::time_t currentTime = std::time(nullptr);
    sendDatagram(checkSum, cmdSettings::STAT,
                 currentTime, workingTime(currentTime, startTime),
                 datagram.senderAddress(), networkSettings::CLIENT_PORT);
}

void Server::operateEnd(cmdStruct *readData)
{
    for(uint64_t i = 0; i < sessions.size(); i++){
        if(sessions[i] == readData->id){
            sessions.erase(sessions.begin()+i);
            qDebug()<<"Session is destroyed"<<readData->id;
            return;
        }
    }
}

char Server::togglesToByte()
{
    byteToggles = 0;
    QList<QCheckBox *> toggles = ui->groupBox->findChildren<QCheckBox*>();
    for(int i = 0; i < toggles.size(); i++){
        if(toggles[i]->isChecked()) byteToggles |= (1 << i);
    }
    return byteToggles;
}
