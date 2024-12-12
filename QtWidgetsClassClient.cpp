#include "QtWidgetsClassClient.h"

QtWidgetsClassClient::QtWidgetsClassClient(QWidget *parent, std::unique_ptr<WorkerClient> cl) : client(std::move(cl)), QWidget(parent)
{
	//ui.setupUi(this);
	client->start();
}

QtWidgetsClassClient::~QtWidgetsClassClient()
{
	client->terminate();
}
