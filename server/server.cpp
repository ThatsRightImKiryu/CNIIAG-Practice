#include "server.h"
#include "ui_server.h"
#include <QUdpSocket>
#include <QNetworkDatagram>
#include "iostream"
#include <QCryptographicHash>
#include <Serversettings.h>
#include <charsetconv.h>

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
    if(!udpSocket->bind(address, port))
        qDebug()<<"Binding FAILED"<<address<<port;
    else
    {
        if(connect(udpSocket, &QUdpSocket::readyRead,
                    this, &Server::readPendingDatagrams))
            qDebug()<<"Listening client on "<<address<<port;
        else
            qDebug()<<"Listening FAILED "<<address<<port;
    }
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
        chooseCmd(readData, makeCheckSum(datagramByte), datagram.senderAddress(), networkSettings::CLIENT_PORT);
    }
}

/*!
 * \brief Server::sendDatagram
 * is for sending regular packages like init
 * using cmdStruct
 */
QByteArray Server::prepareSimplePackage(const char *command, int checkSum)
{
    QByteArray datagramByte;
    char *intBytes = reinterpret_cast<char*>(&checkSum);

    datagramByte.append(intBytes, sizeof(checkSum));
    datagramByte.append(command, strlen(command) + 1);

    return datagramByte;
}

/*!
 * \brief Method is for sending packages formed like
 * using statStruct
 */

QByteArray Server::prepareStatPackage(const char command[], int checkSum)
{
    QByteArray datagramByte;

    char *intBytes = reinterpret_cast<char*>(&checkSum);
    datagramByte.append(intBytes, sizeof(checkSum));

    std::time_t currentTime = time(nullptr);
    char *timeBytes = reinterpret_cast<char*>(&currentTime);
    datagramByte.append(timeBytes, sizeof(currentTime));

    char *cmdBytes = reinterpret_cast<char*>(&cmdCount);
    datagramByte.append(cmdBytes, sizeof(cmdCount));

    std::time_t workingTimeVar = workingTime(currentTime, startTime);
    timeBytes = reinterpret_cast<char*>(&workingTimeVar);
    datagramByte.append(timeBytes, sizeof(workingTimeVar));

    datagramByte.append(togglesToByte());

    char errorsList[100]{'\0'};
    makeErrorsPackage(errorsList);
    datagramByte.append(errorsList, strlen(errorsList));
    datagramByte.append(command, strlen(command) + 1);

    return datagramByte;
}

//-----------Session Methods-----------//

/*!
 * \brief Server::addSession
 * get session_id and check if it is inititalized
 * and add it if not
 */
void Server::addSession(uint16_t id){
    if(isInit(id)){
        qDebug()<<"Session WAS ALREADY";
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
void Server::chooseCmd(cmdStruct *readData, int checkSum,
                       QHostAddress address, int port)
{
    QByteArray datagramSendBytes;

    if(!qstrcmp(readData->command,     cmdSettings::INIT))
    {
        addSession(readData->id);
        datagramSendBytes =
                prepareSimplePackage(cmdSettings::ASK, checkSum);
    }

    if(isInit(readData->id)){
        if(!qstrcmp(readData->command, cmdSettings::STAT))
            datagramSendBytes =
                    prepareStatPackage(cmdSettings::STAT, checkSum);

        if(!qstrcmp(readData->command, cmdSettings::END)){
            readEnd(readData);
            datagramSendBytes =
                    prepareSimplePackage(cmdSettings::END, checkSum);
        }
    }

    if(datagramSendBytes.data())
    {
        udpSocket->writeDatagram(datagramSendBytes, address, port);
    }

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

void Server::makeErrorsPackage(char * resStr)
{
    QList<QCheckBox *> errToggles = ui->groupBox_err->findChildren<QCheckBox*>();

    for(auto et: errToggles)
    {
        if( et->isChecked() )
            strncat(resStr, ERROR_WORD, strlen(ERROR_WORD));
        else
            strncat(resStr, OK_WORD, strlen(OK_WORD));
    }

    charSetConv conv;
    char KOI7ResStr[100]{'\0'};

    conv.fromUTF8toKOI7(resStr, KOI7ResStr);
    conv.compress8To7bits(KOI7ResStr, resStr);

}
