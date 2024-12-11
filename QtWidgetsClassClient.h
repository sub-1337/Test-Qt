#pragma once
#include <memory>
#include <QWidget>
#include "ui_QtWidgetsClassClient.h"
#include "Core.h"

class QtWidgetsClassClient : public QWidget
{
	Q_OBJECT
protected:
	std::unique_ptr<IClient> client;
public:
	QtWidgetsClassClient(QWidget *parent = nullptr, std::unique_ptr<IClient> client = nullptr);
	~QtWidgetsClassClient();

private:
	Ui::QtWidgetsClassClientClass ui;
};
