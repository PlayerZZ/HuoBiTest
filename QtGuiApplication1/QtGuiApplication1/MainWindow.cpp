#include "MainWindow.h"
#include <QMessageBox>
#include <QSslError>
#include <QList>
#include <QUrl>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QFile>
#include <QMetaEnum>
#include <QHBoxLayout>
#include <algorithm>

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
	//error(QAbstractSocket::SocketError error)
	connect(&websocket, static_cast< void (QWebSocket::*) (QAbstractSocket::SocketError)>(&QWebSocket::error)
		, this, [&](QAbstractSocket::SocketError error) {
		//把枚举翻译成 string
		QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
		QMessageBox::warning(0, "SSL error", metaEnum.valueToKey(error));
	});
	connect(&websocket, &QWebSocket::binaryMessageReceived, this, &MainWindow::onRecved);
	//设置代理
	proxy.setHostName(ui.lineEdit_5->text());
	proxy.setPort(ui.lineEdit_6->text().toInt());
	websocket.setProxy(proxy);

	QHBoxLayout *layout = new QHBoxLayout(ui.widget);
	chartview = new QChartView(ui.widget);
	layout->addWidget(chartview);
	ui.widget->setLayout(layout);

	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("VirtualCurrency.db");
	if (!database.open())
	{
		QMessageBox::warning(this, "database error", "open error");
		exit(0);
	}
	//图表
	chart = new QChart;
	acmeSeries = new QCandlestickSeries;
	axisX = new QDateTimeAxis;
	axisY = new QValueAxis;
	axisX->setFormat("hh:mm");
	
	chartview->setChart(chart);
	acmeSeries->setIncreasingColor(QColor(Qt::green));
	acmeSeries->setDecreasingColor(QColor(Qt::red));
	
	chart->setAxisX(axisX, acmeSeries);
	chart->setAxisY(axisY, acmeSeries);
	chart->addSeries(acmeSeries);

	acmeSeries->attachAxis(axisX);
	acmeSeries->attachAxis(axisY);
}

void MainWindow::onConnect()
{
	websocket.open(QUrl("wss://api.huobi.pro/ws"));
}

