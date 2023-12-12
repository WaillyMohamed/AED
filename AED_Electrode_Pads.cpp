#include "AED_Electrode_Pads.h"
#include <QDebug>



AED_Electrode_Pads::AED_Electrode_Pads()
{
    status = false;
    child_or_adult = 0;
}


bool AED_Electrode_Pads::checkAlignment() {
    qDebug() << "Electrode Pads properly aligned.";
    return true;
}

bool AED_Electrode_Pads::isPlacementValid(bool newStatus) {
    status = newStatus;
    return status;
}

QString AED_Electrode_Pads::getPlacement() const {
    return placement;
}

bool AED_Electrode_Pads::getStatus() const {
    return status;
}

int AED_Electrode_Pads::getChild_or_adult() const
{
    return child_or_adult;
}

void AED_Electrode_Pads::setChild_or_adult(int newChild_or_adult)
{
    child_or_adult = newChild_or_adult;
}

void AED_Electrode_Pads::setStatus(bool newStatus)
{
    status = newStatus;
}
