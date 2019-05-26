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


//����дһ��ͼ��
//1 ���Խ����е�������������
//�����ʾ100��
//Ȼ�󽫷Ŵ���ԷŴ� ��СҲ����
//��ʼ��ʾ20��
class KLineChart : public QChartView
{
	Q_OBJECT

public:
	
	KLineChart(QString exchangePair="btcusdt", KLineSocket::Period period = KLineSocket::Period::MIN1,QWidget *parent=nullptr);

	void initChart();

	~KLineChart();


	public slots:
	void onChangePeriod(KLineSocket::Period period);//��ʹ���ߵ�
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
	void onchangeDate(QJsonObject obj);//���ݸı� �Լ�����
	void onaddKline(QJsonObject obj);

protected:
	virtual void wheelEvent(QWheelEvent *event) override;

};
