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

    int charge = device.getchargeLevel();

    // Set the image label for all the stages of the AED
    setLabelImage(ui->a_responsiveness, ":/res/Check_Responsiveness.png", 150, 150);
    setLabelImage(ui->attach_pads, ":/res/Attach_Electrode.png", 150, 150);
    setLabelImage(ui->a_help, ":/res/Ambulance_Step.png", 150, 150);
    setLabelImage(ui->a_cpr,  ":/res/CPR_Breath.PNG", 150, 150);
    setLabelImage(ui->a_cpr_2,  ":/res/CPR_Compressions.PNG", 150, 150);
    setLabelImage(ui->a_standclear,  ":/res/Stand_Clear.png", 150, 150);
    ui->progressBar->setValue(charge);


    // Disable buttons for adult or child pad until place electrode step happens
    ui->adult->setEnabled(false);
    ui->child->setEnabled(false);
    ui->attach->setEnabled(false);

    // Add shock button
    ui->shock_button->setIcon(QIcon(":/res/AED_Heart.png"));
    ui->shock_button->setFixedSize(140,140);
    ui->shock_button->setIconSize(QSize(140,140));
    ui->shock_button->setEnabled(false); // disable this button until shockable rhythm is found.
    ui->shockCount->setText("Shock: 0");

    // Set timer to 0
    ui->timer->setText("00:00");
    // Initialize the device
    device = AED_Device();
    pads = AED_Electrode_Pads();

    step_timer = new QTimer(this);
    displaytimer = new QTimer(this); // timer to update the stopwatch
    cpr_compressions = new QTimer(this);
    //Initialize the number of shocks
    shock_count = 0;

    // Initialize the timers
    connect(displaytimer, &QTimer::timeout, this, &AED_Display::updateTimer);
    connect(step_timer, &QTimer::timeout, this, &AED_Display::nextAEDStep);
    connect(cpr_compressions, &QTimer::timeout, this, &AED_Display::cpr_check);

    // Buttons to choose between adult and child pads
    connect(ui->adult, SIGNAL(released()), this, SLOT(adultPads()));
    connect(ui->child, SIGNAL(released()), this, SLOT(childPads()));
    // Button to attach/detach defib pads
    connect(ui->attach, SIGNAL(released()), this, SLOT(pad_placement()));

    connect(ui->pushButton, SIGNAL (released()), this, SLOT(powerOn())); // connect power button
    ui->pushButton->setText("ON"); // Initially set the button on.
    connect(ui->shock_button, SIGNAL (released()), this, SLOT(display_shock())); // connect power button

    // set minimum and maximum for qslider
    ui->horizontalSlider->setMinimum(0); // compression depth minimum 0 inches
    ui->horizontalSlider->setMaximum(40); // max compression 4 inches
    ui->horizontalSlider->setEnabled(false);
    // Set the compression depth slider invisible
    ui->horizontalSlider->setVisible(false);
    connect(ui->horizontalSlider, SIGNAL(sliderReleased()), this, SLOT(cpr_comp_depth()));
}

AED_Display::~AED_Display()
{
    delete ui;
    delete step_timer;
}

void AED_Display::powerOn()
{

    // reaches the if statement
    if(device.getMode() == "ACTIVE"){ // If the AED in an active state
        device.powerOff(); // resets timer and shocks in back-end. Sets to standby status
        ui->pushButton->setText("ON"); // Set power button text to ON while AED is offline
        pads = AED_Electrode_Pads();
        displaytimer->stop();
        cpr_compressions->stop();
        step_timer->stop();
        // Reset visuals
        ui->a_responsiveness->setStyleSheet("");
        ui->attach_pads->setStyleSheet("");
        ui->a_help->setStyleSheet("");
        ui->a_cpr->setStyleSheet("");
        ui->a_cpr_2->setStyleSheet("");
        ui->a_standclear->setStyleSheet("");
        // reset pads
        ui->adult->setEnabled(false);
        ui->child->setEnabled(false);
        ui->attach->setEnabled(false);
        ui->shock_button->setEnabled(false); // disable this button until shockable rhythm is found.
        // Reset pad colors
        ui->adult->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255,255,255);");
        ui->child->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255,255,255);");
        ui->attach->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255,255,255);");
        // Reset display
        ui->shockCount->setText("Shock: 0"); // reset shocks
        ui->timer->setText("00:00"); // reset timer
        shock_count = 0;
        currentStep = CheckResponsiveness;
        // Clear audio and display messages
        ui->audioMessages->clear();
        ui->LCDScreen->clear();
        // Clear waveforms
        ui->waveform->setVisible(false); // Do not display current waveform.
        ui->waveform_type->setVisible(false);

        // Clear cpr depth slider and label
        ui->horizontalSlider->setValue(0);
        ui->horizontalSlider->setVisible(false);
        ui->depth_value->setText("");
    }
    else{
        // when the power button is pressed the device should power on

        if(device.selfTest() == true){
          ui->pushButton->setText("OFF"); // Set power button text to OFF because the program will be active
          displaytimer->start(1000);
          device.powerOn();
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


                          step_timer->start(5000);

                      });

                  });
              });

          }
        }else{
          return;
        }

    }
}


