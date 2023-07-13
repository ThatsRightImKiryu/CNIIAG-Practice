/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QPushButton *statBtn;
    QLineEdit *currentTimeLE;
    QLineEdit *workingTimeLE;
    QLabel *label;
    QLabel *label_2;
    QTableWidget *sessionTable;
    QLabel *label_3;
    QLineEdit *commandLE;
    QPushButton *endSessionBtn;
    QGroupBox *groupBox;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 675);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(560, 160, 191, 25));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(390, 160, 151, 25));
        statBtn = new QPushButton(centralwidget);
        statBtn->setObjectName(QString::fromUtf8("statBtn"));
        statBtn->setGeometry(QRect(560, 220, 191, 25));
        currentTimeLE = new QLineEdit(centralwidget);
        currentTimeLE->setObjectName(QString::fromUtf8("currentTimeLE"));
        currentTimeLE->setEnabled(true);
        currentTimeLE->setGeometry(QRect(560, 300, 191, 25));
        currentTimeLE->setReadOnly(true);
        workingTimeLE = new QLineEdit(centralwidget);
        workingTimeLE->setObjectName(QString::fromUtf8("workingTimeLE"));
        workingTimeLE->setGeometry(QRect(562, 340, 191, 25));
        workingTimeLE->setReadOnly(true);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(440, 300, 101, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(370, 340, 171, 20));
        sessionTable = new QTableWidget(centralwidget);
        if (sessionTable->columnCount() < 2)
            sessionTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        sessionTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        sessionTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        sessionTable->setObjectName(QString::fromUtf8("sessionTable"));
        sessionTable->setGeometry(QRect(20, 60, 351, 192));
        sessionTable->setMinimumSize(QSize(351, 192));
        sessionTable->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        sessionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(390, 380, 151, 20));
        commandLE = new QLineEdit(centralwidget);
        commandLE->setObjectName(QString::fromUtf8("commandLE"));
        commandLE->setGeometry(QRect(562, 380, 191, 25));
        commandLE->setReadOnly(true);
        endSessionBtn = new QPushButton(centralwidget);
        endSessionBtn->setObjectName(QString::fromUtf8("endSessionBtn"));
        endSessionBtn->setGeometry(QRect(30, 280, 191, 25));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(150, 430, 461, 161));
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
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Send package", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "127.0.0.1:4335", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "init/status", nullptr));
        statBtn->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Current Time", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Seconds passed working", nullptr));
        QTableWidgetItem *___qtablewidgetitem = sessionTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Session id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = sessionTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Server address", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Count of commands", nullptr));
        endSessionBtn->setText(QCoreApplication::translate("MainWindow", "End current session", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Toggles", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        checkBox_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        checkBox_9->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        checkBox_10->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        checkBox_11->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        checkBox_12->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
