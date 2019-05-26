#pragma once

#include <QChartView>

#include <QChart>
#include <QCandlestickSeries>
#include <QCandlestickSet>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QWheelEvent>
#include "KLineSocket.h"


QT_CHARTS_USE_NAMESPACE


//打算写一个图表
//1 可以将所有的数据请求下来
//最多显示100个
//然后将放大可以放大 缩小也可以
//初始显示20个
class KLineChart : public QChartView
{
	Q_OBJECT

public:
	
	KLineChart(QString exchangePair="btcusdt", KLineSocket::Period period = KLineSocket::Period::MIN1,QWidget *parent=nullptr);

	void initChart();

	~KLineChart();


	public slots:
	void onChangePeriod(KLineSocket::Period period);//给使用者调
	void onChangeExchangePair(QString exchangepair);
	
private:
	KLineSocket *websocket;
	QChart *chart=nullptr;
	QValueAxis *axisY;
	QDateTimeAxis *axisX;
	QCandlestickSeries *candlestickser;
	QString exchange_pair;
	KLineSocket::Period m_period;
	qint64 timestamp_step;
private  slots :
	void onchangeDate(QJsonObject obj);//数据改变 自己调用
	void onaddKline(QJsonObject obj);

protected:
	virtual void wheelEvent(QWheelEvent *event) override;

};
