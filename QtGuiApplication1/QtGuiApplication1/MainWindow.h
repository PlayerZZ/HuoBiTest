#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QWebSocket>
#include <QNetworkRequest>
#include <QNetworkProxy>
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	QWebSocket websocket;
	QNetworkProxy proxy;
private:
	Ui::MainWindowClass ui;
public slots:
void onConnect();
};
