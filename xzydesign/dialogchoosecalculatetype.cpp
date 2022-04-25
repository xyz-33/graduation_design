#include "dialogchoosecalculatetype.h"
#include "ui_dialogchoosecalculatetype.h"

DialogChooseCalculateType::DialogChooseCalculateType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChooseCalculateType)
{
    ui->setupUi(this);
}

bool DialogChooseCalculateType::chooseSolver_TH(){
    return ui->checkBox_TH->isChecked();
}

bool DialogChooseCalculateType::chooseSolver_I(){
    return ui->checkBox_I->isChecked();
}

bool DialogChooseCalculateType::chooseSolver_E(){
    return ui->checkBox_E->isChecked();
}

DialogChooseCalculateType::~DialogChooseCalculateType()
{
    delete ui;
}
