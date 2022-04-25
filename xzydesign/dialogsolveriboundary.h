#ifndef DIALOGSOLVERIBOUNDARY_H
#define DIALOGSOLVERIBOUNDARY_H

#include <QDialog>

namespace Ui {
class DialogSolveriBoundary;
}

class DialogSolveriBoundary : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSolveriBoundary(QWidget *parent = 0);
    QString getType();
    QString getIndex();
    QString getCoef();
    ~DialogSolveriBoundary();

private:
    Ui::DialogSolveriBoundary *ui;
};

#endif // DIALOGSOLVERIBOUNDARY_H
