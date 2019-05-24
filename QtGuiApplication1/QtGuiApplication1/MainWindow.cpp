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
	QString filename = QDateTime::currentDateTime().toString("yyyy_MM_dd_HH_mm_ss_zzz") + ".json";
	QFile f_t(filename);
	f_t.open(QIODevice::WriteOnly);
	f_t.write(de_barr);
	int i = 0;
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
