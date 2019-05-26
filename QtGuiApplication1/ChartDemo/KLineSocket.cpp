#include "KLineSocket.h"
#include <QDebug>
#include "gzip.h"
#include <QMetaEnum>
#include <QTimer>
//1min, 5min, 15min, 30min, 60min, 4hour,1day, 1mon, 1week, 1year
QList<QString> KLineSocket::period_str_list = {"1min","5min","15min","30min","60min","4hour","1day","1week","1mon","1year"};

KLineSocket::KLineSocket(QString exchangePair, Period period, QObject *parent)
	: QObject(parent),exchange_pair(exchangePair),m_period(period)
{
	
	qDebug() << QThread::currentThread();
	websocket = new QWebSocket;
	m_thread = new QThread;
	connect(m_thread, &QThread::started, [&] {
		websocket->setProxy({ QNetworkProxy::Socks5Proxy,"127.0.0.1",1080 });
		websocket->open(QUrl("wss://api.huobi.pro/ws"));
	});

	m_thread->start();
	this->moveToThread(m_thread);
	websocket->moveToThread(m_thread);
	
	
	connect(websocket, &QWebSocket::connected,this,&KLineSocket::onConnect,Qt::QueuedConnection);
	connect(websocket, &QWebSocket::disconnected,this, &KLineSocket::onDisconnect, Qt::QueuedConnection);
	connect(websocket, &QWebSocket::binaryMessageReceived, this, &KLineSocket::onRecvMessage);
}

KLineSocket::~KLineSocket()
{
}



void KLineSocket::onChangePeriod(Period period)
{
	m_period = period;
	static QString sub_str_f = R"({ "req": "market.%1.kline.%2","id": "id10"})";
	QString sub_str = sub_str_f.arg(exchange_pair).arg(period_str_list[m_period]);
	websocket->sendTextMessage(sub_str);
}

void KLineSocket::onChangeExchangePair(QString exchangepair)
{
	exchange_pair = exchangepair;
	static QString sub_str_f = R"({ "req": "market.%1.kline.%2","id": "id10"})";
	QString sub_str = sub_str_f.arg(exchange_pair).arg(period_str_list[m_period]);
	websocket->sendTextMessage(sub_str);
}

void KLineSocket::onRecvMessage(QByteArray barr)
{
	QByteArray de_barr = gUncompress(barr);
	QJsonDocument doc = QJsonDocument::fromJson(de_barr);
	QJsonObject obj = doc.object();

	//保持连接
	if (obj.contains("ping"))
	{
		static QString ret = R"({"pong":%1})";
		long long stmap = obj["ping"].toDouble();
		websocket->sendTextMessage(ret.arg(ret));
		return;
	}

	if (obj.contains("data"))
	{
		//全部更新了
		emit changeDate(obj);

		//然后开始订阅
		static QString sub_str_f = R"({"sub": "market.%1.kline.%2","id": "id1"})";
		QString sub_str = sub_str_f.arg(exchange_pair).arg(period_str_list[m_period]);
		websocket->sendTextMessage(sub_str);
	}
	else if (obj.contains("status"))
	{
		//判断是否为ok
		if (obj["status"].toString() != "ok")
		{
			qDebug() << "not ok";
		}
	}
	else if (obj.contains("tick"))
	{
		auto tick = obj["tick"].toObject();
		//有新增数据
		emit addKline(tick);
		//判断是否为同一个K线柱 TODO 
	}
}

void KLineSocket::onConnect()
{
	qDebug() << "connected\n request Kline";
	static QString sub_str_f = R"({ "req": "market.%1.kline.%2","id": "id10"})";
	QString sub_str = sub_str_f.arg(exchange_pair).arg(period_str_list[m_period]);
	websocket->sendTextMessage(sub_str);
}

void KLineSocket::onDisconnect()
{
	qDebug() << "disconnect";
}
