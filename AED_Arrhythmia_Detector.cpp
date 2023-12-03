#include "AED_Arrhythmia_Detector.h"

AED_Arrhythmia_Detector::AED_Arrhythmia_Detector()
{
    shockable = false;
}





/*Determines if the rhythm is shockable*/
bool AED_Arrhythmia_Detector::isShockable()
{
    return shockable;
}

/*Set shock status*/
bool AED_Arrhythmia_Detector::setShockStatus(bool shockStatus)
{
    shockable = shockStatus;
}