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
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(560, 160, 141, 25));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(390, 160, 121, 25));
        statBtn = new QPushButton(centralwidget);
        statBtn->setObjectName(QString::fromUtf8("statBtn"));
        statBtn->setGeometry(QRect(560, 220, 89, 25));
        currentTimeLE = new QLineEdit(centralwidget);
        currentTimeLE->setObjectName(QString::fromUtf8("currentTimeLE"));
        currentTimeLE->setEnabled(true);
        currentTimeLE->setGeometry(QRect(560, 300, 191, 25));
        currentTimeLE->setReadOnly(true);
        workingTimeLE = new QLineEdit(centralwidget);
        workingTimeLE->setObjectName(QString::fromUtf8("workingTimeLE"));
        workingTimeLE->setGeometry(QRect(640, 340, 113, 25));
        workingTimeLE->setReadOnly(true);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(390, 300, 101, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(390, 340, 171, 20));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
