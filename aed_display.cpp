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


    // Add shock button

    ui->shock_button->setIcon(QIcon(":/res/AED_Heart.png"));
    ui->shock_button->setFixedSize(210,210);
    ui->shock_button->setIconSize(QSize(210,210));
    ui->shock_button->setEnabled(false); // disable this button until shockable rhythm is found.


    // Set timer to 0
    ui->timer->setText("00:00");
    // Initialize the device
    device = AED_Device();
    step_timer = new QTimer(this);

    //Initialize the number of shocks
    shock_count = 0;

    // Initialize the timer
    /*
    update_t = new QTimer(this);
    connect(update_t, SIGNAL(timeout()), this, SLOT(timerUp())); */
    connect(ui->pushButton, SIGNAL (released()), this, SLOT(powerOn())); // connect power button
    connect(ui->shock_button, SIGNAL (released()), this, SLOT(display_shock())); // connect power button

}

AED_Display::~AED_Display()
{
    delete ui;
    delete step_timer;
}

void AED_Display::powerOn()
{
    // when the power button is pressed the device should power on
    ui->pushButton->setEnabled(false);
    displaytimer.start();
    //my thought proccess: I wanted a way to display the messages one at a time. starting from "Starting AED".
    // should probably clear the screen afterwards.
    QString aed_status = "Starting AED...\nAED self test complete\nDevice is operational and ready to use";
    std::string message = device.powerOn();
    QStringList lines = aed_status.split("\n");

    ui->audioMessages->append("::Unit OK.\n::Stay Calm"); // Audio messages played for starting the AED

    if(message.find("Device is operational") != std::string::npos){

        ui->LCDScreen->append("\n" + lines.at(0));
        QTimer::singleShot(1000, [=]{
            ui->LCDScreen->append(lines.at(1));

            QTimer::singleShot(1000, [=]{
                ui->LCDScreen->append(lines.at(2));

                QTimer::singleShot(1000, [=]{
                    ui->LCDScreen->clear();

                    connect(step_timer, &QTimer::timeout, this, &AED_Display::nextAEDStep);
                    step_timer->start(5000);

                    timerUp();

                });

            });
        });
    }
}


void AED_Display::timerUp()
{
    qint64 c_time = displaytimer.elapsed() / 1000; // time passed in seconds
    ui->timer->setText(QString::fromStdString(std::to_string(c_time)));

}

void AED_Display::setLabelImage(QLabel *label, const QString &path, int width, int height){
    QPixmap image(path);
    label->setPixmap(image.scaled(width, height, Qt::KeepAspectRatio));

}

/*Note: Figure out a way to end once last stage is reached
This function handles the AED step progression
It updates a displayImage at each step and displays the final message

Status: Complete!

@TODO: Put the respective audio for each stage too
*/
void AED_Display::nextAEDStep(){
  QString displayMessage;
  switch (currentStep){
    case CheckResponsiveness:
    displayMessage = "CHECK RESPONSIVENESS!";
    ui->audioMessages->append("::Check Responsiveness.");
    break;
    case CallForHelp:
    displayMessage = "CALL FOR HELP!";
    ui->audioMessages->append("::Call for help.");
    break;
    case AttachElectrodes:
    displayMessage = "ATTACH ELECTRODES TO CHEST";
    ui->audioMessages->append("::Attach defib pads to patient's bare chest.");
    break;
    case StandClear:
    displayMessage = "ANALYSING PATIENT..";
    ui->audioMessages->append("::Don't touch patient. Analyzing."); // Audio messages played for Standing Clear
    QTimer::singleShot(3000, [=]{
        d_waveform(); // called after stand clear for analysis of the patient
        if(detect.isShockable()){
          currentStep = StandClearShock;
        }else{
          currentStep = CPRBreathing;
        }
    });
    break;
    case StandClearShock:
    displayMessage = "STAND CLEAR (Shock Warning)\nDO NOT touch patient.";
    ui->audioMessages->append("::Shock will be delivered in three, two, one");
    step_timer->stop(); // let the timer stop and then resume after the next audio message
    QTimer::singleShot(3000, [=]{
        ui->audioMessages->append("::Shock tone beeps. Shock Delivered");
        step_timer->start(5000);

    });
    break;
    case CPRBreathing:
    displayMessage = "BEGIN CPR";
    ui->audioMessages->append("::Start CPR.");
    break;
    case CheckCompressions:
    displayMessage = "START CPR BREATHING";
    break;
  }
  ui->LCDScreen->setText(displayMessage + "\n\n");
  ui->LCDScreen->setAlignment(Qt::AlignCenter);

  if (currentStep == CheckCompressions){
    currentStep = CheckResponsiveness;
    step_timer->stop();
  }else{
    std::cout <<"[AED NEXT STEP] Inside the switch statement" << std::endl;
    std::cout<<"Here is the value of current step" <<std::endl;
    currentStep = static_cast<Step>(static_cast<int>(currentStep) + 1);
    std::cout<< currentStep << std::endl;
  }
}

void AED_Display::display_shock()
{ // When the shock button is clicked this function is called
    ++shock_count;
    device.setChargeLevel(device.getchargeLevel()-3);
    QString shock_count_string =  QString("shock: %1").arg(shock_count);
    ui->shockCount->setText(shock_count_string);
    ui->progressBar->setValue(device.getchargeLevel());
    qDebug() << "Here is the value of charge level: " << device.getchargeLevel();
    qDebug() << "Here is the value of shock count: " << shock_count;
    step_timer->start(100); // Restart the timer again.
    ui->shock_button->setEnabled(false); // The shock button should not do anything unless another shockable rhythm is found
}

void AED_Display::d_waveform()
{
    rhythm = detect.detectHeartRhythm();
    std::cout<<"Here is the value of rhythm " + std::to_string(rhythm)<<std::endl;
    if(rhythm == 0){ // Ventricular Fibrillation
        setLabelImage(ui->waveform,  ":/Waveforms/Ventricular Fibrillation.PNG",361, 200);
        ui->waveform_type->setText("Ventricular Fibrillation");

    }
    else if(rhythm == 1){ // Ventricular Tachycardia
        setLabelImage(ui->waveform,  ":/Waveforms/Ventricular Tachycardia.PNG", 361, 200);
        ui->waveform_type->setText("Ventricular Tachycardia");
    }
    else if(rhythm == 2){ // ASYSTOLE
        setLabelImage(ui->waveform,  ":/Waveforms/Asystole.PNG", 361, 200);
        ui->waveform_type->setText("ASYSTOLE");
    }
    else{ // Sinus Rhythm or Pulseless Electrical Activity
        setLabelImage(ui->waveform,  ":/Waveforms/Sinus Rhythm or Pulseless Electrical Activity.PNG", 361, 200);
        ui->waveform_type->setText("Sinus Rhythm or Pulseless Electrical Activity");
    }
    ui->waveform_type->setAlignment(Qt::AlignCenter);

    // Checking if the rhythm is shockable and if so displaying the corresponding audio messages
    if(!detect.isShockable()){
        ui->audioMessages->append("::No shock advised");
    }
    else{ // if the detected rhythm is shockable
        ui->shock_button->setEnabled(true);
        step_timer->stop(); // Stop steps timer to allow the user to click the shock button
    }


}
