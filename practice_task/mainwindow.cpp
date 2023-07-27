#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCryptographicHash>

#include <Clientsettings.h>
#include <charsetconv.h>
#include <constants.h>

namespace labels
{
    const char *TOGGLE_ON = "ON";
    const char *TOGGLE_OFF = "OFF";
    const char *TOGGLE_OK = "Correct";
    const char *TOGGLE_INVALID = "INVALID";
}

namespace deviceStates
{
//STATES
    const char *TOGGLE_OK = "испр.#";
    const char *TOGGLE_INVALID = "ошибка";
//SIZES
    const int TOGGLE_OK_SIZE = strlen(TOGGLE_OK);
    const int TOGGLE_INVALID_SIZE = strlen(TOGGLE_INVALID);
    const int MAX_STATE_SIZE = 13;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setClientId();
    initSocket(networkSettings::ADDRESS,
               networkSettings::CLIENT_PORT);
}
MainWindow::~MainWindow()
{
    destroyAllSessions();

    udpSocket->close();
    delete udpSocket;
    delete ui;
}

void MainWindow::destroyAllSessions()
{
    for(auto a: addresses)
    {
        QHostAddress address = getAddressFromQStr(a);
        int port = getPortFromQStr(a);

        sendEnd(address, port);
    }

}
//---------------------------------"Front" Methods---------------------------------//


void MainWindow::fillAddressTable(){
    QTableWidget *table = ui->sessionTable;

    setAddressTableToDefault(table);

    for(auto address: addresses)
    {
        int rowCount = table->rowCount();
        table->insertRow(rowCount);
        ui->sessionTable->setItem(rowCount, 0, new QTableWidgetItem(QString::number(clientId)));
        ui->sessionTable->setItem(rowCount, 1, new QTableWidgetItem(address));
    }
}

void MainWindow::setAddressTableToDefault(QTableWidget *table)
{
    table->clear(); table->setRowCount(0);
    QStringList headers = {"Session id","Server address"};
    table->setHorizontalHeaderLabels(headers);
}

//---------------------------------Private Slots---------------------------------//

void MainWindow::on_initPushButton_clicked()
{
    QHostAddress address;
    int port;
    setAddressAndPortFromLineEdit(address, port);

    sendDatagram(prepareDatagram(cmdSettings::INIT, clientId),
                 address, port);
}

void MainWindow::on_statBtn_clicked()
{
    QHostAddress address;
    int port;
    setAddressAndPortFromLineEdit(address, port);

    sendDatagram(prepareDatagram(cmdSettings::STAT, clientId),
                 address, port);
}

void MainWindow::on_endSessionBtn_clicked()
{
    QHostAddress address;
    int port;
    setAddressAndPortFromLineEdit(address, port);

    sendEnd(address, port);
}

void MainWindow::on_sessionTable_cellDoubleClicked(int row)
{
    QString address = ui->sessionTable->item(row, 1)->text();
    ui->addressLineEdit->setText(address);
}



//---------------------------------Socket Methods---------------------------------//

void MainWindow::setClientId()
{
    /*!
     * Max value of type due to client id type.
     * For example: sizeof(uint16_t clientId) == 65536
    */
    uint64_t maxClientId = 1;
    maxClientId <<= (sizeof(clientId)*8 - 1);
    srand(time(nullptr));
    clientId = rand() % maxClientId;
    qDebug()<<"ID"<<clientId;

}
void MainWindow::initSocket(QHostAddress address, int port)
{
    udpSocket = new QUdpSocket(this);
    if(!udpSocket->bind(address, port))
        qDebug()<<"Binding FAILED"<<address<<port;
    else
    {
        if(connect(udpSocket, &QUdpSocket::readyRead,
                    this, &MainWindow::readPendingDatagrams))
            qDebug()<<"Listening client on "<<address<<port;
        else
            qDebug()<<"Listening FAILED "<<address<<port;
    }

}

