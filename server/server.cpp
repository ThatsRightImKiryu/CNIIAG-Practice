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
    initSocket(ADDRESS, SERVER_PORT);
}

Server::~Server()
{
    udpSocket->close();
    delete udpSocket;
}


//-----------Socket Methods-----------//

void Server::initSocket(QHostAddress address, int port){
    udpSocket = new QUdpSocket(this);
    qDebug()<<"CHECK BIND"<<udpSocket->bind(address, port);
    connect(udpSocket, &QUdpSocket::readyRead,
                this, &Server::readPendingDatagrams);

    qDebug()<<"Server Listening on address="<<address<<":"<<port;
}

void Server::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {

        cmdCount++;

        QByteArray datagram; // = udpSocket->receiveDatagram();
        QHostAddress* address = new QHostAddress();

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), address);

        ClientStruct readData = *reinterpret_cast<ClientStruct *>(datagram.data());
        std::cout<<"Read successfully "<<readData.command<<readData.id<<std::endl;
        for(auto x: sessions){
            qDebug()<<"SEssions"<<x;
        }

        int checkSum = makeCheckSum(datagram);

        if(!qstrcmp(readData.command, INIT)){
            addSession(readData.id);
            sendDatagram(checkSum, ASK, *address, CLIENT_PORT);
        }
        if(isInit(readData.id) && !qstrcmp(readData.command, STAT)){
            std::time_t currentTime = std::time(nullptr);
            sendDatagram(checkSum, STAT, currentTime, currentTime - startTime, *address, CLIENT_PORT);
        }

        if(isInit(readData.id) && !qstrcmp(readData.command, END)){
            for(uint64_t i = 0; i < sessions.size(); i++){
                if(sessions[i] == readData.id){
                    sessions.erase(sessions.begin()+i);
                    qDebug()<<"Session is destroyed"<<readData.id;
                    return;
                }
            }
        }

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

    char *cmdBytes = reinterpret_cast<char*>(&cmdCount);
    datagram.append(cmdBytes, sizeof(cmdCount));

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

