#ifndef DIALOGMPHTXT_H
#define DIALOGMPHTXT_H

#include <QDialog>

namespace Ui {
class DialogMphtxt;
}

class DialogMphtxt : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMphtxt(QWidget *parent = 0);
    QString getScale();
    QString getBoundaryArr1Line1();
    QString getBoundaryArr1Line2();
    QString getInputFileName();
    QString getOutputFileName();
    //Ui::DialogMphtxt* retUiPointer();
    ~DialogMphtxt();

private:
    Ui::DialogMphtxt *ui;
};

#endif // DIALOGMPHTXT_H