void AED_Display::updateTimer()
{
    // update the amount of seconds and display the minutes and seconds mm:ss
    device.update();
    ui->timer->setText(QString::fromStdString(device.displayTime()));
}

void AED_Display::highlightCurrentStep(QLabel *current_step)
{
  ui->a_responsiveness->setStyleSheet("");
  ui->attach_pads->setStyleSheet("");
  ui->a_help->setStyleSheet("");
  ui->a_cpr->setStyleSheet("");
  ui->a_cpr_2->setStyleSheet("");
  ui->a_standclear->setStyleSheet("");

  current_step->setStyleSheet("border: 2px solid red");

}

void AED_Display::adultPads()
{
    ui->audioMessages->append("::Adult pads have been selected");
    pads.setChild_or_adult(2);
    ui->adult->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(51, 209, 122);");
    ui->child->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255,255,255);");
}

void AED_Display::childPads()
{
    ui->audioMessages->append("::Child pads have been selected");
    pads.setChild_or_adult(1);
    ui->child->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(51, 209, 122);");
    ui->adult->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255,255,255);");
}

void AED_Display::cpr_check()
{
    int compression_depth = device.compressionRate();
    double cv = device.compressionDepth(compression_depth);

    ui->horizontalSlider->setValue(cv);
    std::cout << "Here  is the compression rate " << compression_depth  << std::endl;
    std::cout << "Here  is the compression depth " << cv  << std::endl;
    if (compression_depth == 0){
      ui->LCDScreen->setText("PUSH HARDER \n\n");
      ui->audioMessages->append("::Push harder. Compressions are weak");
    }else if(compression_depth == 1){
      ui->LCDScreen->setText("GOOD COMPRESSIONS \n\n");
      ui->audioMessages->append("::Good compression depth. Begin 2 min CPR");
      cpr_compressions->stop();
      step_timer->start(5000);
    }else if (compression_depth == 2){
      ui->LCDScreen->setText("WEAKEN PUSH \n\n");
      ui->audioMessages->append("::Weaken push. Compressions are too deep");
    }
    ui->LCDScreen->setAlignment(Qt::AlignCenter);
}

void AED_Display::pad_placement()
{
    // Disable the other buttons after attaching them.
    // Check if the pads are already attached
    if(!pads.getStatus()){ // If pads are not placed:
        pads.setStatus(true);
        ui->adult->setEnabled(false);
        ui->child->setEnabled(false);
        ui->audioMessages->append("::Pads have been attached");


        // Move on to the next step
        step_timer->start(5000);
        ui->attach->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(51, 209, 122);");
    }
    else{ // If the pads are already placed and then detached
        ui->audioMessages->append("::Pads have been detached");
        pads.setStatus(false); // detach the defib pads
        pads.setChild_or_adult(0); // Set to default number
        // Allow the buttons to be reselected between child and adult pads
        ui->attach->setEnabled(false);
        ui->adult->setEnabled(true);
        ui->child->setEnabled(true);
        currentStep = AttachElectrodes;
        ui->attach->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 255);");
        ui->child->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 255);");
        ui->adult->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 255);");
        ui->waveform->setVisible(false); // Do not display current waveform.
        ui->waveform_type->setVisible(false);
        ui->shock_button->setEnabled(false);
        // Clear cpr depth slider and label
        ui->horizontalSlider->setValue(0);
        ui->horizontalSlider->setVisible(false);
        ui->depth_value->setText("");
        step_timer->start(5000);
    }




}

