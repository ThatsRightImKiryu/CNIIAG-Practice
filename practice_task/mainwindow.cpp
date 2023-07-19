#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <QCryptographicHash>
#include <Clientsettings.h>
#include <charsetconv.h>

namespace labels
{
    const char *TOGGLE_ON = "ВКЛ.";
    const char *TOGGLE_OFF = "ВЫКЛ.";
    const char *TOGGLE_OK = "Исправно";
    const char *TOGGLE_FAIL = "Не работает";

}
short session_id;
QUdpSocket *udpSocket;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(nullptr));
    clientId = rand() % 65536;

    initSocket(networkSettings::ADDRESS, networkSettings::CLIENT_PORT);
}
MainWindow::~MainWindow()
{
    for(auto a: addresses)
    {
        QHostAddress address = getAddressFromQStr(a);
        int port = getPortFromQStr(a);

        removeAddress(address, port);
        sendDatagram(cmdSettings::END, clientId, address, port);
    }
    udpSocket->close();
    delete udpSocket;
    delete ui;
}
//---------------------------------Slot and "front" Methods---------------------------------//


void MainWindow::on_pushButton_clicked()
{
    QString LEText = ui->lineEdit->text();

    sendDatagram(cmdSettings::INIT, clientId, getAddressFromQStr(LEText), getPortFromQStr(LEText));
}

void MainWindow::on_statBtn_clicked()
{
    QString LEText = ui->lineEdit->text();

    QHostAddress address = getAddressFromQStr(LEText);
    int port = getPortFromQStr(LEText);

    clearWindow();
    sendDatagram(cmdSettings::STAT, clientId, address, port);
}

void MainWindow::on_endSessionBtn_clicked()
{
    sendEnd();
}

void MainWindow::on_sessionTable_cellDoubleClicked(int row)
{
    QString address = ui->sessionTable->item(row, 1)->text();
    ui->lineEdit->setText(address);
}


void MainWindow::fillTable(){
    QTableWidget *table = ui->sessionTable;

    //Set table to default
    table->clear(); table->setRowCount(0);
    QStringList headers = {"Session id","Server address"};
    table->setHorizontalHeaderLabels(headers);

    //filling table
    for(auto address: addresses)
    {
        int rowCount = table->rowCount();
        table->insertRow(rowCount);
        ui->sessionTable->setItem(rowCount, 0, new QTableWidgetItem(QString::number(clientId)));
        ui->sessionTable->setItem(rowCount, 1, new QTableWidgetItem(address));
    }
}


//---------------------------------Socket Methods---------------------------------//

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

        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray datagramByte = datagram.data();

        cmdStruct *readData = reinterpret_cast<cmdStruct *>(datagramByte.data());
        qDebug()<<"Read successfully "<<readData->command;

        chooseCmd(datagram, readData);
    }

}

void MainWindow::sendDatagram(const char command[], uint16_t id,
                              const QHostAddress address, const int port){

    QByteArray datagram;
    char *idBytes = reinterpret_cast<char*>(&id);

    datagram.append(idBytes, sizeof(id));
    datagram.append(command, strlen(command) + 1);

    if(!strcmp(command, cmdSettings::INIT) && !checkSum)
        checkSum = makeCheckSum(datagram);

    udpSocket->writeDatagram(datagram, address, port);
    qDebug()<<"Sent successfully "<<command;

}

//---------------------------------Computing Methods---------------------------------//

int MainWindow::makeCheckSum(QByteArray &datagram){
    QByteArray hashedDatagram = QCryptographicHash::hash(datagram, QCryptographicHash::Md5);
    return *reinterpret_cast<int*>(hashedDatagram.data());
}

void MainWindow::byteToToggles(uint8_t byteToggles)
{
    QList<QLineEdit *> lineEdits = ui->groupBox_err->findChildren<QLineEdit*>();
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
    char *error = new char[7]{'\0'};
    for(int i = 0; i < errLineEdits.size(); i++)
    {
      strncpy(error, errorList+i*6, 6);
      if(!qstrcmp(error, "испр.#"))
      {
          errLineEdits[i]->setText(labels::TOGGLE_OK);
      }
      if(!qstrcmp(error, "ошибка"))
      {
          errLineEdits[i]->setText(labels::TOGGLE_FAIL);
      }
    }
    delete[] error;
}

void MainWindow::clearWindow()
{
    QList<QLineEdit*> gbLineEdits = ui->StatusGroupBox->findChildren<QLineEdit*>();
    for(auto le: gbLineEdits)
    {
        le->clear();
    }

    QList<QLineEdit *> toggles = ui->groupBox_toggle->findChildren<QLineEdit*>();
    for(auto t: toggles)
    {
        t->clear();
    }

    QList<QLineEdit *> errToggles = ui->groupBox_err->findChildren<QLineEdit*>();
    for(auto et: toggles)
    {
        et->clear();
    }
}

//---------------------------------Session Methods---------------------------------//

void MainWindow::addAddress(QHostAddress address, int port){
    QString fullAddress = address.toString() + ":" + QString::number(port);

    if(!isInit(fullAddress))
        addresses.insert(fullAddress);
}

void MainWindow::removeAddress(QHostAddress address, int port){
    QString fullAddress = address.toString() + ":" + QString::number(port);

    addresses.remove(fullAddress);
}

bool MainWindow::isInit(QString address){
   return addresses.contains(address);
}

bool MainWindow::isInit(QHostAddress address, int port){
    QString fullAddress = address.toString() + ":" + QString::number(port);

    return isInit(fullAddress);
}

void MainWindow::chooseCmd(QNetworkDatagram &datagram, cmdStruct *readData)
{
    ui->lineEdit_pkgSize->setText(QString::number(datagram.data().size()));

    if(!qstrcmp(readData->command, cmdSettings::ASK))
    {
        readAsk(datagram, readData);
    }

    StatStruct *readStatData = reinterpret_cast<StatStruct *>(datagram.data().data());
    if(!qstrcmp(readStatData->command, cmdSettings::STAT))
    {
        readStat(readStatData);
    }

}

void MainWindow::readStat(StatStruct *readStatData)
{
    ui->currentTimeLE->setText(std::asctime(std::localtime(&readStatData->currentTime)));
    ui->workingTimeLE->setText(QString::number(readStatData->fullTime));
    ui->commandLE->setText(QString::number(readStatData->cmdCount));
    byteToToggles(readStatData->byteToggles);
    charSetConv utf8_str(readStatData->errorList);
//    setErrors(utf8_str.toUTF8());
    qDebug()<<"STAT package"<<utf8_str.toUTF8();
}


void MainWindow::readAsk(QNetworkDatagram &datagram, cmdStruct *readData)
{
    qDebug()<<"ASK package";
    if(readData->checkSum==checkSum && //crc==got_from_package and init
           !isInit(datagram.senderAddress(), datagram.senderPort()))
    {
        addAddress(datagram.senderAddress(), datagram.senderPort());
        fillTable();
        qDebug()<<"Package got successfully";
    }
    else qDebug()<<"Package sending FAILED";
}

void MainWindow::sendEnd()
{
    QString LEText = ui->lineEdit->text();

    QHostAddress address = getAddressFromQStr(LEText);
    int port = getPortFromQStr(LEText);

    removeAddress(address, port);
    fillTable();
    sendDatagram(cmdSettings::END, clientId, address, port);
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