void MainWindow::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {

        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray datagramByte = datagram.data();

        cmdStruct *readData = reinterpret_cast<cmdStruct *>(datagramByte.data());
        qDebug()<<"Read successfully ";

        //show package size
        ui->lineEdit_pkgSize->setText(QString::number(datagram.data().size()));

        chooseCmd(datagram.senderAddress(), datagram.senderPort(), readData);
    }

}

void MainWindow::sendDatagram(QByteArray datagramByte,
                              const QHostAddress address, const int port)
{
    udpSocket->writeDatagram(datagramByte, address, port);
}


uint16_t MainWindow::makeCheckSum(QByteArray &datagramByte)
{
    uint16_t *word = reinterpret_cast<uint16_t *>(datagramByte.data());
    uint16_t checkSum = 0;

    for(int i = 0; i < datagramByte.size() / 2 + datagramByte.size() % 2; i++)
        checkSum += *(word++);
    qDebug()<<"SIZE DATA"<<datagramByte.size()<<datagramByte;

    return ~checkSum;
}


//---------------------------------"Front" Methods---------------------------------//

void MainWindow::setByteToToggles(uint8_t byteToggles)
{
    QList<QLineEdit *> lineEdits = ui->groupBox_toggle->findChildren<QLineEdit*>();
    for(auto le: lineEdits)
    {
       if(byteToggles % 2)
           le->setText(labels::TOGGLE_ON);
       else
           le->setText(labels::TOGGLE_OFF);
       byteToggles /= 2;
    }
}


void MainWindow::setErrors(char errorList[])
{

    QList<QLineEdit *> errLineEdits = ui->groupBox_err->findChildren<QLineEdit*>();
    int i = 0;
    for(auto ele: errLineEdits)
    {
        char error[deviceStates::MAX_STATE_SIZE]{'\0'};
        memcpy(error, errorList+i, deviceStates::TOGGLE_OK_SIZE);
        if(!qstrcmp(error, deviceStates::TOGGLE_OK))
        {
            ele->setText(labels::TOGGLE_OK);
            i += deviceStates::TOGGLE_OK_SIZE;
            continue;
        }

        memcpy(error, errorList+i, deviceStates::TOGGLE_INVALID_SIZE);
        if(!qstrcmp(error, deviceStates::TOGGLE_INVALID))
        {
            ele->setText(labels::TOGGLE_INVALID);
            i += deviceStates::TOGGLE_INVALID_SIZE;
        }
    }
}

void MainWindow::setProcessedToggles(char *errorList, char byteToggles)
{

    char decompressedErrors[ERROR_DECOMPRESSED_SIZE +1]{'\0'},
         errorsRes[ERROR_CONVERTED_SIZE + 1]{'\0'};
    charSetConv conv;

    setByteToToggles(byteToggles);

    conv.decompress7To8bits(prepareErrorList(errorList), decompressedErrors);
    conv.fromKOI7toUTF8(decompressedErrors, errorsRes);
    setErrors(errorsRes);

}

void MainWindow::setMajorData(uint16_t cmdCount,time_t currentTime, uint64_t fullTime)
{
    ui->currentTimeLE->setText(std::asctime(std::localtime(&currentTime)));
    ui->workingTimeLE->setText(QString::number(fullTime));
    ui->commandLE->setText(QString::number(cmdCount));
}

void MainWindow::clearWindow()
{
    QList<QGroupBox *> groupBoxes = ui->centralwidget->findChildren<QGroupBox *>();
    for(auto gb: groupBoxes)
    {
        clearQLineEditsFromGroupBox(gb);
    }

}

void MainWindow::clearQLineEditsFromGroupBox(QGroupBox * groupBox)
{
    QList<QLineEdit *> lineEdits = groupBox->findChildren<QLineEdit *>();
    for(auto le: lineEdits)
    {
        le->clear();
    }
};