void AED_Display::cpr_comp_depth()
{
    // Take current value of slider
    int current_depth = ui->horizontalSlider->value();
    ui->depth_value->setText(QString::fromStdString(std::to_string(current_depth/10) + "." + std::to_string(current_depth % 10) + " Inches"));

    // Check value with compression ratings
    if(current_depth > 0 && current_depth < 19){ // Weak force
        ui->LCDScreen->setText("PUSH HARDER \n\n");
        ui->audioMessages->append("::Push harder. Compressions are weak");
    }
    else if(current_depth > 19 && current_depth <= 24){ // Good force
        ui->LCDScreen->setText("GOOD COMPRESSIONS \n\n");
        ui->audioMessages->append("::Good compression depth. Begin 2 min CPR");
        step_timer->start(5000);
        ui->horizontalSlider->setEnabled(false);


    }
    else{ // Too much force
        ui->LCDScreen->setText("WEAKEN PUSH \n\n");
        ui->audioMessages->append("::Weaken push. Compressions are too deep");
    }
    // Display current compression ratings
    ui->LCDScreen->setAlignment(Qt::AlignCenter);
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
  AED_Audio c;
  switch (currentStep){
    case CheckResponsiveness:
    displayMessage = "CHECK RESPONSIVENESS!";
    highlightCurrentStep(ui->a_responsiveness);

    c.checkBreathing();
    ui->audioMessages->append("::Check Responsiveness.");
    break;

    //Call for help step
    case CallForHelp:
    highlightCurrentStep(ui->a_help);
    displayMessage = "CALL FOR HELP!";
    ui->audioMessages->append("::Call for help.");
    break;

    //Attach electrodes step
    case AttachElectrodes:
    highlightCurrentStep(ui->attach_pads);
    displayMessage = "ATTACH ELECTRODES TO CHEST";
    // Allow user to choose which electrodes to place
    ui->adult->setEnabled(true);
    ui->child->setEnabled(true);
    ui->attach->setEnabled(true);
    ui->audioMessages->append("::Attach defib pads to patient's bare chest.");
    step_timer->stop(); // stop timer to give user time to choose which electrodes to place
    break;

    //Stand clear analyzing patient step
    case StandClear:
    highlightCurrentStep(ui->a_standclear);
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

    // Stand clear shock
    case StandClearShock:
    displayMessage = "STAND CLEAR (Shock Warning)\nDO NOT touch patient.";
    ui->audioMessages->append("::Shock will be delivered in three, two, one");
    step_timer->stop(); // let the timer stop and then resume after the next audio message
    QTimer::singleShot(3000, [=]{
        ui->audioMessages->append("::Shock tone beeps. Shock Delivered");
        step_timer->start(5000);

    });
    break;

    // Start CPR breathing
    case CPRBreathing:
  {
    ui->horizontalSlider->setEnabled(false);
    highlightCurrentStep(ui->a_cpr_2);
    displayMessage = "BEGIN CPR";
    ui->audioMessages->append("::Start CPR.");
    step_timer->stop();
    ui->horizontalSlider->setEnabled(true);
    ui->horizontalSlider->setVisible(true);
    ui->horizontalSlider->setValue(0);
    ui->depth_value->setText("0 Inches");
    break;
    }

    //Begin the compressions
    case CheckCompressions:
    highlightCurrentStep(ui->a_cpr);
    displayMessage = "START CPR BREATHING";
    break;
  }
  ui->LCDScreen->setText(displayMessage + "\n\n");
  ui->LCDScreen->setAlignment(Qt::AlignCenter);

  if (currentStep == CheckCompressions){
    currentStep = StandClear;
    ui->horizontalSlider->setEnabled(false);
    ui->horizontalSlider->setVisible(false);
    ui->horizontalSlider->setValue(0);
    ui->depth_value->setText("");
  }else{
    currentStep = static_cast<Step>(static_cast<int>(currentStep) + 1);
  }
}

void AED_Display::display_shock()
{ // When the shock button is clicked this function is called
    ++shock_count;
    device.setChargeLevel(device.getchargeLevel()-3);
    QString shock_count_string =  QString("Shock: %1").arg(shock_count);
    ui->shockCount->setText(shock_count_string);
    ui->progressBar->setValue(device.getchargeLevel());
    step_timer->start(100); // Restart the timer again.
    ui->shock_button->setEnabled(false); // The shock button should not do anything unless another shockable rhythm is found
}

void AED_Display::d_waveform()
{
    rhythm = detect.detectHeartRhythm();
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
    ui->waveform->setVisible(true); // necessary due to detaching defib case
    ui->waveform_type->setVisible(true);
}
