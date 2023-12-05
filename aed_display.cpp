#include "aed_display.h"
#include "ui_aed_display.h"

#include <filesystem>
#include <iostream>
#include <unistd.h>
#include <QDebug>
#include <QPixmap>
#include <QLabel>





AED_Display::AED_Display(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AED_Display)
{
    ui->setupUi(this);
    this->setWindowTitle("AED Device");

    // Set the image label for all the stages of the AED
    setLabelImage(ui->a_responsiveness, ":/res/Check_Responsiveness.png", 150, 150);
    setLabelImage(ui->attach_pads, ":/res/Attach_Electrode.png", 150, 150);
    setLabelImage(ui->a_help, ":/res/Ambulance_Step.png", 150, 150);
    setLabelImage(ui->a_cpr,  ":/res/CPR_Breath.PNG", 150, 150);
    setLabelImage(ui->a_cpr_2,  ":/res/CPR_Compressions.PNG", 150, 150);
    setLabelImage(ui->a_standclear,  ":/res/Stand_Clear.png", 150, 150);
    setLabelImage(ui->a_heart,  ":/res/AED_Heart.png", 150, 150);

    // Set timer to 0
    ui->timer->setText("00:00");
    // Initialize the device
    device = AED_Device();

    // Initialize the timer
    /*
    update_t = new QTimer(this);
    connect(update_t, SIGNAL(timeout()), this, SLOT(timerUp())); */
    connect(ui->pushButton, SIGNAL (released()), this, SLOT(powerOn())); // connect power button




}

AED_Display::~AED_Display()
{
    delete ui;
}

void AED_Display::powerOn()
{
    // when the power button is pressed the device should power on
    device.powerOn();
    ui->audioMessages->append(QString::fromStdString(device.powerOn()));
    //stopwatch.start();
    //update_t->start(1000);
}
/*
void AED_Display::timerUp()
{
    int c_time = stopwatch.elapsed() / 1000; // time passed in seconds
    ui->timer->setText(QString::fromStdString(std::to_string(c_time)));

} */

void AED_Display::setLabelImage(QLabel *label, const QString &path, int width, int height){
    QPixmap image(path);
    label->setPixmap(image.scaled(width, height, Qt::KeepAspectRatio));

}

