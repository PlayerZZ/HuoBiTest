#pragma once

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QThread>
#include <QNetworkRequest>
#include <QWebSocket>
#include <QNetworkProxy>
#include <QList>

class KLineSocket : public QObject
{
	Q_OBJECT

public:
	enum Period {
		MIN1,
		MIN5,
		MIN15,
		MIN30,
		HOUR1,
		HOUR4,
		DAY1,
		DAY5,
		WEEK1,
		MON1
	};
	Q_ENUM(Period)
	KLineSocket(QString exchangePair="btcusdt", Period period = MIN1, QObject *parent=nullptr);
	~KLineSocket();
	
private:
	QWebSocket *websocket;//单独的websocket 方便分线程获取数据
	QNetworkProxy proxy;
	QThread *m_thread;
	static QList<QString> period_str_list;
signals:
	void changePeriod(KLineSocket::Period period);
	void changeExchangePair(QString exchangepair);
	void changeDate(QJsonObject obj);
	void addKline(QJsonObject obj);
private slots:
	void onChangePeriod(KLineSocket::Period period);
	void onChangeExchangePair(QString exchangepair);
	void onRecvMessage(QByteArray barr);
	void onConnect();
	void onDisconnect();
public:
	QString exchange_pair;
	Period m_period;
};
