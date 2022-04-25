#ifndef DIALOGSOLVERTHBOUNDARY_H
#define DIALOGSOLVERTHBOUNDARY_H

#include <QDialog>

namespace Ui {
class DialogSolverTHBoundary;
}

class DialogSolverTHBoundary : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSolverTHBoundary(QWidget *parent = 0);
    QString getType();
    QString getIndex();
    QString getCoef();
    ~DialogSolverTHBoundary();

private:
    Ui::DialogSolverTHBoundary *ui;
};

#endif // DIALOGSOLVERTHBOUNDARY_H
