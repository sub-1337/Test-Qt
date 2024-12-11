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
#include <iostream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "QtWidgetsClassServer.h"
#include "QtWidgetsClassClient.h"
#include "Core.h"

int main(int argc, char** argv)
{
	bool isServer = false;
	
	if (argc >= 2)
	{
		std::cout << "argv[1] " << argv[1] << std::endl;
		auto str = std::string(argv[1]);
		if (str == "-c")
			isServer = true;
	}
	
	QApplication app(argc, argv);
	if (isServer)
	{
		std::unique_ptr<IServer> srv = std::make_unique<Server>();
		QtWidgetsClassServer window(nullptr, std::move(srv));
		window.show();
		return app.exec();
	}
	else
	{
		std::unique_ptr<IClient> cl = std::make_unique<Client>();
		QtWidgetsClassClient windowClient(nullptr, std::move(cl));
		windowClient.show();
		return app.exec();
	}
}