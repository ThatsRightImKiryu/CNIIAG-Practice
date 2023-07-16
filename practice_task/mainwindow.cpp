#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <QCryptographicHash>
#include <Clientsettings.h>
#include <koi7.h>
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
    uint8_t byteToggles;
    char errorList[49];
    char command[];
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
    initSocket(networkSettings::ADDRESS, networkSettings::CLIENT_PORT);
}

MainWindow::~MainWindow()
{
    for(auto a: addresses)
    {
        QStringList slist = a.split(":");
        QHostAddress address = QHostAddress(slist.value(0));
        int port = slist.value(1).toInt();

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
    QStringList slist = LEText.split(":");

    QHostAddress address = QHostAddress(slist.value(0));
    int port = slist.value(1).toInt();

    sendDatagram(cmdSettings::INIT, clientId, address, port);
}

void MainWindow::on_statBtn_clicked()
{
    QString LEText = ui->lineEdit->text();
    QStringList slist = LEText.split(":");

    QHostAddress address = QHostAddress(slist.value(0));
    int port = slist.value(1).toInt();
    clearWindow();
    sendDatagram(cmdSettings::STAT, clientId, address, port);
}

void MainWindow::on_endSessionBtn_clicked()
{
    QString LEText = ui->lineEdit->text();
    QStringList slist = LEText.split(":");

    QHostAddress address = QHostAddress(slist.value(0));
    int port = slist.value(1).toInt();
    removeAddress(address, port);
    fillTable();
    sendDatagram(cmdSettings::END, clientId, address, port);
}

void MainWindow::on_sessionTable_cellDoubleClicked(int row)
{
    QString address = ui->sessionTable->item(row, 1)->text();
    ui->lineEdit->setText(address);
}


void MainWindow::fillTable(){
    QTableWidget *table = ui->sessionTable;
    table->clear(); table->setRowCount(0);
    QStringList headers = {"Session id","Server address"};
    table->setHorizontalHeaderLabels(headers);
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

        ServerStruct *readData = reinterpret_cast<ServerStruct *>(datagramByte.data());
        qDebug()<<"Read successfully "<<readData->command;

        if(!qstrcmp(readData->command, cmdSettings::ASK)){
            qDebug()<<"ASK package";
            if(readData->checkSum==checkSum && !isInit(datagram.senderAddress(), datagram.senderPort())){
                addAddress(datagram.senderAddress(), datagram.senderPort());
                fillTable();
                qDebug()<<"Package got successfully";
            }
            else qDebug()<<"Package sending FAILED";
        }


        StatStruct *readStatData = reinterpret_cast<StatStruct *>(datagramByte.data());
        if(!qstrcmp(readStatData->command, cmdSettings::STAT)){
            ui->currentTimeLE->setText(std::asctime(std::localtime(&readStatData->currentTime)));
            ui->workingTimeLE->setText(QString::number(readStatData->fullTime));
            ui->commandLE->setText(QString::number(readStatData->cmdCount));
            byteToToggles(readStatData->byteToggles);
            KOI7 utf8_str(readStatData->errorList);
            qDebug()<<"STAT package"<<utf8_str.toUTF8();
        }
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

    QList<QCheckBox *> toggles = ui->toggleGroupBox->findChildren<QCheckBox*>();
    for(auto t: toggles){
       if(byteToggles % 2) t->setChecked(true);
       byteToggles /= 2;
    }
}

void MainWindow::clearWindow()
{
    QList<QLineEdit*> gbLineEdits = ui->StatusGroupBox->findChildren<QLineEdit*>();
    for(auto le: gbLineEdits)
    {
        le->clear();
    }

    QList<QCheckBox *> toggles = ui->toggleGroupBox->findChildren<QCheckBox*>();
    for(auto t: toggles)
    {
        t->setChecked(false);
    }


}

//---------------------------------Session Methods---------------------------------//

void MainWindow::addAddress(QHostAddress address, int port){
    QString fullAddress = address.toString() + ":" + QString::number(port);

    if(!isInit(fullAddress))
        addresses.push_back(fullAddress);
}

void MainWindow::removeAddress(QHostAddress address, int port){
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

bool MainWindow::isInit(QHostAddress address, int port){
    QString fullAddress = address.toString() + ":" + QString::number(port);
    for(auto x: addresses){
        if(fullAddress == x){
            return true;
        }
    }
    return false;
}




