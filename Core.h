#pragma once
#include "ServWorker.h"

class IAppCore
{
public:
    IAppCore() = default;
    virtual ~IAppCore() = 0; // Pure virtual destructor
};

inline IAppCore::~IAppCore() {}

class IServer : public IAppCore
{
public:
    virtual void Serv_Broadcast() = 0;
    virtual void Serv_AllowConnection() = 0;
    virtual ~IServer() override {}
};

class IClient : public IAppCore
{
public:
    virtual void Client_ConnectServer() = 0;
    virtual void Client_ListenUDP() = 0;
};

class Server : public IServer
{
    WorkerServer workerSenderBeacon;
public:
    Server() : IServer() {}
    virtual void Serv_Broadcast() override;
    virtual void Serv_AllowConnection() override;
    virtual ~Server() override;
};

class Client : public IClient
{
    WorkerClient workerListenUDP;
public:
    Client();
    virtual void Client_ConnectServer() override;
    virtual void Client_ListenUDP() override;
};