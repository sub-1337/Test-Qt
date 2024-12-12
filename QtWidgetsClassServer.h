#pragma once
#include <memory>
#include <QWidget>
#include "ui_QtWidgetsClass.h"
#include "ServWorker.h"

class QtWidgetsClassServer : public QWidget
{
	Q_OBJECT
protected:
	std::unique_ptr<WorkerServer> serv;
public:
	QtWidgetsClassServer(QWidget *parent = nullptr, std::unique_ptr<WorkerServer> serv = nullptr);
	~QtWidgetsClassServer();
	void onButtonClick();

private:
	Ui::QtWidgetsClassClass ui;
};
