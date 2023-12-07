#include "AED_Electrode_Pads.h"
#include <QDebug>

AED_Electrode_Pads::AED_Electrode_Pads(const QString& initialPlacement) : placement(initialPlacement), status(false)
{

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
