#pragma once
#include <iostream>
#include <atomic>
#include <QThread>
#include <QDebug>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>

class WorkerSenderBeacon : public QThread 
{
    Q_OBJECT
private:
    const size_t port = 10001;
    QByteArray message = "beacon";
public:

    virtual void run() override 
    {
        
        /*for (int i = 0; i < 5; ++i) {
            qDebug() << "Thread running, iteration" << i;
            QThread::sleep(1);
        }*/
        QUdpSocket udpSocket;

        // Send the message to the broadcast address on a specific port (e.g., 12345)
        while (true)
        {
            udpSocket.writeDatagram(message, QHostAddress::Broadcast, port);
            QThread::sleep(1);
        }       

    }
};

class WorkerListenUDP : public QThread
{
    Q_OBJECT
    std::unique_ptr<QUdpSocket> udpSocket;
    const size_t port = 10001;
public:
    virtual void run() override
    {
        udpSocket = std::make_unique<QUdpSocket>();
        
        auto resOfBind = udpSocket->bind(QHostAddress::AnyIPv4, port);

        if (resOfBind) {
            qDebug() << "Listening on port:" << port;
        }
        else {
            qDebug() << "Failed to bind to port:" << port;
            return;
        }

        connect(udpSocket.get(), &QUdpSocket::readyRead, this, &WorkerListenUDP::readPendingDatagrams);

        //readPendingDatagrams();

        /*QObject::connect(&udpSocket, &QUdpSocket::readyRead, [&udpSocket]() {
            while (udpSocket->hasPendingDatagrams()) {
                QByteArray datagram;
                datagram.resize(udpSocket->pendingDatagramSize());
                QHostAddress sender;
                quint16 senderPort;

                udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
            }
            });*/
    }
private:
    QByteArray message = "beacon";
private slots:
    void readPendingDatagrams()
    {
        while (udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(static_cast<int>(udpSocket->pendingDatagramSize()));
            QHostAddress sender;
            quint16 senderPort;

            // Получение данных
            udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
            if (datagram == message)
                std::cout << "Hit" << std::endl;
            QThread::sleep(1);
        }
    }
    void Process()
    {

    }
};