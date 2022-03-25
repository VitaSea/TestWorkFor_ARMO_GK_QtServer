#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>

#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>

namespace Ui { class MainWindow; }

class Server : public QMainWindow
{
    Q_OBJECT

public:

    explicit Server(QWidget *parent = nullptr);
    ~Server();

signals:

    void NewMessage(QString);

private slots:

    void NewClientConnection();
    void AddSocketOnList(QTcpSocket* socket);
    void ReadClientSocket();
    void DisconnectedSocket();
    void ShowMessage(const QString& str);
    void RunServer();

private:

    Ui::MainWindow *ui;
    QTcpServer* tcp_server;
    QSet<QTcpSocket*> tcp_socket_set;
};

#endif // MAINWINDOW_H
