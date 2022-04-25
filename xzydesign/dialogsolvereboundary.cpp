#include "dialogsolvereboundary.h"
#include "ui_dialogsolvereboundary.h"

DialogSolverEBoundary::DialogSolverEBoundary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSolverEBoundary)
{
    ui->setupUi(this);
}

QString DialogSolverEBoundary::getType()
{
    int index = ui->comboBox->currentIndex();
    if(index == 0)
    {
          return "voltage";
    }
    else if(index == 1){
        return "current";
    }
    QString defaultValue = "fluxed";
    return defaultValue;
}

QString DialogSolverEBoundary::getIndex()
{
    if(!ui->inputIndex->text().isEmpty())
    {
          return ui->inputIndex->text();
    }
    QString defaultValue = "0";
    return defaultValue;
}

QString DialogSolverEBoundary::getCoef()
{
    if(!ui->inputCoef->text().isEmpty())
    {
          return ui->inputCoef->text();
    }
    QString defaultValue = "0";
    return defaultValue;
}

DialogSolverEBoundary::~DialogSolverEBoundary()
{
    delete ui;
}
