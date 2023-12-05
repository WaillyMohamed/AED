/********************************************************************************
** Form generated from reading UI file 'aed_display.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AED_DISPLAY_H
#define UI_AED_DISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AED_Display
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTextBrowser *LCDScreen;
    QLabel *a_responsiveness;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QLabel *attach_pads;
    QLabel *a_help;
    QLabel *a_cpr;
    QLabel *a_standclear;
    QLabel *a_heart;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AED_Display)
    {
        if (AED_Display->objectName().isEmpty())
            AED_Display->setObjectName(QString::fromUtf8("AED_Display"));
        AED_Display->resize(1200, 800);
        centralwidget = new QWidget(AED_Display);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 1029, 652));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(1031, 16777215));
        label->setBaseSize(QSize(1029, 65));
        LCDScreen = new QTextBrowser(centralwidget);
        LCDScreen->setObjectName(QString::fromUtf8("LCDScreen"));
        LCDScreen->setGeometry(QRect(330, 190, 291, 191));
        a_responsiveness = new QLabel(centralwidget);
        a_responsiveness->setObjectName(QString::fromUtf8("a_responsiveness"));
        a_responsiveness->setGeometry(QRect(50, 230, 150, 120));
        a_responsiveness->setMinimumSize(QSize(150, 120));
        a_responsiveness->setLineWidth(1);
        a_responsiveness->setAlignment(Qt::AlignCenter);
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 670, 261, 51));
        progressBar->setValue(100);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(700, 660, 161, 71));
        pushButton->setIconSize(QSize(10, 10));
        attach_pads = new QLabel(centralwidget);
        attach_pads->setObjectName(QString::fromUtf8("attach_pads"));
        attach_pads->setGeometry(QRect(690, 220, 150, 120));
        attach_pads->setMinimumSize(QSize(150, 120));
        attach_pads->setLineWidth(1);
        attach_pads->setAlignment(Qt::AlignCenter);
        a_help = new QLabel(centralwidget);
        a_help->setObjectName(QString::fromUtf8("a_help"));
        a_help->setGeometry(QRect(390, 10, 150, 120));
        a_help->setMinimumSize(QSize(150, 120));
        a_help->setLineWidth(1);
        a_help->setAlignment(Qt::AlignCenter);
        a_cpr = new QLabel(centralwidget);
        a_cpr->setObjectName(QString::fromUtf8("a_cpr"));
        a_cpr->setGeometry(QRect(120, 470, 181, 121));
        a_cpr->setMinimumSize(QSize(150, 120));
        a_cpr->setLineWidth(1);
        a_cpr->setAlignment(Qt::AlignCenter);
        a_standclear = new QLabel(centralwidget);
        a_standclear->setObjectName(QString::fromUtf8("a_standclear"));
        a_standclear->setGeometry(QRect(670, 430, 150, 131));
        a_standclear->setMinimumSize(QSize(150, 120));
        a_standclear->setLineWidth(1);
        a_standclear->setAlignment(Qt::AlignCenter);
        a_heart = new QLabel(centralwidget);
        a_heart->setObjectName(QString::fromUtf8("a_heart"));
        a_heart->setGeometry(QRect(400, 430, 150, 131));
        a_heart->setMinimumSize(QSize(150, 120));
        a_heart->setLineWidth(1);
        a_heart->setAlignment(Qt::AlignCenter);
        AED_Display->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AED_Display);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1200, 22));
        AED_Display->setMenuBar(menubar);
        statusbar = new QStatusBar(AED_Display);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AED_Display->setStatusBar(statusbar);

        retranslateUi(AED_Display);

        QMetaObject::connectSlotsByName(AED_Display);
    } // setupUi

    void retranslateUi(QMainWindow *AED_Display)
    {
        AED_Display->setWindowTitle(QCoreApplication::translate("AED_Display", "AED_Display", nullptr));
        label->setText(QString());
        a_responsiveness->setText(QCoreApplication::translate("AED_Display", "Ok?", nullptr));
        pushButton->setText(QCoreApplication::translate("AED_Display", "POWER", nullptr));
        attach_pads->setText(QCoreApplication::translate("AED_Display", "Attach", nullptr));
        a_help->setText(QCoreApplication::translate("AED_Display", "Help", nullptr));
        a_cpr->setText(QCoreApplication::translate("AED_Display", "CPR", nullptr));
        a_standclear->setText(QCoreApplication::translate("AED_Display", "Stand Clear", nullptr));
        a_heart->setText(QCoreApplication::translate("AED_Display", "AED_Heart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AED_Display: public Ui_AED_Display {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AED_DISPLAY_H
