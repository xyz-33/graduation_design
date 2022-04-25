#include "dialogtimecontrol.h"
#include "ui_dialogtimecontrol.h"

DialogTimeControl::DialogTimeControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTimeControl)
{
    ui->setupUi(this);
}

QString DialogTimeControl::getStartTime()
{
    if(!ui->inputStartTime->text().isEmpty())
    {
          return ui->inputStartTime->text();
    }
    QString defaultValue = "0";
    return defaultValue;
}

QString DialogTimeControl::getEndTime()
{
    if(!ui->inputEndTime->text().isEmpty())
    {
          return ui->inputEndTime->text();
    }
    QString defaultValue = "0";
    return defaultValue;
}

QString DialogTimeControl::getMaxStep()
{
    if(!ui->inputMaxStep->text().isEmpty())
    {
          return ui->inputMaxStep->text();
    }
    QString defaultValue = "10";
    return defaultValue;
}

QString DialogTimeControl::getMaxdt()
{
    if(!ui->inputMaxdt->text().isEmpty())
    {
          return ui->inputMaxdt->text();
    }
    QString defaultValue = "10";
    return defaultValue;
}

QString DialogTimeControl::getPatchSize()
{
    if(!ui->inputPatchSize->text().isEmpty())
    {
          return ui->inputPatchSize->text();
    }
    QString defaultValue = "10";
    return defaultValue;
}


DialogTimeControl::~DialogTimeControl()
{
    delete ui;
}
