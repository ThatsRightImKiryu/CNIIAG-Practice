#include "server.h"

#include <QUdpSocket>
#include <QNetworkDatagram>
#include "iostream"
#include "string"
#include <QCryptographicHash>
#include <Serversettings.h>

typedef struct {
    uint16_t id;
    char command[CMD_SIZE];
} ClientStruct;


short session_id;
QUdpSocket *udpSocket;


Server::Server(QHostAddress address, int port)
{
        initSocket(address, port);
}

Server::Server()
{
    Server(ADDRESS, SERVER_PORT);
}

Server::~Server()
{
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

        QByteArray datagram;// = udpSocket->receiveDatagram();
        QHostAddress* address = new QHostAddress();

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), address);

        ClientStruct readData = *reinterpret_cast<ClientStruct *>(datagram.data());
        std::cout<<"Read successfully "<<readData.command<<readData.id<<std::endl;

        int checkSum = makeCheckSum(datagram);

        if(!qstrcmp(readData.command, INIT)){
            addSession(readData.id);
            sendDatagram(checkSum, ASK, *address, CLIENT_PORT);
        }
        qDebug()<<"CHeck init and stat"<<isInit(readData.id)<<!qstrcmp(readData.command, STAT);
        if(isInit(readData.id) && !qstrcmp(readData.command, STAT)){
            std::time_t currentTime = std::time(nullptr);
            qDebug()<<"CHECK time"<<currentTime<< currentTime - startTime;
            sendDatagram(checkSum, STAT, currentTime, currentTime - startTime, *address, CLIENT_PORT);
        }
//        else std::cout<<"You need to init"<<std::endl;

    }

}

void Server::sendDatagram(int checkSum, char command[], QHostAddress address, int port){
    QByteArray datagram;
    char *intBytes = reinterpret_cast<char*>(&checkSum);
    datagram.append(command, CMD_SIZE);
    datagram.append(intBytes, sizeof(checkSum));

    udpSocket->writeDatagram(datagram, address, port);
    std::cout<<"Sent successfully "<<command<<std::endl;
}

void Server::sendDatagram(int checkSum, char command[],  std::time_t currentTime,
                          std::time_t fullTime, QHostAddress address, int port){
    QByteArray datagram;

    char *intBytes = reinterpret_cast<char*>(&checkSum);
    datagram.append(command, CMD_SIZE);
    datagram.append(intBytes, sizeof(checkSum));

    char *time = reinterpret_cast<char*>(&currentTime);
    datagram.append(time, sizeof(currentTime));

    time = reinterpret_cast<char*>(&fullTime);
    datagram.append(time, sizeof(fullTime));

    udpSocket->writeDatagram(datagram, address, port);
    std::cout<<"Sent successfully "<<command<<std::endl;
}


void Server::addSession(int id){
    if(isInit(id)){
        std::cout<<"Session WAS ALREADY init"<<std::endl;
    }
    else
    {
        sessions.push_back(id);
        std::cout<<"Session IS init successfully"<<std::endl;
    }
}

int Server::makeCheckSum(QByteArray datagram){
    datagram = QCryptographicHash::hash(datagram, QCryptographicHash::Md5);
    return *reinterpret_cast<int*>(datagram.data());;
}

bool Server::isInit(int id){
    for(auto x: sessions){
        if(x == id){
            return true;
        }
    }
    return false;
}

