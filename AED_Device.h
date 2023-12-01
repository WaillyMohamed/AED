#ifndef AED_DEVICE_H
#define AED_DEVICE_H

#include <string>

enum DeviceMode{
    ACTIVE,
    STANDBY
};

class AED_Device
{
public:
    AED_Device();
    int chargeLevel;
    std::string batteryStatus;
};

#endif // AED_DEVICE_H
