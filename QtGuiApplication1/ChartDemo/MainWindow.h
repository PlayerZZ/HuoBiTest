#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "KLineChart.h"
#include <QHBoxLayout>	
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainWindowClass ui;
};
