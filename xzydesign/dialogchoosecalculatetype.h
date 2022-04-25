#ifndef DIALOGCHOOSECALCULATETYPE_H
#define DIALOGCHOOSECALCULATETYPE_H

#include <QDialog>

namespace Ui {
class DialogChooseCalculateType;
}

class DialogChooseCalculateType : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChooseCalculateType(QWidget *parent = 0);
    bool chooseSolver_TH();
    bool chooseSolver_I();
    bool chooseSolver_E();
    ~DialogChooseCalculateType();

private:
    Ui::DialogChooseCalculateType *ui;
};

#endif // DIALOGCHOOSECALCULATETYPE_H
