#ifndef DIALOGTIMECONTROL_H
#define DIALOGTIMECONTROL_H

#include <QDialog>

namespace Ui {
class DialogTimeControl;
}

class DialogTimeControl : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTimeControl(QWidget *parent = 0);
    QString getStartTime();
    QString getEndTime();
    QString getMaxStep();
    QString getMaxdt();
    QString getPatchSize();
    ~DialogTimeControl();

private:
    Ui::DialogTimeControl *ui;
};

#endif // DIALOGTIMECONTROL_H
