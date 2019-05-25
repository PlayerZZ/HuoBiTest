#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QWebSocket>
#include <QNetworkRequest>
#include <QNetworkProxy>
#include <zlib.h>
#include <QByteArray>
#include <QChart>
#include <QChartView>
#include <QSqlDatabase>
#include <QSqlQuery>


#include <QJsonValue>
#include <QCandlestickSeries>
#include <QCandlestickSet>

#include <QMessageBox>
#include <QSqlError>
#include <QDateTimeAxis>
#include <QValueAxis>
QT_CHARTS_USE_NAMESPACE
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	QWebSocket websocket;
	QNetworkProxy proxy;
	QChartView *chartview;
	QSqlDatabase database;

	QChart *chart;
	QCandlestickSeries *acmeSeries;
	QDateTimeAxis *axisX;
	QValueAxis *axisY;

private:
	Ui::MainWindowClass ui;
public slots:
	void onConnect();
	void onRecved(QByteArray barr);
	void onDisconnect();
	void onButtonKline();
private:
	QByteArray gUncompress(const QByteArray &data);

};
