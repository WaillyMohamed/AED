#include "aed_display.h"
#include "ui_aed_display.h"
#include <filesystem>
#include <iostream>
#include <unistd.h>
#include <QDebug>

AED_Display::AED_Display(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AED_Display)
{
    ui->setupUi(this);
    // Get current directory
    char temp[256];
    getcwd(temp, 256);
    std::string path = std::string(temp) + "/AED_Design.png"; // Display Interface
    QString url = QString::fromStdString(":/images/AED_Design.png");
    QPixmap img(url);
    ui->label->setPixmap(url);

    connect(ui->pushButton, SIGNAL (released()), this, SLOT(powerOn())); // connect power button


}

AED_Display::~AED_Display()
{
    delete ui;
}

void AED_Display::powerOn()
{

}

