#include "AED_Arrhythmia_Detector.h"
#include <ctime>

AED_Arrhythmia_Detector::AED_Arrhythmia_Detector()
{
    shockable = false;
}



int AED_Arrhythmia_Detector::detectHeartRhythm()
{
    bool padsAligned = true; // assume the pads are aligned
    if (!padsAligned) {
        std::cout << "Pads are not aligned. Please align pads.\n";
        return false;
    }

    srand(time(NULL));
    int shockableRhythm = rand() % 2;

    if (shockableRhythm == 1) {
        shockable = true;
        int rhythmType = rand() % 2;
        if (rhythmType == 0) {
            currentHeartRhythm = VENTRICULAR_FIBRILLATION;
            return 0; // returns 0
        } else {
            currentHeartRhythm = VENTRICULAR_TACHYCARDIA;
            return 1; // returns 1
        }
    } else {
        shockable = false;
        int rhythmType = rand() % 2;
        if (rhythmType == 0) {
            currentHeartRhythm = ASYSTOLE;
            return 2; // returns 0
        } else {
            currentHeartRhythm = SINUS_RHYTHM_OR_PEA;
            return 3; // returns 1
        }

    }
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
