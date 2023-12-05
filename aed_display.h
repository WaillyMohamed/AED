#ifndef AED_DISPLAY_H
#define AED_DISPLAY_H

#include <QMainWindow>

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

private slots:
    void powerOn();

};



#endif // AED_DISPLAY_H
