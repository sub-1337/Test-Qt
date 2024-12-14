#pragma once
#include <memory>
#include <QWidget>
#include <QPainter>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTimer>
#include <QPushButton>
#include "ServWorker.h"

class QtWidgetsClassClient : public QWidget
{
	Q_OBJECT
protected:
	std::unique_ptr<WorkerClient> client;
    std::unique_ptr<QTableWidget> table;
    std::unique_ptr<QTimer> timerToRedraw;
    
public:
	QtWidgetsClassClient(QWidget *parent = nullptr, std::unique_ptr<WorkerClient> client = nullptr);
	~QtWidgetsClassClient();
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);
        
        std::vector<std::shared_ptr<QPushButton>> buttons;

        std::vector<ServersList> serversList = client->getServerList();
        table = std::make_unique<QTableWidget>(serversList.size(), 4); // первое - строки, второе - столбцы
        
        for (ServersList currButton : serversList)
        {
            buttons.push_back(std::make_shared<QPushButton> ("Connect"));
            connect(buttons.back().get(), &QPushButton::clicked, this, &QtWidgetsClassClient::onConnectPress);
        }
            

        for (size_t i = 0; i < serversList.size(); i++)
        {
            table->setItem(i, 0, new QTableWidgetItem(serversList[0].ipOfServer.toString()));
            buttons[i]->setText("Test");
            table->setCellWidget(i, 3, buttons[i].get());
        }

        //table.setWindowTitle("Пример таблицы");

        // Установка заголовков
        //table->setHorizontalHeaderLabels(QStringList{ "Колонка 1", "Колонка 2", "Колонка 3" });

        // Добавление данных в ячейки
        /*table->setItem(0, 0, new QTableWidgetItem("A1"));
        table->setItem(0, 1, new QTableWidgetItem("B1"));
        table->setItem(0, 2, new QTableWidgetItem("C1"));

        table->setItem(1, 0, new QTableWidgetItem("A2"));
        table->setItem(1, 1, new QTableWidgetItem("B2"));
        table->setItem(1, 2, new QTableWidgetItem("C2"));

        QPushButton* button = new QPushButton("Connect");
        table->setCellWidget(1, 2, button);*/

        table->show();

        /*QObject::connect(button, &QPushButton::clicked, [&]() {
            int a = 10;
            });*/
        table->resize(400, 300);
        table->show();

        timerToRedraw->start(1000);

        connect(timerToRedraw.get(), &QTimer::timeout, this, &QtWidgetsClassClient::redraw);
    }
    void redraw()
    {
        update();
    }
    void onConnectPress()
    {
        int a = 0;
    }

private:
	//Ui::QtWidgetsClassClientClass ui;
public:
    using QWidget::QWidget;
};
