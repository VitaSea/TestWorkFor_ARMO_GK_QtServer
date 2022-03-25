#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcp_server = nullptr;
    // Соединяем сигнал получения нового сообщения с слотом его для его отображения на экран
    connect(this, &Server::NewMessage, this, &Server::ShowMessage);
    // Соединяем сигнал нажатия на кнопку запуска сервера с слотом его запуска
    connect(ui->pushButtonRunServer, &QPushButton::clicked, this, &Server::RunServer);
}

void Server::RunServer()
{
    if(!tcp_server)
    {
        tcp_server = new QTcpServer(this);
        if(tcp_server->listen(QHostAddress::Any, 52417)) // Запускаем сервер
        {
           // Соединяем сигнал новых входящих подключений с слотом для добавления сокета подключенного клиента
           connect(tcp_server, &QTcpServer::newConnection, this, &Server::NewClientConnection);
           ui->labelStatusServer->setText("Статус сервера: Работает");
           ui->pushButtonRunServer->setText("Остановить сервер");
        }
        else
        {
            ui->labelStatusServer->setText("Статус сервера: Неудачный запуск");
            delete tcp_server;
            tcp_server = nullptr;
        }
    }
    else
    {
        tcp_server->close();
        delete tcp_server;
        tcp_server = nullptr;
        ui->labelStatusServer->setText("Статус сервера: Выключен");
        ui->pushButtonRunServer->setText("Запустить сервер");
    }
}

void Server::ShowMessage(const QString& str)
{
    ui->textBrowser_receivedMessages->append(str);
}

void Server::NewClientConnection()
{
    while (tcp_server->hasPendingConnections())
    {
        AddSocketOnList(tcp_server->nextPendingConnection());
    }
}

void Server::AddSocketOnList(QTcpSocket* tcp_socket)
{
    tcp_socket_set.insert(tcp_socket);
    connect(tcp_socket, &QTcpSocket::readyRead,    this, &Server::ReadClientSocket);
    connect(tcp_socket, &QTcpSocket::disconnected, this, &Server::DisconnectedSocket);
    ShowMessage(QString("Клиент #%1: подключился.").arg(tcp_socket->socketDescriptor()));
}

void Server::ReadClientSocket()
{
    const quint16 file_info_part_size = 64;

    QTcpSocket* tcp_socket = (QTcpSocket*)sender();
    QByteArray arr_buffer;

    QDataStream data_stream(tcp_socket);
    data_stream.setVersion(QDataStream::Qt_5_14);
    data_stream.startTransaction();
    data_stream >> arr_buffer;

    if(!data_stream.commitTransaction())   // Получение данных файла от клиента
    {
        QString message = QString("Получение данных файла от клиента #%1:").arg(tcp_socket->socketDescriptor());
        emit NewMessage(message);
        return;
    }

    // Записываем информацию о полученных данных от клиента
    // message_type: file_name: file_size:
    QString data_info = arr_buffer.mid(0, file_info_part_size); // Первые (file_info_part_size = 64) байт
    // Записываем тип принятого файла "image", "audio", "video", "other"
    QString str_message_type = data_info.split(",")[0].split(":")[1];
    // Вырезаем лишние байты для data_info из буффера
    arr_buffer = arr_buffer.mid(file_info_part_size);

    if(str_message_type == "message") // Сообщение содержит обычный текст
    {
        QString message = QString("Клиент #%1 прислал текстовое сообщение: %2").arg(tcp_socket->socketDescriptor()).arg(QString::fromStdString(arr_buffer.toStdString()));
        emit NewMessage(message);
    }
    else // К сообщению прикреплён файл
    {
        QString str_file_name = data_info.split(",")[1].split(":")[1];                 // Имя файла name.xxx
        QString str_file_size = data_info.split(",")[2].split(":")[1].split(";")[0];   // Размер файла

        // Создаём файл для записи в него данных из буффера
        QFile file(str_file_name);

        if(file.open(QIODevice::WriteOnly))
        {
            file.write(arr_buffer); // Записываем буффер в файл

            QString message;
            message = ("Клиент #%1 прислал %2 файл %3: размером " + str_file_size + " байт.").arg(tcp_socket->socketDescriptor()).arg(str_message_type).arg(file.fileName());

            if(str_message_type == "image")
            {
                QPixmap pixmap;
                pixmap.convertFromImage(QImage(file.fileName()));
                ui->labelImageBrowser->setPixmap(pixmap.scaled(ui->labelImageBrowser->width(), ui->labelImageBrowser->height(), Qt::KeepAspectRatio));
            }
            else if(str_message_type == "audio")
            {
                ui->labelImageBrowser->setText(QString("Аудио файл %1 получен.").arg(str_file_name));
            }
            else if(str_message_type == "video")
            {
                ui->labelImageBrowser->setText(QString("Видео файл %1 получен.").arg(str_file_name));
            }
            else if(str_message_type == "other")
            {
                ui->labelImageBrowser->setText(QString("Файл %1 получен.").arg(str_file_name));
            }
            emit NewMessage(message);
            file.close();
        }
    }
}

void Server::DisconnectedSocket()
{
    QTcpSocket* tcp_soket = (QTcpSocket*)sender();
    QSet<QTcpSocket*>::iterator it = tcp_socket_set.find(tcp_soket);

    if (it != tcp_socket_set.end())
    {
        ShowMessage(QString("Клиент отключился от сервера."));
        tcp_socket_set.remove(*it);
    }
    tcp_soket->deleteLater();
}

Server::~Server()
{
    foreach (QTcpSocket* tcp_socket, tcp_socket_set)
    {
        tcp_socket->close();
        tcp_socket->deleteLater();
    }

    tcp_server->close();
    tcp_server->deleteLater();
    delete ui;
}
