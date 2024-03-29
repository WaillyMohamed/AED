#ifndef AED_DEVICE_H
#define AED_DEVICE_H

#include <string>
#include <iostream>
#include <ctime>
#include <QDebug>
#include <cmath>


enum DeviceMode{
    ACTIVE, //fully operational and ready to respond to emergency
    STANDBY // low-power or inactive state
};

class AED_Device
{
public:
    AED_Device();
    /*Get the charge level of the device*/
    int getchargeLevel();

    /*Get the battery status*/
    std::string getStatus();

    /*Shock when rhythm detected is either vf or vt*/
    void shock();

    /*Perform self test and power on*/
    std::string powerOn();
    std::string powerOff();

    /*Set the device mode for the AED*/
    void setDeviceMode(DeviceMode mode);

    /*Perform a self test*/
    bool selfTest();

    /*Set charge level*/
    void setChargeLevel(int cl);


    std::string safetyFeature(); // generates an issue


    int getSeconds() const;
    void update();
    std::string displayTime(); // Method will takes seconds and return a string that formats the time in hours and minutes


    std::string getMode() const;

private:
    int charge_level;
    DeviceMode mode;
    int seconds;
};

#endif // AED_DEVICE_H
