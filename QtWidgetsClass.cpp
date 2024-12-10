#include "QtWidgetsClass.h"

QtWidgetsClass::QtWidgetsClass(QWidget *parent, std::unique_ptr<IServer> serv)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::clicked, this, &QtWidgetsClass::onButtonClick);
	this->serv = std::move(serv);
}

void QtWidgetsClass::onButtonClick() {
	this->serv->Serv_Broadcast();
}

QtWidgetsClass::~QtWidgetsClass()
{}
