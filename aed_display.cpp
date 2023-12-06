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
    , ui(new Ui::AED_Display),
    currentStep(CheckResponsiveness) //initialize the current step -> check responsiveness
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
    step_timer = new QTimer(this);

    // Initialize the timer
    /*
    update_t = new QTimer(this);
    connect(update_t, SIGNAL(timeout()), this, SLOT(timerUp())); */
    connect(ui->pushButton, SIGNAL (released()), this, SLOT(powerOn())); // connect power button




}

AED_Display::~AED_Display()
{
    delete ui;
    delete step_timer;
}

void AED_Display::powerOn()
{
    // when the power button is pressed the device should power on

    //my thought proccess: I wanted a way to display the messages one at a time. starting from "Starting AED".
    // should probably clear the screen afterwards. can remove if unneccessary
    QString aed_status = "Starting AED...\nAED self test complete\nDevice is operational and ready to use";
    std::string message = device.powerOn();
    QStringList lines = aed_status.split("\n");

    ui->audioMessages->append(QString::fromStdString(device.powerOn()));
    if(message.find("Device is operational") != std::string::npos){

        ui->LCDScreen->append(lines.at(0));
        QTimer::singleShot(1000, [=]{
            ui->LCDScreen->append(lines.at(1));

            QTimer::singleShot(1000, [=]{
                ui->LCDScreen->append(lines.at(2));

                connect(step_timer, &QTimer::timeout, this, &AED_Display::nextAEDStep);
                step_timer->start(5000);
            });
        });


    }
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

/*Note: Figure out a way to end once last stage is reached
This function handles the AED step progression
It updates a displayImage at each step and displays the final message
There has to be a better way?
*/
void AED_Display::nextAEDStep(){
  QString displayMessage;
  switch (currentStep){
    case CheckResponsiveness:
    displayMessage = "CHECK RESPONSIVENESS!";
    break;
    case CallForHelp:
    displayMessage = "CALL FOR HELP!";
    break;
    case AttachElectrodes:
    displayMessage = "ATTACH ELECTRODES TO PATIENT'S CHEST";
    break;
    case StandClear:
    displayMessage = "STAND CLEAR";
    break;
    case CPRBreathing:
    displayMessage = "BEGIN CPR";
    break;

    case CheckCompressions:
    displayMessage = "START CPR BREATHING";
    break;
  }
  ui->LCDScreen->append(displayMessage);

  if (currentStep == CheckCompressions){
    currentStep = CheckResponsiveness;
  }else{
    std::cout <<"[AED NEXT STEP] Inside the switch statement" << std::endl;
    std::cout<<"Here is the value of current step" <<std::endl;
    currentStep = static_cast<Step>(static_cast<int>(currentStep) + 1);
    std::cout<< currentStep << std::endl;
  }
}
