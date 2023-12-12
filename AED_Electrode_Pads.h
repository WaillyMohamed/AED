#ifndef AED_ELECTRODE_PADS_H
#define AED_ELECTRODE_PADS_H

#include <QString>

class AED_Electrode_Pads
{
public:

    AED_Electrode_Pads();

    bool checkAlignment();
    bool isPlacementValid(bool status);

    //getters
    QString getPlacement() const;
    bool getStatus() const;

    int getChild_or_adult() const;
    void setChild_or_adult(int newChild_or_adult);

    void setStatus(bool newStatus);

private:
    QString placement; //emulates the physical placement of the pad on patient
    bool status; // is it properly placed?
    int child_or_adult; // 1 represents child pads and 2 represents adult pads. 0 is default
};

#endif // AED_ELECTRODE_PADS_H
