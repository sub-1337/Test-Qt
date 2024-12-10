#pragma once
#include <QThread>
#include <QDebug>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>

class Worker : public QThread {
    Q_OBJECT
public:
    void run() override {
        
        /*for (int i = 0; i < 5; ++i) {
            qDebug() << "Thread running, iteration" << i;
            QThread::sleep(1);
        }*/
        QUdpSocket udpSocket;

        // Allow broadcasting
        // udpSocket.setSocketOption(QAbstractSocket::;

        // Create the message to broadcast
        QByteArray message = "Hello, this is a broadcast message!";

        // Send the message to the broadcast address on a specific port (e.g., 12345)
        while (true)
        {
            udpSocket.writeDatagram(message, QHostAddress::Broadcast, 10001);
            QThread::sleep(1);
        }
        

    }
};