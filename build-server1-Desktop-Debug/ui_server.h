/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Server
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Server)
    {
        if (Server->objectName().isEmpty())
            Server->setObjectName(QString::fromUtf8("Server"));
        Server->resize(800, 600);
        centralwidget = new QWidget(Server);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(180, 190, 461, 161));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(40, 50, 92, 23));
        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(140, 50, 92, 23));
        checkBox_3 = new QCheckBox(groupBox);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(240, 50, 92, 23));
        checkBox_4 = new QCheckBox(groupBox);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(340, 50, 92, 23));
        checkBox_9 = new QCheckBox(groupBox);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setGeometry(QRect(40, 90, 92, 23));
        checkBox_10 = new QCheckBox(groupBox);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
        checkBox_10->setGeometry(QRect(140, 90, 92, 23));
        checkBox_11 = new QCheckBox(groupBox);
        checkBox_11->setObjectName(QString::fromUtf8("checkBox_11"));
        checkBox_11->setGeometry(QRect(230, 90, 92, 23));
        checkBox_12 = new QCheckBox(groupBox);
        checkBox_12->setObjectName(QString::fromUtf8("checkBox_12"));
        checkBox_12->setGeometry(QRect(340, 90, 92, 23));
        Server->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Server);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        Server->setMenuBar(menubar);
        statusbar = new QStatusBar(Server);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Server->setStatusBar(statusbar);

        retranslateUi(Server);

        QMetaObject::connectSlotsByName(Server);
    } // setupUi

    void retranslateUi(QMainWindow *Server)
    {
        Server->setWindowTitle(QCoreApplication::translate("Server", "Server", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Server", "Toggles", nullptr));
        checkBox->setText(QCoreApplication::translate("Server", "1", nullptr));
        checkBox_2->setText(QCoreApplication::translate("Server", "2", nullptr));
        checkBox_3->setText(QCoreApplication::translate("Server", "3", nullptr));
        checkBox_4->setText(QCoreApplication::translate("Server", "4", nullptr));
        checkBox_9->setText(QCoreApplication::translate("Server", "5", nullptr));
        checkBox_10->setText(QCoreApplication::translate("Server", "6", nullptr));
        checkBox_11->setText(QCoreApplication::translate("Server", "7", nullptr));
        checkBox_12->setText(QCoreApplication::translate("Server", "8", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Server: public Ui_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
