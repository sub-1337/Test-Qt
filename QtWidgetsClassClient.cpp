#include "QtWidgetsClassClient.h"

QtWidgetsClassClient::QtWidgetsClassClient(QWidget *parent, std::unique_ptr<IClient> cl) : client(std::move(cl)), QWidget(parent)
{
	ui.setupUi(this);
}

QtWidgetsClassClient::~QtWidgetsClassClient()
{}
