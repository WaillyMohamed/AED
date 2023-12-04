#include "AED_Audio.h"

AED_Audio::AED_Audio(QObject *parent)
    : QObject{parent}
{
}

void AED_Audio::playShockPrompts() {
    qDebug() << "[AED Audio]: Stand Clear";
    QThread::msleep(2000);
    qDebug() << "[AED Audio]: Analyzing...";
    QThread::msleep(2000);
    qDebug() << "[AED Audio]: Shock Advised";

}

void AED_Audio::playNormalAudio() {
    qDebug() << "[AED Audio]: Heart Rate is Normal";
}

void AED_Audio::responsiveAudio() {
    qDebug() << "[AED Audio]: Check Responsivness";
}

void AED_Audio::helpCall() {
    qDebug() << "[AED Audio]: Call for help";
}

void AED_Audio::openAirway() {
    qDebug() << "[AED Audio]: Open Airway";
}

void AED_Audio::checkBreathing() {
    qDebug() << "[AED Audio]: Check Breathing";
}

void AED_Audio::attachElectrode() {
    qDebug() << "[AED Audio]: Attach Electrode Pads to patient's bare chest";
}
