#include "dialogmaincontrol.h"
#include "ui_dialogmaincontrol.h"
#include <QMessageBox>
#include <QString>

DialogMainControl::DialogMainControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMainControl)
{
    ui->setupUi(this);
}

QString DialogMainControl::getLogFileName()
{
    if(!ui->inputLogFileName->text().isEmpty())
    {
          return ui->inputLogFileName->text();
    }
    QString defaultValue = "warning";
    return defaultValue;
}

QString DialogMainControl::getOutputFieldFileName()
{
    if(!ui->inputOutputFieldFileName->text().isEmpty())
    {
          return ui->inputOutputFieldFileName->text();
    }
    QString defaultValue = "warning";
    return defaultValue;
}

DialogMainControl::~DialogMainControl()
{
    //QMessageBox::information(this,"提示","主控参数输入完毕");
    delete ui;
}
