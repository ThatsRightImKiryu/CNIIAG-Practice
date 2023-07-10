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
        QByteArray datagram;// = udpSocket->receiveDatagram();
        QHostAddress* address = new QHostAddress();

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), address);

        ClientStruct readData = *reinterpret_cast<ClientStruct *>(datagram.data());
        std::cout<<"Read successfully "<<readData.command<<readData.id<<std::endl;
        if(!qstrcmp(readData.command, INIT)){
            int checkSum = makeCheckSum(datagram);
            addSession(checkSum);
            sendDatagram(checkSum, ASK, *address, CLIENT_PORT);
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

void Server::addSession(int checkSum){
    for(auto x: sessions){
        if(x == checkSum){
            std::cout<<"Session WAS ALREADY init"<<std::endl;
            return;
        }
    }
    sessions.push_back(checkSum);
    std::cout<<"Session IS init successfully"<<std::endl;
}

int Server::makeCheckSum(QByteArray datagram){
    datagram = QCryptographicHash::hash(datagram, QCryptographicHash::Md5);
    return *reinterpret_cast<int*>(datagram.data());;
}
