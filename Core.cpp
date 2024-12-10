#include "Core.h"



void Server::Serv_Broadcast()
{    
    workerThread_Server.start();  // Start the thread

    // workerThread.wait();  // Wait for the thread to finish
}
void Server::Serv_AllowConnection()
{

}
Server::~Server()
{
    workerThread_Server.terminate();
}