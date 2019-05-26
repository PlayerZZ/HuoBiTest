#include "KLineChart.h"
#include <QMessageBox>
#include <QMetaEnum>

#include <QUrl>
KLineChart::KLineChart(QString exchangePair, KLineSocket::Period period, QWidget *parent)
	: QChartView(parent), candlestickser(new QCandlestickSeries)
{

	
	//this->setEnabled(false);
	//init chart
	
	


	//init websocket
	websocket = new KLineSocket(exchangePair, period);


	//数据处理
	connect(websocket, &KLineSocket::changeDate, this, &KLineChart::onchangeDate,Qt::QueuedConnection);
	connect(websocket, &KLineSocket::addKline, this, &KLineChart::onaddKline,Qt::QueuedConnection);

	
}

void KLineChart::initChart()
{
	auto oldchart = chart;
	chart = new QChart;
	
	setChart(chart);
	if (oldchart)
	{
		delete oldchart;
	}
	
	candlestickser->setIncreasingColor(QColor(Qt::green));
	candlestickser->setDecreasingColor(QColor(Qt::red));
	axisX = new QDateTimeAxis(chart);
	axisX->setFormat("hh:mm");
	axisY = new QValueAxis(chart);
	chart->setAxisX(axisX);
	chart->setAxisY(axisY, candlestickser);
	chart->addSeries(candlestickser);
	candlestickser->attachAxis(axisX);
	candlestickser->attachAxis(axisY);
	auto candlestickSet = candlestickser->sets().size() > 20 ? candlestickser->sets()[candlestickser->sets().size() - 20] : candlestickser->sets()[0];
	axisX->setMin(QDateTime::fromMSecsSinceEpoch(candlestickSet->timestamp()));
}

KLineChart::~KLineChart()
{
}



void KLineChart::onchangeDate(QJsonObject obj)
{
	qDebug() << QThread::currentThread();
	//全部都重新构造
	candlestickser->clear();
	switch (m_period)
	{
	case KLineSocket::MIN1:
	case KLineSocket::MIN5:
	case KLineSocket::MIN15:
	
	case KLineSocket::MIN30:
		axisX->setFormat("hh:mm");
		break;
	case KLineSocket::HOUR1:
		
	case KLineSocket::HOUR4:
		axisX->setFormat("MM-dd hh");
		break;
	case KLineSocket::DAY1:

	case KLineSocket::DAY5:
		
	case KLineSocket::WEEK1:
		axisX->setFormat("MM-dd");
		break;
	case KLineSocket::MON1:
		axisX->setFormat("yyyy-MM");
		break;
	default:
		break;
	}
	auto datas = obj["data"].toArray();
	//初始显示20个
	int s1 = datas.size();
	
	for (int i = 0; i < datas.size(); i++)
	{
		//这里的时间戳是精确到毫秒的 所以int 是不够了 要longlong 
		long long timestamp = datas[i].toObject()["id"].toInt();
		timestamp *= 1000;
		QCandlestickSet *candlestickSet = new QCandlestickSet(timestamp);
		auto t1 = datas[i].toObject()["open"].toDouble();
		auto t2 = datas[i].toObject()["close"].toDouble();
		auto t3 = datas[i].toObject()["high"].toDouble();
		auto t4 = datas[i].toObject()["low"].toDouble();

		candlestickSet->setOpen(t1);
		candlestickSet->setClose(t2);
		candlestickSet->setHigh(t3);
		candlestickSet->setLow(t4);
		candlestickser->append(candlestickSet);
	}
	int s2 = candlestickser->sets().size();
	initChart();


}

void KLineChart::onaddKline(QJsonObject tick)
{
	timestamp_step = 60000;
	switch (m_period)
	{
	case KLineSocket::MIN1:
		break;
	case KLineSocket::MIN5:
		timestamp_step *= 5;
		break;
	case KLineSocket::MIN15:
		timestamp_step *= 15;
		break;
	case KLineSocket::MIN30:
		timestamp_step *= 30;
		break;
	case KLineSocket::HOUR1:
		timestamp_step *= 60;
		break;
	case KLineSocket::HOUR4:
		timestamp_step *= 60 * 4;
		break;
	case KLineSocket::DAY1:
		timestamp_step *= 60 * 24;
		break;
	case KLineSocket::DAY5:
		timestamp_step *= 60 * 24 * 5;
		break;
	case KLineSocket::WEEK1:
		timestamp_step *= 60 * 24 * 7;
		break;
	case KLineSocket::MON1:
		//这个就不好算了……毕竟每个月的step不相同 先粗略的用 30天好了
		timestamp_step *= 60 * 24 * 30;
		break;
	default:
		break;
	}

	//否则更新 插入
	long long timestamp = tick["id"].toInt();
	timestamp *= 1000;
	auto t1 = timestamp / timestamp_step;
	auto t2 = candlestickser->sets().last()->timestamp() / timestamp_step;
	if (timestamp / timestamp_step == candlestickser->sets().last()->timestamp() / timestamp_step)
	{
		//更新
		//同一分跟更新
		candlestickser->sets().last()->setHigh(tick["high"].toDouble());
		candlestickser->sets().last()->setLow(tick["low"].toDouble());
		candlestickser->sets().last()->setOpen(tick["open"].toDouble());
		candlestickser->sets().last()->setClose(tick["close"].toDouble());
	}
	else {
		QCandlestickSet *candlestickSet = new QCandlestickSet(timestamp);
		auto t1 = tick["open"].toDouble();
		candlestickSet->setOpen(tick["open"].toDouble());
		candlestickSet->setHigh(tick["high"].toDouble());
		candlestickSet->setLow(tick["low"].toDouble());
		candlestickSet->setClose(tick["close"].toDouble());
		candlestickser->append(candlestickSet);
	}

	//更新坐标
	axisX->setMax(QDateTime::fromMSecsSinceEpoch(timestamp).addSecs(120));
	auto slist = candlestickser->sets();
	QList<double> high_list;
	auto maxone = std::max_element(slist.begin(), slist.end(), [&](QCandlestickSet * a, QCandlestickSet* b) {
		high_list << (a->high());
		return a->high() < b->high();
	});
	double high_one = (**maxone).high();
	auto minone = std::min_element(slist.begin(), slist.end(), [](QCandlestickSet* a, QCandlestickSet* b) {
		return a->low() < b->low();
	});
	//shit 它指向的是指针，所以只有一个解引用的话，还真的是用不了……
	axisY->setRange((**minone).low(), (**maxone).high());

}



void KLineChart::wheelEvent(QWheelEvent *event)
{
	auto dt1 = axisX->min();
	if (event->delta()>0)
	{
		dt1 = dt1.addMSecs(timestamp_step);
	}
	else {
		dt1 = dt1.addMSecs(-timestamp_step);
	}
	axisX->setMin(dt1);
}

void KLineChart::onChangePeriod(KLineSocket::Period period)
{
	m_period = period;
	websocket->changePeriod(m_period);
}



void KLineChart::onChangeExchangePair(QString exchangepair)
{
	exchange_pair = exchangepair;
	websocket->changeExchangePair(exchange_pair);
}

//理想情况 这个是运行在分线程的……
