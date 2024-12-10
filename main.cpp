//
//#include <iostream>
//#include <QtCore/QCoreApplication>
//
//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);
//    std::cout << "Qt version: " << qVersion() << std::endl;
//    return a.exec();
//}

#include <memory>
#include <string>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "QtWidgetsClass.h"
#include "Core.h"

int main(int argc, char** argv)
{
	bool is_server = true;
	if (argc >= 2)
	{
		auto str = std::string(argv[1]);
		if (str == "-c")
			is_server = true;
	}
	QApplication app(argc, argv);
	if (is_server)
	{
		std::unique_ptr<IServer> srv = std::make_unique<Server>();
		QtWidgetsClass window(nullptr, std::move(srv));
		window.show();
		return app.exec();
	}
	else
	{
		return app.exec();
	}
}