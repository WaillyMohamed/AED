#ifndef AED_ELECTRODE_PADS_H
#define AED_ELECTRODE_PADS_H

#include <QString>

class AED_Electrode_Pads
{
public:
    AED_Electrode_Pads(const QString& initialPlacement);

    bool checkAlignment();
    bool isPlacementValid(bool status);

    //getters
    QString getPlacement() const;
    bool getStatus() const;

private:
    QString placement; //emulates the physical placement of the pad on patient
    bool status; // is it properly placed?
};

#endif // AED_ELECTRODE_PADS_H
