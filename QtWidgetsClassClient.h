#pragma once
#include <memory>
#include <QWidget>
#include <QPainter>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include "ui_QtWidgetsClassClient.h"
#include "Core.h"

class QtWidgetsClassClient : public QWidget
{
	Q_OBJECT
protected:
	std::unique_ptr<IClient> client;
    std::unique_ptr<QTableWidget> table;
    bool drawed = false;
public:
	QtWidgetsClassClient(QWidget *parent = nullptr, std::unique_ptr<IClient> client = nullptr);
	~QtWidgetsClassClient();
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);
        if (drawed == false) 
        {
            table = std::make_unique<QTableWidget>(3, 3);

            //table.setWindowTitle("Пример таблицы");

            // Установка заголовков
            //table->setHorizontalHeaderLabels(QStringList{ "Колонка 1", "Колонка 2", "Колонка 3" });

            // Добавление данных в ячейки
            table->setItem(0, 0, new QTableWidgetItem("A1"));
            table->setItem(0, 1, new QTableWidgetItem("B1"));
            table->setItem(0, 2, new QTableWidgetItem("C1"));

            table->setItem(1, 0, new QTableWidgetItem("A2"));
            table->setItem(1, 1, new QTableWidgetItem("B2"));
            table->setItem(1, 2, new QTableWidgetItem("C2"));

            QPushButton* button = new QPushButton("Connect");
            table->setCellWidget(1, 2, button);

            table->show();

            QObject::connect(button, &QPushButton::clicked, [&]() {
                int a = 10;
                });
            table->resize(400, 300);
            table->show();

            drawed = true;
        }      
    }


private:
	Ui::QtWidgetsClassClientClass ui;
public:
    using QWidget::QWidget;
};
