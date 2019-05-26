#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QHBoxLayout* layout = new QHBoxLayout;
	ui.widget->setLayout(layout);
	using Period = KLineSocket::Period ;
	KLineChart *chartview = new KLineChart("btcusdt", Period::MIN1, this);
	layout->addWidget(chartview);
}
