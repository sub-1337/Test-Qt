#pragma once
#include <memory>
#include <QWidget>
#include "ui_QtWidgetsClass.h"
#include "Core.h"

class QtWidgetsClass : public QWidget
{
	Q_OBJECT
	std::unique_ptr<IServer> serv;
public:
	QtWidgetsClass(QWidget *parent = nullptr, std::unique_ptr<IServer> serv = nullptr);
	~QtWidgetsClass();
	void onButtonClick();

private:
	Ui::QtWidgetsClassClass ui;
};
