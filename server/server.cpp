#include "server.h"
#include "ui_server.h"
#include <QUdpSocket>
#include <QNetworkDatagram>
#include "iostream"
#include <QCryptographicHash>
#include <Serversettings.h>
#include <charsetconv.h>

short session_id;
QUdpSocket *udpSocket;

/*!
 \class Server::Server(QWidget *parent)

 \brief Consrtucotr for initialize socket and visual part of server
 */
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

/*!
 \class void Server::initSocket(QHostAddress address, int port)

 \brief Method to bind udpSocket using address and port
        and pending datagrams
 */
void Server::initSocket(QHostAddress address, int port)
{

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(address, port);

    connect(udpSocket, &QUdpSocket::readyRead,
                this, &Server::readPendingDatagrams);

    qDebug()<<"Server Listening on address="<<address<<":"<<port;
}

/*!
 * \brief Server::readPendingDatagrams
 * wating udpDatagram to read using cmdStruct.
 * if data includes form of cmdStruct
 * methd initialize client.
 * If it is -> check if command is status requset
 * when client if authorized via void Server::readPendingDatagrams().
 */
void Server::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {

        cmdCount++;

        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray datagramByte = datagram.data();

        cmdStruct  *readData = reinterpret_cast<cmdStruct *>(datagramByte.data());

        qDebug()<<"Read successfully "<<readData->command<<readData->id;

        chooseCmd(datagram, readData);

    }

}

/*!
 * \brief Server::sendDatagram
 * is for sending regular packages like init
 * using cmdStruct
 */
void Server::sendDatagram(int checkSum, const char command[],
                          const QHostAddress address, const int port){
    QByteArray datagram;
    char *intBytes = reinterpret_cast<char*>(&checkSum);

    datagram.append(intBytes, sizeof(checkSum));
    datagram.append(command, strlen(command) + 1);

    udpSocket->writeDatagram(datagram, address, port);
    qDebug()<<"Sent successfully"<<command;
}

/*!
 * \brief Method is for sending packages formed like
 * using statStruct
 */

void Server::sendDatagram(int checkSum, const char command[],
                          std::time_t currentTime, std::time_t fullTime,
                          const QHostAddress address, const int port)
{
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

    char errorsList[100]{'\0'};

    makeErrorsPackage(errorsList);

    datagram.append(errorsList, strlen(errorsList));

    datagram.append(command, strlen(command) + 1);

    udpSocket->writeDatagram(datagram, address, port);
    qDebug()<<"Sent successfully "<<datagram.data();
}

//-----------Session Methods-----------//

/*!
 * \brief Server::addSession
 * get session_id and check if it is inititalized
 * and add it if not
 */
void Server::addSession(uint16_t id){
    if(isInit(id)){
        qDebug()<<"Session WAS ALREADY inClientStructit";
    }
    else
    {
        sessions.insert(id);
        qDebug()<<"Session IS init successfully";
    }
}

bool Server::isInit(int id){
    return sessions.contains(id);
}

//-----------Computing Methods-----------//

/*!
 * \brief Server::makeCheckSum
 * make crc of initializing datagram package
 * and hash it to 4 bytes
 */
int Server::makeCheckSum(QByteArray &datagram){
    QByteArray hashedDatagram = QCryptographicHash::hash(datagram, QCryptographicHash::Md5);
    return *reinterpret_cast<int*>(hashedDatagram.data());
}


/*!
 * \brief Server::workingTime
 * if for status packages
 */
inline std::time_t Server::workingTime(std::time_t currentTime,
                               std::time_t startTime)
{
    return currentTime - startTime;
}

/*!
 * \brief Server::chooseCmd
 * choose what to do with package
 * due to package data
 */
void Server::chooseCmd(QNetworkDatagram &datagram, cmdStruct *readData)
{
    QByteArray datagamBytes = datagram.data();
    int checkSum = makeCheckSum(datagamBytes);

    if(!qstrcmp(readData->command,     cmdSettings::INIT)){
        sendInit(datagram, readData, checkSum);
    }

    if(isInit(readData->id)){
        if(!qstrcmp(readData->command, cmdSettings::STAT)){
            sendStat(datagram, checkSum);
        }

        if(!qstrcmp(readData->command, cmdSettings::END)){
            readEnd(readData);
            sendEnd(datagram, checkSum);
        }
    }

}

void Server::sendInit(QNetworkDatagram &datagram, cmdStruct *readData, int checkSum)
{
    addSession(readData->id);
    sendDatagram(checkSum, cmdSettings::ASK, datagram.senderAddress(),
                 networkSettings::CLIENT_PORT);
}

void Server::sendStat(QNetworkDatagram &datagram, int checkSum)
{
    std::time_t currentTime = std::time(nullptr);
    sendDatagram(checkSum, cmdSettings::STAT,
                 currentTime, workingTime(currentTime, startTime),
                 datagram.senderAddress(), networkSettings::CLIENT_PORT);
}

void Server::sendEnd(QNetworkDatagram &datagram, int checkSum)
{
    sendDatagram(checkSum, cmdSettings::END, datagram.senderAddress(),
                 networkSettings::CLIENT_PORT);
}

void Server::readEnd(cmdStruct *readData)
{
    sessions.remove(readData->id);
    qDebug()<<"Session is destroyed"<<readData->id;
}

char Server::togglesToByte()
{
    byteToggles = 0;
    QList<QCheckBox *> toggles = ui->groupBox->findChildren<QCheckBox*>();
    for(int i = 0; i < toggles.size(); i++)
    {
        if(toggles[i]->isChecked()) byteToggles |= (1 << i);
    }    
    return byteToggles;
}

void Server::makeErrorsPackage(char * charStr)
{
    QList<QCheckBox *> errToggles = ui->groupBox_err->findChildren<QCheckBox*>();
    const char* errorWord = "ошибка";
    const char* okWord = "испр.#";
    char resStr[100]{'\0'};

    for(auto et: errToggles)
    {
        if( et->isChecked() )
            strncat(resStr, errorWord, strlen(errorWord));
        else
            strncat(resStr, okWord, strlen(errorWord));
    }

    charSetConv conv;
    char KOI7ResStr[100]{'\0'}, compressedResStr[100]{'\0'};

    conv.fromUTF8toKOI7(resStr, KOI7ResStr);
    conv.compress8To7bits(KOI7ResStr, compressedResStr);

    qstrcpy(charStr, compressedResStr);
}
