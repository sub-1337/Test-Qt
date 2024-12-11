#include "QtWidgetsClassServer.h"

QtWidgetsClassServer::QtWidgetsClassServer(QWidget *parent, std::unique_ptr<IServer> serv)
	: serv(std::move(serv)), QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::clicked, this, &QtWidgetsClassServer::onButtonClick);
}

void QtWidgetsClassServer::onButtonClick() {
	this->serv->Serv_Broadcast();
}

QtWidgetsClassServer::~QtWidgetsClassServer()
{}
