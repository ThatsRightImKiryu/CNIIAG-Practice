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
    QTableWidget *sessionTable;
    QPushButton *endSessionBtn;
    QGroupBox *toggleGroupBox;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;
    QGroupBox *StatusGroupBox;
    QLineEdit *commandLE;
    QLabel *label_3;
    QLineEdit *workingTimeLE;
    QLabel *label;
    QLineEdit *currentTimeLE;
    QLabel *label_2;
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
        endSessionBtn = new QPushButton(centralwidget);
        endSessionBtn->setObjectName(QString::fromUtf8("endSessionBtn"));
        endSessionBtn->setGeometry(QRect(30, 280, 191, 25));
        toggleGroupBox = new QGroupBox(centralwidget);
        toggleGroupBox->setObjectName(QString::fromUtf8("toggleGroupBox"));
        toggleGroupBox->setGeometry(QRect(150, 450, 461, 161));
        checkBox = new QCheckBox(toggleGroupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(40, 50, 92, 23));
        checkBox_2 = new QCheckBox(toggleGroupBox);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(140, 50, 92, 23));
        checkBox_3 = new QCheckBox(toggleGroupBox);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(240, 50, 92, 23));
        checkBox_4 = new QCheckBox(toggleGroupBox);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(340, 50, 92, 23));
        checkBox_9 = new QCheckBox(toggleGroupBox);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setGeometry(QRect(40, 90, 92, 23));
        checkBox_10 = new QCheckBox(toggleGroupBox);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
        checkBox_10->setGeometry(QRect(140, 90, 92, 23));
        checkBox_11 = new QCheckBox(toggleGroupBox);
        checkBox_11->setObjectName(QString::fromUtf8("checkBox_11"));
        checkBox_11->setGeometry(QRect(230, 90, 92, 23));
        checkBox_12 = new QCheckBox(toggleGroupBox);
        checkBox_12->setObjectName(QString::fromUtf8("checkBox_12"));
        checkBox_12->setGeometry(QRect(340, 90, 92, 23));
        StatusGroupBox = new QGroupBox(centralwidget);
        StatusGroupBox->setObjectName(QString::fromUtf8("StatusGroupBox"));
        StatusGroupBox->setGeometry(QRect(380, 250, 401, 191));
        commandLE = new QLineEdit(StatusGroupBox);
        commandLE->setObjectName(QString::fromUtf8("commandLE"));
        commandLE->setGeometry(QRect(190, 150, 191, 25));
        commandLE->setReadOnly(true);
        label_3 = new QLabel(StatusGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 150, 151, 20));
        workingTimeLE = new QLineEdit(StatusGroupBox);
        workingTimeLE->setObjectName(QString::fromUtf8("workingTimeLE"));
        workingTimeLE->setGeometry(QRect(190, 110, 191, 25));
        workingTimeLE->setReadOnly(true);
        label = new QLabel(StatusGroupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 70, 101, 17));
        currentTimeLE = new QLineEdit(StatusGroupBox);
        currentTimeLE->setObjectName(QString::fromUtf8("currentTimeLE"));
        currentTimeLE->setEnabled(true);
        currentTimeLE->setGeometry(QRect(188, 70, 191, 25));
        currentTimeLE->setReadOnly(true);
        label_2 = new QLabel(StatusGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 110, 171, 20));
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
        QTableWidgetItem *___qtablewidgetitem = sessionTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Session id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = sessionTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Server address", nullptr));
        endSessionBtn->setText(QCoreApplication::translate("MainWindow", "End current session", nullptr));
        toggleGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Toggles", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        checkBox_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        checkBox_9->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        checkBox_10->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        checkBox_11->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        checkBox_12->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        StatusGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Status from server", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Count of commands", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Current Time", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Seconds passed working", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