//---------------------------------Session Methods---------------------------------//

void MainWindow::addAddress(QHostAddress address, int port){
    QString fullAddress = address.toString() + ":" + QString::number(port);

    if(!isInit(fullAddress))
        addresses.insert(fullAddress);
}

void MainWindow::removeAddress(QString fullAddress){
    if(addresses.remove(fullAddress))
        qDebug()<<"Session successfully destroyed";
    else
        qDebug()<<"Session destroy FAILED";

}

void MainWindow::removeAddress(QHostAddress address, int port){
    QString fullAddress = makeFullAddress(address, port);

    removeAddress(fullAddress);
}


bool MainWindow::isInit(QString address){
   return addresses.contains(address);
}

bool MainWindow::isInit(QHostAddress address, int port){
    QString fullAddress = makeFullAddress(address, port);

    return isInit(fullAddress);
}

void MainWindow::chooseCmd(QHostAddress address, int port, cmdStruct *readData)
{
    if(!qstrcmp(readData->command, cmdSettings::ASK))
        return readAsk(address, port, readData->checkSum);

    if(!qstrcmp(readData->command, cmdSettings::END))
    {
        QString fullAddress = makeFullAddress(address, port);
        return readEnd(fullAddress);
    }

    /*!
     * \brief readStatData is a reinterpreted to statistics
     * package of old data
     */
    StatStruct *readStatData = reinterpret_cast<StatStruct *>(readData);
    if(!qstrcmp(readStatData->command, cmdSettings::STAT))
        readStat(*readStatData);

}

QByteArray MainWindow::prepareDatagram(const char command[], uint16_t id)
{
    QByteArray datagramByte;
    char *idBytes = reinterpret_cast<char*>(&id);

    datagramByte.append(idBytes, sizeof(id));
    datagramByte.append(command, strlen(command));

    if(!qstrcmp(command, cmdSettings::INIT) && !checkSum)
        checkSum = makeCheckSum(datagramByte);

    qDebug()<<"Sending"<<command;

    return datagramByte;
}

void MainWindow::readStat(StatStruct &readStatData)
{   
   setMajorData(readStatData.cmdCount, readStatData.currentTime, readStatData.fullTime);
   setProcessedToggles(readStatData.errorList, readStatData.byteToggles);
}

void MainWindow::readAsk(QHostAddress address, int port, uint16_t pkgCheckSum)
{
    if(pkgCheckSum==checkSum && //crc==got_from_package and init
           !isInit(address, port))
    {
        addAddress(address, port);

        clearWindow();
        fillAddressTable();
        qDebug()<<"Package got successfully";
    }
    else qDebug()<<"Package getting FAILED";
}

void MainWindow::readEnd(QString fullAddress)
{
    removeAddress(fullAddress);

    fillAddressTable();
    clearWindow();
}

void MainWindow::sendEnd(QHostAddress address, int port)
{
    sendDatagram(prepareDatagram(cmdSettings::END, clientId),
                 address, port);
}

inline QString MainWindow::makeFullAddress(QHostAddress address, int port)
{
    return address.toString() + ":" + QString::number(port);
}

void MainWindow::setAddressAndPortFromLineEdit(QHostAddress &address, int &port)
{
    QString AddrLEText = ui->addressLineEdit->text();
    address = getAddressFromQStr(AddrLEText);
    port = getPortFromQStr(AddrLEText);
}

QHostAddress MainWindow::getAddressFromQStr(QString fullAddress)
{
    QStringList slist = fullAddress.split(":");
    return QHostAddress(slist.value(0));
}

int MainWindow::getPortFromQStr(QString fullAddress)
{
    QStringList slist = fullAddress.split(":");
    return slist.value(1).toInt();
}

inline char* MainWindow::prepareErrorList(char* errorList)
{
    return (errorList[ERROR_LIST_SIZE] = '\0', errorList);
}
