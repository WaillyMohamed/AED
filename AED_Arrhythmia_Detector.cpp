#include "AED_Arrhythmia_Detector.h"

AED_Arrhythmia_Detector::AED_Arrhythmia_Detector()
{
    shockable = false;
}



bool AED_Arrhythmia_Detector::detectHeartRhythm()
{
    bool padsAligned = true; // assume the pads are aligned
    if (!padsAligned) {
        std::cout << "Pads are not aligned. Please align pads.\n";
        return false;
    }

    int shockableRhythm = rand() % 2;

    if (shockableRhythm == 1) {
        int rhythmType = rand() % 2;
        if (rhythmType == 0) {
            currentHeartRhythm = VENTRICULAR_FIBRILLATION;
        } else {
            currentHeartRhythm = VENTRICULAR_TACHYCARDIA;
        }
        shockable = true;
    } else {
        currentHeartRhythm = NORMAL;
        shockable = false;
    }

    return true;
}   


/*Determines if the rhythm is shockable*/
bool AED_Arrhythmia_Detector::isShockable()
{
    return shockable;
}

/*Set shock status*/
void AED_Arrhythmia_Detector::setShockStatus(bool shockStatus)
{
    shockable = shockStatus;
}
