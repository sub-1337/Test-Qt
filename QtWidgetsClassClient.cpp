#include "QtWidgetsClassClient.h"

QtWidgetsClassClient::QtWidgetsClassClient(QWidget *parent, std::unique_ptr<WorkerClient> cl) : client(std::move(cl)),
QWidget(parent), timerToRedraw(std::make_unique<QTimer>(this))
{
	//ui.setupUi(this);
	client->start();
}

QtWidgetsClassClient::~QtWidgetsClassClient()
{
	client->terminate();
}
