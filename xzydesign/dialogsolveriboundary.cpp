#include "dialogsolveriboundary.h"
#include "ui_dialogsolveriboundary.h"

DialogSolveriBoundary::DialogSolveriBoundary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSolveriBoundary)
{
    ui->setupUi(this);
}

QString DialogSolveriBoundary::getType()
{
    int index = ui->comboBox->currentIndex();
    if(index == 0)
    {
          return "fixed";
    }
    QString defaultValue = "fixed";
    return defaultValue;
}

QString DialogSolveriBoundary::getIndex()
{
    if(!ui->inputIndex->text().isEmpty())
    {
          return ui->inputIndex->text();
    }
    QString defaultValue = "0";
    return defaultValue;
}

QString DialogSolveriBoundary::getCoef()
{
    if(!ui->inputCoef->text().isEmpty())
    {
          return ui->inputCoef->text();
    }
    QString defaultValue = "0";
    return defaultValue;
}
DialogSolveriBoundary::~DialogSolveriBoundary()
{
    delete ui;
}
