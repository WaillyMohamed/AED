#include "AED_Device.h"


AED_Device::AED_Device()
{
    charge_level = 100;
    mode = STANDBY;
}

int AED_Device::getchargeLevel()
{
    return charge_level;
}

void AED_Device::shock()
{

}

/*
This function initiates a self test to ensure the device is functioning properly and ready for use. Provide visual and audible indication that is it operational

This function should be called when the device is powered on and when the device is switched from standby to active mode


*/
void AED_Device::powerOn()
{
    if (selfTest())
    {
        setDeviceMode(ACTIVE);
        std::cout << "Device is operational and ready for use.\n";
        std::cout << "[Visual -> Display Class: Green LED On]\n";
        std::cout << "[Audible -> Audio: Beep Sound]\n";
    }
    else
    {
        setDeviceMode(STANDBY);
         std::cout << "Device is not operational. Please check the device.\n";
         std::cout << "[Visual -> Display Class] RED LED ON\n";
         std::cout << "[Audio -> Audio Class] Device not operational sound\n";
    }
}


void AED_Device::setDeviceMode(DeviceMode newMode)
{
    mode = newMode;

}

bool AED_Device::selfTest()
{
    if (charge_level < 50)
    {
        return false;
    }
    else
    {
        return true;
    }
}
