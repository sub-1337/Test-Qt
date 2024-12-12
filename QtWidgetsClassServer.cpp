#include "QtWidgetsClassServer.h"
#include "ServWorker.h"
QtWidgetsClassServer::QtWidgetsClassServer(QWidget *parent, std::unique_ptr<WorkerServer> serv)
	: serv(std::move(serv)), QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::clicked, this, &QtWidgetsClassServer::onButtonClick);
}

void QtWidgetsClassServer::onButtonClick() {
	serv->start();
}

QtWidgetsClassServer::~QtWidgetsClassServer()
{
	serv->terminate();
}
