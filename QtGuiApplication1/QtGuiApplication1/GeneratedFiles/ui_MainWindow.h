/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_7;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_8;
    QPushButton *pushButton_13;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_14;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QTextEdit *textEdit;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QComboBox *comboBox;
    QLabel *label_6;
    QComboBox *comboBox_2;
    QLabel *label_7;
    QLineEdit *lineEdit_5;
    QLabel *label_8;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLabel *label_9;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(866, 711);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout_2->addWidget(pushButton_7, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 0, 2, 1, 1);

        pushButton_9 = new QPushButton(groupBox_2);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout->addWidget(pushButton_9, 1, 0, 1, 1);

        pushButton_10 = new QPushButton(groupBox_2);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        gridLayout->addWidget(pushButton_10, 1, 1, 1, 1);

        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout->addWidget(pushButton_8, 1, 2, 1, 1);

        pushButton_13 = new QPushButton(groupBox_2);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));

        gridLayout->addWidget(pushButton_13, 2, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setEnabled(false);

        gridLayout->addWidget(lineEdit_3, 3, 1, 1, 2);

        pushButton_14 = new QPushButton(groupBox_2);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));

        gridLayout->addWidget(pushButton_14, 2, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 0, 2, 2, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 2);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout_2->addWidget(textEdit, 2, 0, 1, 4);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        formLayout_2 = new QFormLayout(groupBox_3);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        comboBox = new QComboBox(groupBox_3);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, comboBox);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_6);

        comboBox_2 = new QComboBox(groupBox_3);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, comboBox_2);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_7);

        lineEdit_5 = new QLineEdit(groupBox_3);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lineEdit_5);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_8);

        lineEdit_6 = new QLineEdit(groupBox_3);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, lineEdit_6);

        lineEdit_7 = new QLineEdit(groupBox_3);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, lineEdit_7);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_9);


        gridLayout_2->addWidget(groupBox_3, 0, 3, 2, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 866, 23));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);
        QObject::connect(pushButton, SIGNAL(clicked(bool)), MainWindowClass, SLOT(onConnect()));
        QObject::connect(pushButton_7, SIGNAL(clicked(bool)), MainWindowClass, SLOT(onDisconnect()));
        QObject::connect(pushButton_3, SIGNAL(clicked(bool)), MainWindowClass, SLOT(onButtonKline()));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindowClass", "\350\277\236\346\216\245", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindowClass", "\346\226\255\345\274\200", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindowClass", "\345\221\275\344\273\244", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindowClass", "KLine", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindowClass", "Market Depth", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindowClass", "Trade Detail", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindowClass", "Market Detail", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("MainWindowClass", "Market Tickers", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindowClass", "Accounts", Q_NULLPTR));
        pushButton_13->setText(QApplication::translate("MainWindowClass", "Orders", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindowClass", "\346\214\207\344\273\244", Q_NULLPTR));
        pushButton_14->setText(QApplication::translate("MainWindowClass", "Account List", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindowClass", "\347\224\250\346\210\267", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindowClass", "ACCESS KEY", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindowClass", "SRCUTITY KEY", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindowClass", "\345\217\202\346\225\260", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindowClass", "\345\221\250\346\234\237", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "1min", Q_NULLPTR)
         << QApplication::translate("MainWindowClass", "15min", Q_NULLPTR)
         << QApplication::translate("MainWindowClass", "30min", Q_NULLPTR)
         << QApplication::translate("MainWindowClass", "1hour", Q_NULLPTR)
         << QApplication::translate("MainWindowClass", "4hour", Q_NULLPTR)
         << QApplication::translate("MainWindowClass", "1day", Q_NULLPTR)
        );
        label_6->setText(QApplication::translate("MainWindowClass", "\351\227\264\351\232\224", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "500ms", Q_NULLPTR)
         << QApplication::translate("MainWindowClass", "1000ms", Q_NULLPTR)
        );
        label_7->setText(QApplication::translate("MainWindowClass", "\344\273\243\347\220\206", Q_NULLPTR));
        lineEdit_5->setInputMask(QApplication::translate("MainWindowClass", "000.000.000.000", Q_NULLPTR));
        lineEdit_5->setText(QApplication::translate("MainWindowClass", "127.0.0.1", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindowClass", "\347\253\257\345\217\243", Q_NULLPTR));
        lineEdit_6->setText(QApplication::translate("MainWindowClass", "1080", Q_NULLPTR));
        lineEdit_7->setText(QApplication::translate("MainWindowClass", "btcusdt", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindowClass", "\344\272\244\346\230\223\345\257\271", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
