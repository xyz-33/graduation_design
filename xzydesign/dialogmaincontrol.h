#ifndef DIALOGMAINCONTROL_H
#define DIALOGMAINCONTROL_H

#include <QDialog>

namespace Ui {
class DialogMainControl;
}

class DialogMainControl : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMainControl(QWidget *parent = 0);
    QString getLogFileName();
    QString getOutputFieldFileName();
    ~DialogMainControl();

private:
    Ui::DialogMainControl *ui;
};

#endif // DIALOGMAINCONTROL_H
