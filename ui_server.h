/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextBrowser *textBrowser_receivedMessages;
    QLabel *labelImageBrowser;
    QLabel *labelStatusServer;
    QPushButton *pushButtonRunServer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(910, 488);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        textBrowser_receivedMessages = new QTextBrowser(centralWidget);
        textBrowser_receivedMessages->setObjectName(QString::fromUtf8("textBrowser_receivedMessages"));
        textBrowser_receivedMessages->setGeometry(QRect(0, 50, 381, 431));
        textBrowser_receivedMessages->setStyleSheet(QString::fromUtf8(""));
        labelImageBrowser = new QLabel(centralWidget);
        labelImageBrowser->setObjectName(QString::fromUtf8("labelImageBrowser"));
        labelImageBrowser->setGeometry(QRect(390, 50, 511, 431));
        labelImageBrowser->setFrameShape(QFrame::Box);
        labelImageBrowser->setAlignment(Qt::AlignCenter);
        labelStatusServer = new QLabel(centralWidget);
        labelStatusServer->setObjectName(QString::fromUtf8("labelStatusServer"));
        labelStatusServer->setGeometry(QRect(220, 10, 681, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        labelStatusServer->setFont(font);
        pushButtonRunServer = new QPushButton(centralWidget);
        pushButtonRunServer->setObjectName(QString::fromUtf8("pushButtonRunServer"));
        pushButtonRunServer->setGeometry(QRect(9, 10, 201, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButtonRunServer->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MyServer", nullptr));
        labelImageBrowser->setText(QString());
        labelStatusServer->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201 \321\201\320\265\321\200\320\262\320\265\321\200\320\260: \320\222\321\213\320\272\320\273\321\216\321\207\320\265\320\275", nullptr));
        pushButtonRunServer->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214 \321\201\320\265\321\200\320\262\320\265\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
