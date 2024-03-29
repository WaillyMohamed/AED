#include "AED_Device.h"


AED_Device::AED_Device()
{
   // To model the charge/power being low, change this value to 5
    charge_level = 100;
    mode = STANDBY;
    seconds = 0;
}

int AED_Device::getchargeLevel()
{
    return charge_level;
}
/*
This function initiates a self test to ensure the device is functioning properly and ready for use. Provide visual and audible indication that is it operational

This function should be called when the device is powered on and when the device is switched from standby to active mode


*/
std::string AED_Device::powerOn()
{
    std::string message = "";
    if (selfTest())
    {
        setDeviceMode(ACTIVE);
        std::cout << "Device is operational and ready for use.\n";
        std::cout << "[Display: Green LED On]\n";
        std::cout << "[AUDIO: Beep Sound]\n";
        message = "Device is operational and ready for use\nAudio: Beep Sound\n";
    }
    else
    {
        setDeviceMode(STANDBY);
         std::cout << "Device is not operational. Please check the device.\n";
         std::cout << "[Visual -> Display Class] RED LED ON\n";
         std::cout << "[Audio -> Audio Class] Device not operational sound\n";
         message = "Device is not operational. Please check the device.";
    }
    return message;
}

std::string AED_Device::powerOff()
{
    std::string message = "Device turning off...\n";
    seconds = 0;
    mode = STANDBY;
    return message;

}


void AED_Device::setDeviceMode(DeviceMode newMode)
{
    mode = newMode;

}

void AED_Device::setChargeLevel(int cl){
  charge_level = cl;

}

int AED_Device::getSeconds() const
{
    return seconds;
}

void AED_Device::update()
{
    seconds++;
}

std::string AED_Device::displayTime()
{
    std::string time = "";
    int mm = seconds / 60;
    int ss = seconds % 60;
    if(mm < 10){ // if the number is in double digits
        time = "0";
    }
    time += std::to_string(mm) + ":";
    if (ss < 10){
        time += "0";
    }
    time += std::to_string(ss);
    return time;
}

std::string AED_Device::getMode() const
{
    std::string m = "";
    switch(mode){
        case ACTIVE:
            m = "ACTIVE";
            break;
        case STANDBY:
            m = "STANDBY";
            break;
    }
    return m;
}

bool AED_Device::selfTest()
{
    if (charge_level < 5)
    {
        return false;
    }
    else
    {
        return true;
    }
}



std::string AED_Device::safetyFeature()
{
    srand(time(NULL));
    int x = rand() % 1;
    if(x == 0){
        return "Plug in cable";
    }
    else{
        return "Change batteries";
    }
}
