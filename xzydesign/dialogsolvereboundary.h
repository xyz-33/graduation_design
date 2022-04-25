#ifndef DIALOGSOLVEREBOUNDARY_H
#define DIALOGSOLVEREBOUNDARY_H

#include <QDialog>

namespace Ui {
class DialogSolverEBoundary;
}

class DialogSolverEBoundary : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSolverEBoundary(QWidget *parent = 0);
    QString getType();
    QString getIndex();
    QString getCoef();
    ~DialogSolverEBoundary();

private:
    Ui::DialogSolverEBoundary *ui;
};

#endif // DIALOGSOLVEREBOUNDARY_H
