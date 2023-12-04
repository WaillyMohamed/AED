#ifndef AED_AUDIO_H
#define AED_AUDIO_H

#include <QObject>

class AED_Audio : public QObject
{
    Q_OBJECT
public:
    explicit AED_Audio(QObject *parent = nullptr);

signals:

};

#endif // AED_AUDIO_H
