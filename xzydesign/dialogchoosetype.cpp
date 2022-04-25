#include "dialogchoosetype.h"
#include "ui_dialogchoosetype.h"

DialogChooseType::DialogChooseType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChooseType)
{
    ui->setupUi(this);
}

QString DialogChooseType::getCalculateType()
{
    int index = ui->comboBoxCalculateType->currentIndex();
    if(index == 0)
    {
        return "热";
    }
    else if(index == 1){
        return "力";
    }
    else if(index == 2){
        return "电";
    }
    QString defaultValue = "热";
    return defaultValue;
}

QString DialogChooseType::getSolverType()
{
    int index = ui->comboBoxSolverType->currentIndex();
    if(index == 0)
    {
        return "HYPRE_PCG";
    }
    else if(index == 1){
        return "JAUMIN_CG";
    }
    else if(index == 2){
        return "PETSc_Solver";
    }
    QString defaultValue = "HYPRE_PCG";
    return defaultValue;
}

DialogChooseType::~DialogChooseType()
{
    delete ui;
}
