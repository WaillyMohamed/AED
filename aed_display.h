#ifndef AED_DISPLAY_H
#define AED_DISPLAY_H

#include "AED_Device.h"

#include <QMainWindow>
#include <QLabel>
#include <QElapsedTimer>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class AED_Display; }
QT_END_NAMESPACE

class AED_Display : public QMainWindow
{
    Q_OBJECT

public:
    AED_Display(QWidget *parent = nullptr);
    ~AED_Display();

private:
    Ui::AED_Display *ui;
    void setLabelImage(QLabel *label, const QString &path, int width, int height);
    AED_Device device;
 //   QElapsedTimer stopwatch;
   // QTimer *update_t;

private slots:
    void powerOn();
//    void timerUp();

};



#endif // AED_DISPLAY_H
