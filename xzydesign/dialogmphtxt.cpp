#include "dialogmphtxt.h"
#include "ui_dialogmphtxt.h"
#include <QMessageBox>
#include <QString>

DialogMphtxt::DialogMphtxt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMphtxt)
{
    ui->setupUi(this);
}

QString DialogMphtxt::getScale()
{
    if(!ui->inputScale->text().isEmpty())
    {
          return ui->inputScale->text();
    }
    QString defaultValue = "1";
    return defaultValue;
}

QString DialogMphtxt::getBoundaryArr1Line1()
{
    if(!ui->inputBoundaryArr1Line1->text().isEmpty())
    {
          return ui->inputBoundaryArr1Line1->text();
    }
    QString defaultValue = "0 0 0 0";
    return defaultValue;
}

QString DialogMphtxt::getBoundaryArr1Line2()
{
    if(!ui->inputBoundaryArr1Line2->text().isEmpty())
    {
          return ui->inputBoundaryArr1Line2->text();
    }
    QString defaultValue = "0 0 0 0";
    return defaultValue;
}

QString DialogMphtxt::getInputFileName()
{
    if(!ui->inputInputFileName->text().isEmpty())
    {
          return ui->inputInputFileName->text();
    }
    QString defaultValue = "warning";
    return defaultValue;
}

QString DialogMphtxt::getOutputFileName()
{
    if(!ui->inputOutputFileName->text().isEmpty())
    {
          return ui->inputOutputFileName->text();
    }
    QString defaultValue = "warning";
    return defaultValue;
}
/*
Ui::DialogMphtxt *DialogMphtxt::retUiPointer()
{
    return ui;
}
*/

DialogMphtxt::~DialogMphtxt()
{
    delete ui;
}
