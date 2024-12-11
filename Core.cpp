#include "Core.h"



void Server::Serv_Broadcast()
{    
    workerSenderBeacon.start();  // Start the thread

    // workerThread.wait();  // Wait for the thread to finish
}
void Server::Serv_AllowConnection()
{

}
Server::~Server()
{
    workerSenderBeacon.terminate();
}

Client::Client()
{
    workerListenUDP.start();
}

void Client::Client_ListenUDP()
{

}

void Client::Client_ConnectServer()
{

}