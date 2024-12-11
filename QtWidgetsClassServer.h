#pragma once
#include <memory>
#include <QWidget>
#include "ui_QtWidgetsClass.h"
#include "Core.h"

class QtWidgetsClassServer : public QWidget
{
	Q_OBJECT
protected:
	std::unique_ptr<IServer> serv;
public:
	QtWidgetsClassServer(QWidget *parent = nullptr, std::unique_ptr<IServer> serv = nullptr);
	~QtWidgetsClassServer();
	void onButtonClick();

private:
	Ui::QtWidgetsClassClass ui;
};
