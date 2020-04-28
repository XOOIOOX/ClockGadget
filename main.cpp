#include "ClockGadget.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
	QCoreApplication::setOrganizationName("XOOIOOX");
	QCoreApplication::setApplicationName("Clock");
	QApplication app(argc, argv);
	app.setQuitOnLastWindowClosed(false);
	ClockGadget window;
	window.show();
	return app.exec();
}