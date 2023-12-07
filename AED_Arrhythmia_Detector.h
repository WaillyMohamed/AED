#ifndef AED_ARRHYTHMIA_DETECTOR_H
#define AED_ARRHYTHMIA_DETECTOR_H

#include <string>
#include <iostream>

enum Heart_Rhythm
{
    ASYSTOLE,
    SINUS_RHYTHM_OR_PEA,
    VENTRICULAR_FIBRILLATION,
    VENTRICULAR_TACHYCARDIA
};


class AED_Arrhythmia_Detector
{
public:
    AED_Arrhythmia_Detector();

    int detectHeartRhythm();

    /*Determines if the rhythm is shockable*/
    bool isShockable();

    /*Set shock status*/
    void setShockStatus(bool shockStatus);

private:
    //AED_Electrode_Pads placement;
    bool shockable;

    //
    Heart_Rhythm currentHeartRhythm;


};

#endif // AED_ARRHYTHMIA_DETECTOR_H
