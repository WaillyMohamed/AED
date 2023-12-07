#ifndef AED_DISPLAY_H
#define AED_DISPLAY_H

#include "AED_Device.h"
#include "AED_Arrhythmia_Detector.h"

#include <QMainWindow>
#include <QLabel>
#include <QElapsedTimer>
#include <QTimer>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class AED_Display; }
QT_END_NAMESPACE

class AED_Display : public QMainWindow
{
    Q_OBJECT

public:
    AED_Display(QWidget *parent = nullptr);
    ~AED_Display();

private:
    Ui::AED_Display *ui;
    void setLabelImage(QLabel *label, const QString &path, int width, int height);
    void d_waveform(); // This method analyzes and displays the waveform. It also performs a shock on the patient if the rhythm is shockable.

    AED_Device device;
    AED_Arrhythmia_Detector detect;
    int rhythm; // 0 VF, 1 VT, 2 ASYSTOLE, 3 SINUS
    int shock_count; // shock count wthat would be incremented

    //This represents the respective AED "steps"
    enum Step{
      CheckResponsiveness,
      CallForHelp,
      AttachElectrodes,
      StandClear,
      StandClearShock,
      CPRBreathing,
      CheckCompressions,
    };

    Step currentStep; //keep track of the current step
    QTimer *step_timer;
    QElapsedTimer displaytimer;


private slots:
    void powerOn();
    void nextAEDStep();
    void display_shock();
    void timerUp();

};



#endif // AED_DISPLAY_H
