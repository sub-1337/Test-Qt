#pragma once
#include <iostream>
#include <atomic>
#include <vector>
#include <chrono>
#include <QThread>
#include <QDebug>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>

enum class ServerState
{
    none = 0,
    sendBeacon,
    reciveMessage,
    terminating
};

class WorkerServer : public QThread 
{
    Q_OBJECT
private:
    const size_t port = 10001;
    const QByteArray message = "beacon";
    std::atomic<ServerState> currentState = ServerState::sendBeacon;
    std::unique_ptr<QUdpSocket> udpSocket;
public:

    virtual void run() override 
    {
        udpSocket = std::make_unique<QUdpSocket>();
        ServerState state = currentState.load();
        // Send the message to the broadcast address on a specific port (e.g., 12345)
        while (state != ServerState::terminating)
        {
            
            state = currentState.load();
            if (state == ServerState::sendBeacon)
            {
                SendUDPBeacon();
            }
            if (state == ServerState::reciveMessage)
            {
                ReciveMessage();
            }
                
            QThread::sleep(1);
        }  
    }
private:
    void SendUDPBeacon()
    {
        udpSocket->writeDatagram(message, QHostAddress::Broadcast, port);
    }
    void ReciveMessage()
    {

    }
};

enum class ClientState
{
    none = 0,
    initUDP,
    acceptUDPBeacon,
    sendMessage,
    terminating
};

struct ServersList
{
    QHostAddress ipOfServer;
    std::chrono::steady_clock::time_point lastPingTime;
    bool isOnline;
};

class WorkerClient : public QThread
{
    Q_OBJECT
    std::unique_ptr<QUdpSocket> udpSocket;
    const size_t portUDPBeacon = 10001;
    std::atomic<ClientState> currentState = ClientState::initUDP;
    std::vector<ServersList> serversList;
    std::mutex serverListMutex;
public:
    virtual void run() override
    {
        ClientState state = currentState.load();
        while (state != ClientState::terminating)
        {
            state = currentState.load();
            if (state == ClientState::initUDP)
            {
                AcceptUDP();
            }
            if (state == ClientState::acceptUDPBeacon)
            {
                readPendingDatagrams();
            }
            if (state == ClientState::sendMessage)
            {
                SendMessage();
            }
            QThread::sleep(1);
        }
    }
private:
    QByteArray message = "beacon";
    void AcceptUDP()
    {
        udpSocket = std::make_unique<QUdpSocket>();

        auto resOfBind = udpSocket->bind(QHostAddress::AnyIPv4, portUDPBeacon);

        if (resOfBind) {
            qDebug() << "Listening on port:" << portUDPBeacon;
        }
        else {
            qDebug() << "Failed to bind to port:" << portUDPBeacon;
            return;
        }

        connect(udpSocket.get(), &QUdpSocket::readyRead, this, &WorkerClient::readPendingDatagrams);
        currentState.store(ClientState::acceptUDPBeacon);

    }
private slots:
    void readPendingDatagrams()
    {
        while (udpSocket->hasPendingDatagrams())
        {
            QByteArray datagram;
            datagram.resize(static_cast<int>(udpSocket->pendingDatagramSize()));
            QHostAddress sender;
            quint16 senderPort;

            // Получение данных
            udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
            if (datagram == message)
            {
                std::lock_guard<std::mutex> lk(serverListMutex);
                {
                    for (ServersList entry : serversList)
                    {
                        if (entry.ipOfServer == sender)
                        {
                            return;
                        }
                    }
                    serversList.push_back(ServersList{ sender, std::chrono::steady_clock::now() , true });
                    currentState.store(ClientState::sendMessage);
                }
            }               
            
        }        
    }
    void SendMessage()
    {

    }
public:
    std::vector<ServersList> getServerList()
    {
        std::lock_guard<std::mutex> lk(serverListMutex);
        {
            return serversList;
        }
    }
};