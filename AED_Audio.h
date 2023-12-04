#ifndef AED_AUDIO_H
#define AED_AUDIO_H

#include <QObject>
#include <QDebug>
#include <QThread>

class AED_Audio : public QObject
{
    Q_OBJECT
public:
    explicit AED_Audio(QObject *parent = nullptr);
    
    void playShockPrompts(); //called when shock is to be administered
    void playNormalAudio(); //function is called when heart rate is normal
    void responsiveAudio(); //emulates "check responsiveness audio"
    void helpCall(); //call for help stage in process
    void openAirway(); //open airway stage in process
    void checkBreathing(); //check patient's breathing
    void attachElectrode(); //attach electrode pads

private:
    QString message;
};

#endif // AED_AUDIO_H

