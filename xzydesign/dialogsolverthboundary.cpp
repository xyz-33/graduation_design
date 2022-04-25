#include "dialogsolverthboundary.h"
#include "ui_dialogsolverthboundary.h"

DialogSolverTHBoundary::DialogSolverTHBoundary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSolverTHBoundary)
{
    ui->setupUi(this);
}

QString DialogSolverTHBoundary::getType()
{
    int index = ui->comboBox->currentIndex();
    if(index == 0)
    {
          return "fluxed";
    }
    else if(index == 1){
        return "fixed";
    }
    QString defaultValue = "fluxed";
    return defaultValue;
}

QString DialogSolverTHBoundary::getIndex()
{
    if(!ui->inputIndex->text().isEmpty())
    {
          return ui->inputIndex->text();
    }
    QString defaultValue = "0";
    return defaultValue;
}

QString DialogSolverTHBoundary::getCoef()
{
    if(!ui->inputCoef->text().isEmpty())
    {
          return ui->inputCoef->text();
    }
    QString defaultValue = "0";
    return defaultValue;
}

DialogSolverTHBoundary::~DialogSolverTHBoundary()
{
    delete ui;
}
