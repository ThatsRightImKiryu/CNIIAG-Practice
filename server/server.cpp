#include "server.h"

#include <QUdpSocket>
#include <QNetworkDatagram>
#include "iostream"
#include "string"
#include <QCryptographicHash>
#include <Serversettings.h>

typedef struct {
    uint16_t id;
    char command[4];
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

    qDebug()<<"Server Listening on address="<<address<<":"<<port<<udpSocket;
}

void Server::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;// = udpSocket->receiveDatagram();
        QHostAddress* address = new QHostAddress();

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), address);
        ClientStruct readData = *(ClientStruct *)datagram.data();

        std::cout<<"Read successfully "<<readData.command<<readData.id<<std::endl;
        qDebug() << datagram.data();
        if(!qstrcmp(readData.command, "ini")){
            int checkSum = makeCheckSum(datagram);
            addSession(checkSum);
            sendDatagram(checkSum, "ask", *address, CLIENT_PORT);
        }
    }

}

void Server::sendDatagram(int checkSum, char command[], QHostAddress address, int port){
    QByteArray datagram;
    char *intBytes = (char *)&checkSum;
    datagram.append(command, 4);
    datagram.append(intBytes, 4);

    udpSocket->writeDatagram(datagram, address, port);
    std::cout<<"Sent successfully"<<std::endl;
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
    return *(int*)datagram.data();
}