void MainWindow::onRecved(QByteArray barr)
{
	QByteArray de_barr = gUncompress(barr);
	QJsonDocument doc = QJsonDocument::fromJson(de_barr);
	QJsonObject obj = doc.object();

	//保持连接
	if (obj.contains("ping"))
	{
		static QString ret = R"({"pong":%1})";
		long long stmap = obj["ping"].toDouble();
		websocket.sendTextMessage(ret.arg(ret));
		return;
	}
	

	

	//线取前10个数据显示下
	if (obj.contains("data"))
	{
		auto datas = obj["data"].toArray();
		for (int i = datas.size()-10; i < datas.size(); i++)
		{
			//这里的时间戳是精确到毫秒的 所以int 是不够了 要longlong 
			long long timestamp = datas[i].toObject()["id"].toInt();
			timestamp *= 1000;
			QCandlestickSet *candlestickSet = new QCandlestickSet(timestamp);
			candlestickSet->setOpen(datas[i].toObject()["open"].toDouble());
			candlestickSet->setHigh(datas[i].toObject()["high"].toDouble());
			candlestickSet->setLow(datas[i].toObject()["low"].toDouble());
			candlestickSet->setClose(datas[i].toObject()["close"].toDouble());
			acmeSeries->append(candlestickSet);
		}
		//需要更新坐标轴的显示区域
		axisX->setMin(QDateTime::fromMSecsSinceEpoch(acmeSeries->sets().first()->timestamp()).addSecs(-120));
		axisX->setMax(QDateTime::fromMSecsSinceEpoch(acmeSeries->sets().last()->timestamp()).addSecs(120));
		auto slist = acmeSeries->sets();
		auto maxone = std::max_element(slist.begin(), slist.end(), [](QCandlestickSet * a, QCandlestickSet* b) {
			return a->high() > b->high();
		});
		auto minone = std::min_element(slist.begin(), slist.end(), [](QCandlestickSet* a, QCandlestickSet* b) {
			return a->low() < b->low();
		});
		//shit 它指向的是指针，所以只有一个解引用的话，还真的是用不了……
		axisY->setMin((**minone).low() - 10);
		axisY->setMax((**maxone).high() + 20);
		
		//然后开始订阅 插入到数据库
		static QString sub_str_f = R"({"sub": "market.%1.kline.%2","id": "id1"})";
		QString sub_str = sub_str_f.arg(ui.lineEdit_7->text()).arg(ui.comboBox->currentText());
		websocket.sendTextMessage(sub_str);
	} else if (obj.contains("status"))
	{
		//判断是否为ok
		if (obj["status"].toString()!="ok")
		{
			QMessageBox::warning(this, "sub error", "not ok");
		}

	} else if (obj.contains("tick"))
	{
		auto tick = obj["tick"].toObject();
		static QString query_str_f("insert into %1 (timestamp , high , low ,open ,close ,amount ,volume ,count ) values (%2,%3,%4,%5,%6,%7,%8,%9)");
		QString query_str = query_str_f.arg(ui.lineEdit_7->text()).arg(tick["id"].toInt()).arg(QString::number(tick["high"].toDouble())).arg(QString::number(tick["low"].toDouble()))
			.arg(QString::number(tick["open"].toDouble())).arg(QString::number(tick["close"].toDouble()))
			.arg(QString::number(tick["amount"].toDouble())).arg(QString::number(tick["vol"].toDouble())).arg(tick["count"].toInt());
		QSqlQuery query;
		if (!query.exec(query_str))
		{
			//QMessageBox::warning(this, "database error", "insert failed");
			auto a = query.lastError();
			auto b  = a.text();
			int i = 0;
		}
		//看更新时间是否跟现在是同一分的
		
		if (acmeSeries->sets().last()->timestamp() / 60000 == tick["id"].toInt() / 60)
		{
			//同一分跟更新
			acmeSeries->sets().last()->setHigh(tick["high"].toDouble());
			acmeSeries->sets().last()->setLow(tick["low"].toDouble());
			acmeSeries->sets().last()->setOpen(tick["open"].toDouble());
			acmeSeries->sets().last()->setClose(tick["close"].toDouble());
			
		}
		else {
			//否则更新 插入
			long long timestamp = tick["id"].toInt();
			timestamp *= 1000;
			QCandlestickSet *candlestickSet = new QCandlestickSet(timestamp);
			candlestickSet->setOpen(tick["open"].toDouble());
			candlestickSet->setHigh(tick["high"].toDouble());
			candlestickSet->setLow(tick["low"].toDouble());
			candlestickSet->setClose(tick["close"].toDouble());
			acmeSeries->append(candlestickSet);
			//更新坐标
			axisX->setMax(QDateTime::fromMSecsSinceEpoch(timestamp).addSecs(120));
// 			auto slist = acmeSeries->sets();
// 			auto maxone = std::max_element(slist.begin(), slist.end(), [](QCandlestickSet * a, QCandlestickSet* b) {
// 				return (*a).high() > b->high();
// 			});
// 			auto minone = std::min_element(slist.begin(), slist.end(), [](QCandlestickSet* a, QCandlestickSet* b) {
// 				return a->low() < b->low();
// 			});
// 			//shit 它指向的是指针，所以只有一个解引用的话，还真的是用不了……
// 			axisY->setRange((**minone).low() - 200, (**maxone).high() + 200);

		}
		
		
		
	}
	
}

void MainWindow::onDisconnect()
{
	websocket.close();
}

void MainWindow::onButtonKline()
{
	QString req_str_fromat = R"({ "req": "market.%1.kline.%2","id": "id10"})";
	QString req_str = req_str_fromat.arg(ui.lineEdit_7->text()).arg(ui.comboBox->currentText());
	websocket.sendTextMessage(req_str);
	//看有没有数据库数据
	static QString create_sql_f = "create table %1 (id INTEGER  primary key AUTOINCREMENT,timestamp int, high varchar(50), low varchar(50),open varchar(50),close varchar(50),amount varchar(50),volume varchar(50),count int)";
	QString create_sql = create_sql_f.arg(ui.lineEdit_7->text());
	QSqlQuery sql_query;
	sql_query.exec(create_sql);
}

QByteArray MainWindow::gUncompress(const QByteArray &data)
{
	if (data.size() <= 4) {
		qWarning("gUncompress: Input data is truncated");
		return QByteArray();
	}

	QByteArray result;

	int ret;
	z_stream strm;
	static const int CHUNK_SIZE = 1024;
	char out[CHUNK_SIZE];

	/* allocate inflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = data.size();
	strm.next_in = (Bytef*)(data.data());

	ret = inflateInit2(&strm, 15 + 32); // gzip decoding
	if (ret != Z_OK)
		return QByteArray();

	// run inflate()
	do {
		strm.avail_out = CHUNK_SIZE;
		strm.next_out = (Bytef*)(out);

		ret = inflate(&strm, Z_NO_FLUSH);
		Q_ASSERT(ret != Z_STREAM_ERROR);  // state not clobbered

		switch (ret) {
		case Z_NEED_DICT:
			ret = Z_DATA_ERROR;     // and fall through
		case Z_DATA_ERROR:
		case Z_MEM_ERROR:
			(void)inflateEnd(&strm);
			return QByteArray();
		}

		result.append(out, CHUNK_SIZE - strm.avail_out);
	} while (strm.avail_out == 0);

	// clean up and return
	inflateEnd(&strm);
	return result;
}
