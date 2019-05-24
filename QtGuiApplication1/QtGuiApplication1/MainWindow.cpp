#include "MainWindow.h"
#include <QMessageBox>
#include <QSslError>
#include <QList>
#include <QUrl>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(&websocket, &QWebSocket::connected, this, [&] {
		ui.statusBar->showMessage("Connect!"); 
		ui.groupBox_2->setEnabled(true);
	});
	connect(&websocket, &QWebSocket::disconnected, this, [&] {
		ui.statusBar->showMessage("Disconnect!"); 
		ui.groupBox_2->setEnabled(false);
	});
	typedef void (QWebSocket:: *sslErrorsSignal)(const QList<QSslError> &);
	connect(&websocket, static_cast<sslErrorsSignal>(&QWebSocket::sslErrors),
		this, [] (QList<QSslError> erros){
		QMessageBox::warning(0, "SSL error", erros[0].errorString());
	});
	//ÉèÖÃ´úÀí
	proxy.setHostName(ui.lineEdit_5->text());
	proxy.setPort(ui.lineEdit_6->text().toInt());
	websocket.setProxy(proxy);
}

void MainWindow::onConnect()
{
	websocket.open(QUrl("wss://api.huobi.pro/ws"));
}
