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
    QGroupBox *StatusGroupBox;
    QLineEdit *commandLE;
    QLabel *label_3;
    QLineEdit *workingTimeLE;
    QLabel *label;
    QLineEdit *currentTimeLE;
    QLabel *label_2;
    QGroupBox *groupBox_toggle;
    QLabel *label_11;
    QLabel *label_4;
    QLabel *label_10;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_8;
    QGroupBox *groupBox_err;
    QLabel *label_17;
    QLabel *label_19;
    QLabel *label_16;
    QLineEdit *lineEdit_11;
    QLabel *label_14;
    QLabel *label_18;
    QLabel *label_15;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_16;
    QLineEdit *lineEdit_15;
    QLabel *label_13;
    QLabel *label_12;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit_12;
    QLineEdit *lineEdit_pkgSize;
    QLabel *label_20;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 918);
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
        groupBox_toggle = new QGroupBox(centralwidget);
        groupBox_toggle->setObjectName(QString::fromUtf8("groupBox_toggle"));
        groupBox_toggle->setGeometry(QRect(80, 520, 241, 361));
        label_11 = new QLabel(groupBox_toggle);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 270, 67, 17));
        label_4 = new QLabel(groupBox_toggle);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 30, 61, 20));
        label_10 = new QLabel(groupBox_toggle);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 230, 67, 17));
        label_7 = new QLabel(groupBox_toggle);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 150, 67, 17));
        label_8 = new QLabel(groupBox_toggle);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 190, 67, 17));
        label_9 = new QLabel(groupBox_toggle);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 310, 67, 17));
        label_5 = new QLabel(groupBox_toggle);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 70, 67, 17));
        label_6 = new QLabel(groupBox_toggle);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 110, 67, 17));
        lineEdit_9 = new QLineEdit(groupBox_toggle);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(90, 30, 113, 25));
        lineEdit_9->setReadOnly(true);
        lineEdit_4 = new QLineEdit(groupBox_toggle);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(90, 60, 113, 25));
        lineEdit_4->setReadOnly(true);
        lineEdit_6 = new QLineEdit(groupBox_toggle);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(90, 100, 113, 25));
        lineEdit_6->setReadOnly(true);
        lineEdit_7 = new QLineEdit(groupBox_toggle);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(90, 150, 113, 25));
        lineEdit_7->setReadOnly(true);
        lineEdit_5 = new QLineEdit(groupBox_toggle);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(90, 190, 113, 25));
        lineEdit_5->setReadOnly(true);
        lineEdit_3 = new QLineEdit(groupBox_toggle);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(90, 230, 113, 25));
        lineEdit_3->setReadOnly(true);
        lineEdit_2 = new QLineEdit(groupBox_toggle);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(90, 270, 113, 25));
        lineEdit_2->setReadOnly(true);
        lineEdit_8 = new QLineEdit(groupBox_toggle);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(90, 310, 113, 25));
        lineEdit_8->setReadOnly(true);
        groupBox_err = new QGroupBox(centralwidget);
        groupBox_err->setObjectName(QString::fromUtf8("groupBox_err"));
        groupBox_err->setGeometry(QRect(470, 530, 261, 351));
        label_17 = new QLabel(groupBox_err);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(6, 270, 101, 20));
        label_19 = new QLabel(groupBox_err);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(6, 110, 101, 20));
        label_16 = new QLabel(groupBox_err);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(6, 310, 101, 20));
        lineEdit_11 = new QLineEdit(groupBox_err);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        lineEdit_11->setGeometry(QRect(120, 30, 113, 25));
        lineEdit_11->setReadOnly(true);
        label_14 = new QLabel(groupBox_err);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(6, 150, 101, 20));
        label_18 = new QLabel(groupBox_err);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(6, 70, 101, 20));
        label_15 = new QLabel(groupBox_err);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(6, 190, 101, 20));
        lineEdit_14 = new QLineEdit(groupBox_err);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        lineEdit_14->setGeometry(QRect(120, 70, 113, 25));
        lineEdit_14->setReadOnly(true);
        lineEdit_10 = new QLineEdit(groupBox_err);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        lineEdit_10->setGeometry(QRect(120, 110, 113, 25));
        lineEdit_10->setReadOnly(true);
        lineEdit_16 = new QLineEdit(groupBox_err);
        lineEdit_16->setObjectName(QString::fromUtf8("lineEdit_16"));
        lineEdit_16->setGeometry(QRect(120, 150, 113, 25));
        lineEdit_16->setReadOnly(true);
        lineEdit_15 = new QLineEdit(groupBox_err);
        lineEdit_15->setObjectName(QString::fromUtf8("lineEdit_15"));
        lineEdit_15->setGeometry(QRect(120, 190, 113, 25));
        lineEdit_15->setReadOnly(true);
        label_13 = new QLabel(groupBox_err);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(6, 230, 101, 20));
        label_12 = new QLabel(groupBox_err);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(0, 30, 101, 20));
        lineEdit_17 = new QLineEdit(groupBox_err);
        lineEdit_17->setObjectName(QString::fromUtf8("lineEdit_17"));
        lineEdit_17->setGeometry(QRect(120, 230, 113, 25));
        lineEdit_17->setReadOnly(true);
        lineEdit_13 = new QLineEdit(groupBox_err);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        lineEdit_13->setGeometry(QRect(120, 270, 113, 25));
        lineEdit_13->setReadOnly(true);
        lineEdit_12 = new QLineEdit(groupBox_err);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        lineEdit_12->setGeometry(QRect(120, 310, 113, 25));
        lineEdit_12->setReadOnly(true);
        lineEdit_pkgSize = new QLineEdit(centralwidget);
        lineEdit_pkgSize->setObjectName(QString::fromUtf8("lineEdit_pkgSize"));
        lineEdit_pkgSize->setGeometry(QRect(130, 330, 113, 25));
        lineEdit_pkgSize->setReadOnly(true);
        label_20 = new QLabel(centralwidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(10, 340, 111, 17));
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
        StatusGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Status from server", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Count of commands", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Current Time", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Seconds passed working", nullptr));
        groupBox_toggle->setTitle(QCoreApplication::translate("MainWindow", "Toggles", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Toggle 7", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Toggle 1", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Toggle 6", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Toggle 4", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Toggle 5", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Toggle 8", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Toggle 2", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Toggle 3", nullptr));
        groupBox_err->setTitle(QCoreApplication::translate("MainWindow", "Error toggles", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Error Toggle 7", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Error Toggle 3", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Error Toggle 8", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Error Toggle 4", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Error Toggle 2", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Error Toggle 5", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Error Toggle 6", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Error Toggle 1", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Size of package", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
