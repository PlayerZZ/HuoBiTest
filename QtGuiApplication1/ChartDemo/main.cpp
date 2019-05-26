#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

// 	KLineChart t;
// 	t.show();

	//KLineChart t;
	return a.exec();
}
