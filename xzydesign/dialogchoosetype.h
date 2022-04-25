#ifndef DIALOGCHOOSETYPE_H
#define DIALOGCHOOSETYPE_H

#include <QDialog>

namespace Ui {
class DialogChooseType;
}

class DialogChooseType : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChooseType(QWidget *parent = 0);
    QString getCalculateType();
    QString getSolverType();
    ~DialogChooseType();

private:
    Ui::DialogChooseType *ui;
};

#endif // DIALOGCHOOSETYPE_H
