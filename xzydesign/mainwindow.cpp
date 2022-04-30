#include "mainwindow.h"
#include "ui_mainwindow.h"
//mphtxt文件转换参数输入框
#include "dialogmphtxt.h"
#include "ui_dialogmphtxt.h"
//主控参数输入框
#include "dialogmaincontrol.h"
#include "ui_dialogmaincontrol.h"
//计算类型与求解器类型选择框
#include "dialogchoosetype.h"
#include "ui_dialogchoosetype.h"
//热SolverTH边界条件输入框
#include "dialogsolverthboundary.h"
#include "ui_dialogsolverthboundary.h"
//力Solveri边界条件输入框
#include "dialogsolveriboundary.h"
#include "ui_dialogsolveriboundary.h"
//电solverE边界条件输入框
#include "dialogsolvereboundary.h"
#include "ui_dialogsolvereboundary.h"
//时间步进参数输入框
#include "dialogtimecontrol.h"
#include "ui_dialogtimecontrol.h"

#include <QFileDialog>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>
#include <QFile>
#include <QInputDialog>

//组数和计算类型在on_actionFEM_triggered()中输入
//但之后还要在写入边界条件时(on_actionBoundaryCondition_triggered())用到
//所以定义成全局变量
static int typeNumber;
static QStringList calculateTypeList;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::chooseDirectory(QString title){
    QString fileDir;
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(title);
    fileDialog->setDirectory("/home/Dev");
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setOption(QFileDialog::DontUseNativeDialog);
    fileDialog->setVisible(true);
    if (fileDialog->exec() == QDialog::Accepted) {
        fileDir = fileDialog->selectedFiles()[0];
    }
    return fileDir;
}

//点击菜单栏的基础设置->创建.input文件
void MainWindow::on_action_createInputFile_triggered()
{
    QMessageBox::information(this,"提示","请先选择存放.input文件的目录");
    QString inputDir = chooseDirectory("选择存放.input文件的目录");
    if(inputDir.isEmpty() || inputDir.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新选择");
        return;
    }
    else{
        QMessageBox::information(this,"提示","选择完毕，下面请输入文件名称");
    }
    bool ok;
    QString fullInputFileDir;
    //输入文件名
    QString fileName = QInputDialog::getText(this, "文件名输入框",
                                                "请输入.input文件名(例:xxx.input 输入xxx即可)",
                                                QLineEdit::Normal, "", &ok);
    if(ok){
        fullInputFileDir = inputDir + QString("/%1.input").arg(fileName);
        QMessageBox::information(this,"提示","已获取到文件名");
    }
    else{
        QMessageBox::information(this,"提示","输入框已删除");
        return;
    }
    QFile file(fullInputFileDir);
    //判断文件是否存在
    if(!file.exists()){
        QMessageBox::information(this,"提示",QString("%1.input文件不存在，将创建该文件").arg(fileName));
        //如果不存在，QIODevice::WriteOnly在文件不存在时将自动创建文件
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.close();
        QMessageBox::information(this,"提示",QString("已创建%1.input文件\n该文件的绝对路径为%2").arg(fileName).arg(fullInputFileDir));
    }
    else{
        QMessageBox::information(this,"提示","文件已存在");
        return;
    }
}

//点击菜单栏的模型生成->k文件
//该函数将所选择的.k文件移动到程序.input目录下
void MainWindow::on_action_k_triggered()
{
    //getOpenFileName会可能出现warning但不用理会，是gtk平台的问题
    QString fileName = QFileDialog::getOpenFileName(this,"选择.k文件",
                                                    "/home/Dev",
                                                    ".k文件(*.k)",
                                                    nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    //考虑到选文件时点击cancel的情况
    if(fileName.isEmpty() || fileName.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新选择");
        return;
    }
    else{
        QMessageBox::information(this,"提示","已成功选择.k文件\n下面请选择.k文件所要移动到的目录");
    }
    QString targetDir = chooseDirectory("选择.k文件所要移动到的目录");
    if(targetDir.isEmpty() || targetDir.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新选择");
        return;
    }
    else{
        QMessageBox::information(this,"提示","选择完毕，下面将把.k文件移动到指定目录");
    }
    copyFile(fileName, targetDir);
    QMessageBox::information(this,"提示","成功将文件移动到指定目录下");
}

//该函数将sourceFile复制一份到targetPath下
void MainWindow::copyFile(QString sourceFile, QString targetPath)
{
    sourceFile = sourceFile + " ";
    QString command = "cp " + sourceFile + targetPath;
    //qDebug()<<"command is :"<<command;
    QProcess p(0);
    p.start("bash", QStringList()<<"-c"<<command);
    p.waitForFinished();
}

//点击菜单栏的模型生成->mphtxt文件
void MainWindow::on_actionmphtxt_triggered()
{
    QMessageBox::information(this, "提示", "下面将选择mphtxt文件，a.out文件所在目录\n之后将在该目录下生成input文件，并进一步生成.k文件");
    QString mphtxtDirectory = chooseDirectory("请选择mphtxt文件，a.out文件所在目录");
    if(!mphtxtDirectory.isEmpty() && !mphtxtDirectory.isNull()){
        QMessageBox::information(this, "提示", "mphtxt目录选择完毕，下面将输入mphtxt转换参数");
    }
    else{
        QMessageBox::information(this,"提示","将回到主页面,请重新选择");
        return;
    }
    QString scale, boundaryArr1Line1, boundaryArr1Line2, inputFileName, outputFileName;
    //新建对话框
    DialogMphtxt* dialogMphtxt = new DialogMphtxt(this);
    dialogMphtxt->setVisible(true);
    int ret = dialogMphtxt->exec();
    //点击cancel按钮将退出输入框
    if(ret == QDialog::Rejected){
        delete dialogMphtxt;
        QMessageBox::information(this,"提示","输入框已删除");
        return;
    }
    //正常输入信息，点击ok
    if(ret == QDialog::Accepted)
    {
        scale = dialogMphtxt->getScale();
        boundaryArr1Line1 = dialogMphtxt->getBoundaryArr1Line1();
        boundaryArr1Line2 = dialogMphtxt->getBoundaryArr1Line2();
        inputFileName = dialogMphtxt->getInputFileName();
        outputFileName = dialogMphtxt->getOutputFileName();
    }
    delete dialogMphtxt;
    QMessageBox::information(this,"提示","成功获取输入参数,下面将把这些输入参数写入input文件");
    //将这些信息写入input文件
    QString fileName = mphtxtDirectory + "/input";
    QFile file(fileName);
    //判断文件是否存在
    if(!file.exists()){
        QMessageBox::information(this,"提示","input文件不存在，将创建该文件");
        //如果不存在，QIODevice::WriteOnly在文件不存在时将自动创建文件
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.close();
    }
    //input文件已经创建好了，下面将数据写入文件
    if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        QTextStream in(&file);
        in << "#scale\n";
        in << scale + "\n";
        in << "#in_filename\n";
        in << inputFileName + "\n";
        in << "#out_filename\n";
        in << outputFileName + "\n";
        in << "#BoundaryNum\n" << "1\n" <<
              "#Boudary_Imformation\n" <<
              "#Boundary1\n" << "8\n" << "#Boundary1_arr\n";
        in << boundaryArr1Line1 + "\n";
        in << boundaryArr1Line2 + "\n";
        file.close();
        QMessageBox::information(this,"提示","已将输入信息写入input文件,下面将mphtxt文件转换为k文件");
    }
    //input文件写好了，下面将mphtxt文件转换为k文件
    QString command = "./a.out";
    QProcess p(0);
    p.setWorkingDirectory(mphtxtDirectory);
    p.start("bash", QStringList() <<"-c" << command);
    bool result = p.waitForFinished();
    if(result){
        QMessageBox::information(this,"提示","已生成k文件,下面请选择.k文件所要移动到的目录");
    }
    QString targetDir = chooseDirectory("选择.k文件所要移动到的目录");
    if(targetDir.isEmpty() || targetDir.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新选择");
        return;
    }
    else{
        QMessageBox::information(this,"提示","选择完毕，下面将把.k文件移动到指定目录");
    }
    QString kfileName = QString("%1/%2").arg(mphtxtDirectory).arg(outputFileName);
    copyFile(kfileName, targetDir);
    QMessageBox::information(this,"提示","成功将文件移动到指定目录下");
}

//点击菜单栏的程序设置->主控参数
void MainWindow::on_actionMainControl_triggered()
{
    bool quit = chooseToQuit("设置主控参数前请先创建.input文件（在基础设置中），请问您是否已经完成？若已完成，点Yes继续操作，若无，点No退出");
    if(quit) return;
    QMessageBox::information(this,"提示","下面将输入主控参数");
    QString logFileName, outputFieldFileName;
    //新建对话框
    DialogMainControl* dialogMainControl = new DialogMainControl(this);
    dialogMainControl->setVisible(true);
    int ret = dialogMainControl->exec();
    //点击cancel按钮将退出输入框
    if(ret == QDialog::Rejected){
        delete dialogMainControl;
        QMessageBox::information(this,"提示","输入框已删除");
        return;
    }
    //点击ok是正常输入信息
    if(ret == QDialog::Accepted)
    {
        logFileName = dialogMainControl->getLogFileName();
        outputFieldFileName = dialogMainControl->getOutputFieldFileName();
    }
    QMessageBox::information(this,"提示","成功获取输入参数,下面将选择想要写入的.input文件");
    delete dialogMainControl;
    //选择.input文件
    QString fileName = QFileDialog::getOpenFileName(this,"选择.input文件",
                                                    "/home/Dev",
                                                    ".input文件(*.input)",
                                                    nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    if(fileName.isEmpty() || fileName.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新选择");
        return;
    }
    QMessageBox::information(this,"提示",".input文件已选好，下面将向该文件中写入主控参数信息");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        QTextStream in(&file);
        in << "Main{\n\t";
        in << "log_file_name = \""+ logFileName + "\"\n\t";
        in << "log_all_nodes = FALSE\n\t";
        in << "javis_dump_interval = 1\n\t";
        in << "javis_dump_dirname = \""+ outputFieldFileName + "\"\n\t";
        in << "javis_number_procs_per_file = 1\n\t"
           << "restart_dump_interval = 0\n\t"
           << "restart_dump_dirname = \"restart_elas\"\n}\n";
        file.close();
        QMessageBox::information(this,"提示","已将主控参数信息写入.input文件\n主控参数设置完成");
    }
}

//点击菜单栏的程序设置->有限元计算参数
void MainWindow::on_actionFEM_triggered()
{
    bool quit = chooseToQuit("有限元参数设置前请先创建.input文件（在基础设置中），请问您是否已经完成？若已完成，点Yes继续操作，若无，点No退出");
    if(quit) return;
    QMessageBox::information(this,"提示","下面将输入问题类型");
    bool ok;
    //输入问题类型
    QString problemType = QInputDialog::getText(this, "问题类型输入框",
                                                "请输入问题类型",
                                                QLineEdit::Normal, "", &ok);
    if(ok){
        QMessageBox::information(this,"提示","已获取到问题类型");
    }
    else{
        QMessageBox::information(this,"提示","输入框已删除");
        return;
    }
    //输入计算数量
    QMessageBox::information(this,"提示","下面将输入计算类型的数量\n例：若想计算力问题和电问题，则为2；若想计算力问题、热问题和电问题，则为3");
    typeNumber = QInputDialog::getInt(this, "计算类型的数量输入框",
                                          "请输入计算类型的数量 (输入范围[1,3])",
                                          1,1,3,1,&ok);
    if(ok){
        QMessageBox::information(this,"提示","已获取到计算数量");
    }
    else{
        QMessageBox::information(this,"提示","输入框已删除");
        return;
    }
    //选择计算类型与求解器类型
    QMessageBox::information(this,"提示","下面将输入每个问题的计算类型和求解器类型");
    QStringList solverTypeList;
    for(int i=0; i<typeNumber; i++){
        //新建对话框
        QMessageBox::information(this,"提示", QString("下面将进行第%1组输入,一共有%2组").arg(i+1).arg(typeNumber));
        DialogChooseType* dialogChooseType = new DialogChooseType(this);
        dialogChooseType->setVisible(true);
        int ret = dialogChooseType->exec();
        //点击cancel按钮将退出输入框
        if(ret == QDialog::Rejected){
            delete dialogChooseType;
            QMessageBox::information(this,"提示","输入框已删除");
            return;
        }
        //点击ok是正常输入信息
        if(ret == QDialog::Accepted)
        {
            //获取输入，并将其保存至List中，之后要写入.input文件时再从List里取
            calculateTypeList << dialogChooseType->getCalculateType();
            solverTypeList << dialogChooseType->getSolverType();
        }
        QMessageBox::information(this,"提示","成功获取输入信息");
        delete dialogChooseType;
    }
    QMessageBox::information(this,"提示","已获取到所有问题的计算类型和求解器类型,下面将选择想要写入的.input文件");
    //选择.input文件
    QString fileName = QFileDialog::getOpenFileName(this,"选择.input文件",
                                                    "/home/Dev",
                                                    ".input文件(*.input)",
                                                    nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    if(fileName.isEmpty() || fileName.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新选择");
        return;
    }
    QMessageBox::information(this,"提示",".input文件已选好，下面将向该文件中写入计算类型和求解器类型信息");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        QTextStream in(&file);
        //下面写入FEM一些基本参数
        in << "FEM{\n\t";
        in << "problem_type = \""+ problemType + "\"\n\t";
        in << "element_type = \"LinearTetrahedron\"\n\t"
           << "element_marks = 0\n\t"
           << "integrator_type = \"LinearTetrahedron\"\n\t"
           << "integrator_marks = 0\n\t"
           << "material_type = \"LinearTetrahedron\"\n\t"
           << "material_marks = 0\n\t"
           << "shape_func_type = \"LinearTetrahedron\"\n\t"
           << "shape_func_marks = 0\n}\n";
        //下面写入solver参数
        in << "Solver{\n";
        for(int i=0; i<typeNumber; i++){
            //如果选择的是热SolverTH
            if(calculateTypeList[i].compare("热")==0){
                in << "\tSolverTH{\n";
                write_SolverInfo_intoFile(in, solverTypeList[i]);
            }
            //如果选择的是力Solveri__
            else if(calculateTypeList[i].compare("力")==0){
                in << "\tSolveri__{\n";
                write_SolverInfo_intoFile(in, solverTypeList[i]);
            }
            //如果选择的是电SolverE
            else if(calculateTypeList[i].compare("电")==0){
                in << "\tSolverE{\n";
                write_SolverInfo_intoFile(in, solverTypeList[i]);
            }
            else{
                QMessageBox::information(this,"提示","判断计算类型时出错了");
            }
        }
        in << "}\n";
        file.close();
        QMessageBox::information(this,"提示","已将所有计算类型和求解器类型信息写入.input文件\n有限元参数设置完成");
    }
}

//将求解器HYPRE_PCG信息写入.input文件
void MainWindow::write_HYPRE_PCG_intoFile(QTextStream& in){
    in << "\t\tsolver_name = \"HYPRE_PCG\"\n\t\t"
       << "solver_tol = 1.0e-40\n\t\t"
       << "solver_max_iter = 30000\n\t\t"
       << "solver_min_iter = 1\n\t\t"
       << "print_iter_info = 1"
       <<  "\n\t}\n";
}

//将求解器JAUMIN_CG信息写入.input文件
void MainWindow::write_JAUMIN_CG_intoFile(QTextStream& in){
    in << "\t\tsolver_name = \"JAUMIN_CG\"\n\t\t"
       << "solver_tol = 1.0e-8\n\t\t"
       << "solver_max_iter = 10000\n\t\t"
       << "solver_min_iter = 1\n\t\t"
       << "print_level = 1"
       <<  "\n\t}\n";
}

//将求解器PETSc_Solver信息写入.input文件
void MainWindow::write_PETSc_Solver_intoFile(QTextStream& in){
    in << "\t\tsolver_name = \"PETSc_Solver\"\n\t\t"
       << "expert_options = \"-ksp_converged_reason -ksp_type preonly -pc_type lu - pc_factor_mat_solver_package  mumps\""
       << "\n\t}\n";
}

//根据所输入的求解器类型，将相应的求解器信息写入.input文件
void MainWindow::write_SolverInfo_intoFile(QTextStream& in, QString solverType){
    if(solverType.compare("HYPRE_PCG")==0){
        write_HYPRE_PCG_intoFile(in);
        QMessageBox::information(this,"提示","已将求解器HYPRE_PCG信息写入.input文件");
    }
    else if(solverType.compare("JAUMIN_CG")==0){
        write_JAUMIN_CG_intoFile(in);
        QMessageBox::information(this,"提示","已将求解器JAUMIN_CG信息写入.input文件");
    }
    else if(solverType.compare("PETSc_Solver")==0){
        write_PETSc_Solver_intoFile(in);
        QMessageBox::information(this,"提示","已将求解器PETSc_Solver信息写入.input文件");

    }
    else{
        QMessageBox::information(this,"提示","判断求解器类型时出错了");
        return;
    }
}

//点击菜单栏的程序设置->边界条件设置
//该函数将弹出输入边界数量，边界条件的输入框，并将用户输入的信息写入.input文件
void MainWindow::on_actionBoundaryCondition_triggered()
{
    bool quit = chooseToQuit("设置边界条件前请先进行有限元参数设置，请问您是否已经设置？若已设置，点Yes继续操作，若无，点No退出");
    if(quit) return;
    int boundaryNumber[3]; //用于保存每个类型对应的边界数量
    //将输入的n组(type,index,coef)值分别保存在typeList，indexList，coefList中,之后要写入.input文件时再从List里取
    QStringList typeList_TH, indexList_TH, coefList_TH;
    QStringList typeList_I, indexList_I, coefList_I;
    QStringList typeList_E, indexList_E, coefList_E;
    QMessageBox::information(this,"提示","下面将开始输入边界条件");
    for(int i=0; i<typeNumber; i++){
        //对于每个类型，都先输入边界条件数量，再弹出对应数量的输入框
        if(calculateTypeList[i].compare("热")==0){
            //输入边界数量
            boundaryNumber[i] = getBoundaryNumber("热");
            //获取边界条件保存在typeListTH，indexListTH，coefListTH中
            if(boundaryNumber[i]<0){
                QMessageBox::information(this,"提示","将回到主页面,请重新输入");
                return;
            }
            get_SolverTH_Boundarycondition(boundaryNumber[i], typeList_TH, indexList_TH, coefList_TH);
            QMessageBox::information(this,"提示","热问题边界条件输入完毕，辛苦了");
        }
        else if(calculateTypeList[i].compare("力")==0){
            //输入边界数量
            boundaryNumber[i] = getBoundaryNumber("力");
            //获取边界条件保存在typeListI，indexListI，coefListI中
            if(boundaryNumber[i]<0){
                QMessageBox::information(this,"提示","将回到主页面,请重新输入");
                return;
            }
            get_SolverI_Boundarycondition(boundaryNumber[i], typeList_I, indexList_I, coefList_I);
            QMessageBox::information(this,"提示","力问题边界条件输入完毕，辛苦了");
        }
        else if(calculateTypeList[i].compare("电")==0){
            //输入边界数量
            boundaryNumber[i] = getBoundaryNumber("电");
            //获取边界条件保存在typeListE，indexListE，coefListE中
            if(boundaryNumber[i]<0){
                QMessageBox::information(this,"提示","将回到主页面,请重新输入");
                return;
            }
            get_SolverE_Boundarycondition(boundaryNumber[i], typeList_E, indexList_E, coefList_E);
            QMessageBox::information(this,"提示","电问题边界条件输入完毕，辛苦了");
        }
        else{
            QMessageBox::information(this,"提示","判断计算类型时出错了");
            return;
        }

    }
    QMessageBox::information(this,"提示","已成功获取所有边界条件，下面将选择想要写入的.input文件");
    //选择.input文件
    QString fileName = QFileDialog::getOpenFileName(this,"选择.input文件",
                                                    "/home/Dev",
                                                    ".input文件(*.input)",
                                                    nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    if(fileName.isEmpty() || fileName.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新选择");
        return;
    }
    QMessageBox::information(this,"提示",".input文件已选好，下面将向该文件中写入边界条件信息");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        QTextStream in(&file);
        for(int i=0; i<typeNumber; i++){
            if(calculateTypeList[i].compare("热")==0){
                QMessageBox::information(this,"提示","下面将开始写入热问题边界条件");
                in << "Ther_Boundary{\n\t";
                write_BoundaryCondition_intoFile(in, boundaryNumber[i], typeList_TH, indexList_TH, coefList_TH);
                QMessageBox::information(this,"提示","已将热问题边界条件写入.input文件");
            }
            else if(calculateTypeList[i].compare("力")==0){
                QMessageBox::information(this,"提示","下面将开始写入力问题边界条件");
                in << "Mech_Boundary{\n\t";
                write_BoundaryCondition_intoFile(in, boundaryNumber[i], typeList_I, indexList_I, coefList_I);
                QMessageBox::information(this,"提示","已将力问题边界条件写入.input文件");
            }
            else if(calculateTypeList[i].compare("电")==0){
                QMessageBox::information(this,"提示","下面将开始写入电问题边界条件");
                in << "Elec_Boundary{\n\t";
                write_BoundaryCondition_intoFile(in, boundaryNumber[i], typeList_E, indexList_E, coefList_E);
                QMessageBox::information(this,"提示","已将电问题边界条件写入.input文件");
            }
            else{
                QMessageBox::information(this,"提示","判断计算类型时出错了");
            }
        }
        //边界信息写完后还要加一个},与最开始的FEM{对应
        in << "}\n";
    }
    file.close();
    QMessageBox::information(this,"提示","已将所有边界条件写入.input文件\n边界条件设置完成");
}

int MainWindow::getBoundaryNumber(QString calculateType){
    QMessageBox::information(this,"提示",QString("下面将输入%1问题的边界数量").arg(calculateType));
    bool ok; //用于QInputDialog判断点击了yes还是no
    int boundaryNumber = QInputDialog::getInt(this, QString("%1问题边界数量输入框").arg(calculateType),
                                                QString("请输入%1问题边界数量 (输入范围[0,100])").arg(calculateType),
                                             0,0,100,1,&ok);
    if(ok){
        QMessageBox::information(this,"提示", QString("%1问题的边界数量是%2").arg(calculateType).arg(boundaryNumber));
        return boundaryNumber;
    }
    else{
        QMessageBox::information(this,"提示","输入框已删除,将退出边界条件设置");
        return -1;
    }
}

//将边界条件写入.input文件
void MainWindow::write_BoundaryCondition_intoFile(QTextStream& in, int boundaryNumber, QStringList& typeList, QStringList& indexList, QStringList& coefList){
    in << QString("Num_Boundary = %1\n").arg(boundaryNumber);
    for(int i=0; i<boundaryNumber; i++){
        in << QString("\tBoundary_%1{\n").arg(i+1);
        in << QString("\t\ttype = \"%1\"").arg(typeList[i]);
        in << "\n\t\tindex = " + indexList[i];
        in << "\n\t\tcoef = " + coefList[i];
        in << "\n\t}\n";
    }
    in << "}\n";
}

//计算类型是热SolverTH，获取边界条件
void MainWindow::get_SolverTH_Boundarycondition(int boundaryNumber, QStringList& typeList, QStringList& indexList, QStringList& coefList){
    //弹出boundaryNumber个SolverTH边界条件的输入框
    for(int i=0; i<boundaryNumber; i++){
        QString type, index, coef;
        QMessageBox::information(this,"提示", QString("下面将进行第%1组输入,一共有%2组").arg(i+1).arg(boundaryNumber));
        DialogSolverTHBoundary* dialogSolverTHBoundary = new DialogSolverTHBoundary(this);
        dialogSolverTHBoundary->setVisible(true);
        int ret = dialogSolverTHBoundary->exec();
        //点击cancel按钮将退出输入框
        if(ret == QDialog::Rejected){
            delete dialogSolverTHBoundary;
            QMessageBox::information(this,"提示","输入框已删除");
            return;
        }
        //点击ok是正常输入信息
        if(ret == QDialog::Accepted){
            //获取type，index，coef这三个输入信息
            typeList << dialogSolverTHBoundary->getType();
            indexList << dialogSolverTHBoundary->getIndex();
            coefList << dialogSolverTHBoundary->getCoef();
        }
        QMessageBox::information(this,"提示","成功获取输入信息");
        delete dialogSolverTHBoundary;
    }
}

//计算类型是力SolverI，获取边界条件
void MainWindow::get_SolverI_Boundarycondition(int boundaryNumber, QStringList& typeList, QStringList& indexList, QStringList& coefList){
    //弹出boundaryNumber个SolverI边界条件的输入框
    for(int i=0; i<boundaryNumber; i++){
        QString type, index, coef;
        QMessageBox::information(this,"提示", QString("下面将进行第%1组输入,一共有%2组").arg(i+1).arg(boundaryNumber));
        DialogSolveriBoundary* dialogSolveriBoundary = new DialogSolveriBoundary(this);
        dialogSolveriBoundary->setVisible(true);
        int ret = dialogSolveriBoundary->exec();
        //点击cancel按钮将退出输入框
        if(ret == QDialog::Rejected){
            delete dialogSolveriBoundary;
            QMessageBox::information(this,"提示","输入框已删除");
            return;
        }
        //点击ok是正常输入信息
        if(ret == QDialog::Accepted){
            //获取type，index，coef这三个输入信息,存入对应的List
            typeList << dialogSolveriBoundary->getType();
            indexList << dialogSolveriBoundary->getIndex();
            coefList << dialogSolveriBoundary->getCoef();
        }
        QMessageBox::information(this,"提示","成功获取输入信息");
        delete dialogSolveriBoundary;
    }
}

//计算类型是力SolverE，获取边界条件
void MainWindow::get_SolverE_Boundarycondition(int boundaryNumber, QStringList& typeList, QStringList& indexList, QStringList& coefList){
    //弹出boundaryNumber个SolverE边界条件的输入框
    for(int i=0; i<boundaryNumber; i++){
        QString type, index, coef;
        QMessageBox::information(this,"提示", QString("下面将进行第%1组输入,一共有%2组").arg(i+1).arg(boundaryNumber));
        DialogSolverEBoundary* dialogSolverEBoundary = new DialogSolverEBoundary(this);
        dialogSolverEBoundary->setVisible(true);
        int ret = dialogSolverEBoundary->exec();
        //点击cancel按钮将退出输入框
        if(ret == QDialog::Rejected){
            delete dialogSolverEBoundary;
            QMessageBox::information(this,"提示","输入框已删除");
            return;
        }
        //点击ok是正常输入信息
        if(ret == QDialog::Accepted){
            //获取type，index，coef这三个输入信息,存入对应的List
            typeList << dialogSolverEBoundary->getType();
            indexList << dialogSolverEBoundary->getIndex();
            coefList << dialogSolverEBoundary->getCoef();
        }
        QMessageBox::information(this,"提示","成功获取输入信息");
        delete dialogSolverEBoundary;
    }
}

//点击菜单栏的程序设置->几何结构参数
void MainWindow::on_actionGridGeometry_triggered()
{
    bool quit = chooseToQuit("几何结构参数设置前请先创建.input文件（在基础设置中），请问您是否已经完成？若已完成，点Yes继续操作，若无，点No退出");
    if(quit) return;
    //选择.k文件
    QMessageBox::information(this,"提示","请选择Mesh信息所需的.k文件");
    QString kfileName = QFileDialog::getOpenFileName(this,"选择.k文件",
                                                    "/home/Dev",
                                                    ".k文件(*.k)",
                                                    nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    if(kfileName.isEmpty() || kfileName.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新选择");
        return;
    }
    QMessageBox::information(this,"提示",".k文件已选好，下面将输入加密次数");
    //输入加密次数
    bool ok;
    QString refineTimes = QInputDialog::getText(this, "加密次数输入框",
                                                "请输入加密次数",
                                                QLineEdit::Normal, "", &ok);
    if(ok){
        QMessageBox::information(this,"提示","已获取到加密次数");
    }
    else{
        QMessageBox::information(this,"提示","输入框已删除");
        return;
    }
    //将上面两个信息写入.input文件
    QMessageBox::information(this,"提示","下面请选择想要写入的.input文件");
    //选择.input文件
    QString fileName = QFileDialog::getOpenFileName(this,"选择.input文件",
                                                    "/home/Dev",
                                                    ".input文件(*.input)",
                                                    nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    if(fileName.isEmpty() || fileName.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新选择");
        return;
    }
    QMessageBox::information(this,"提示",".input文件已选好，下面将向该文件中写入几何结构参数信息");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        QTextStream in(&file);
        in << "GridGeometry{\n"
           << "\tMeshImportationParameter{\n";
        in << QString("\t\tfile_name = \"%1\"\n").arg(kfileName);
        in << QString("\t\trefine_times = %1\n").arg(refineTimes);
        in << "\t}\n}\n";
    }
    file.close();
    QMessageBox::information(this,"提示","已将几何结构参数信息写入.input文件\n几何结构参数设置完成");
}

//点击菜单栏的程序设置->时间步进参数
void MainWindow::on_actionTimeControl_triggered()
{
    bool quit = chooseToQuit("时间步进参数设置前请先创建.input文件（在基础设置中），请问您是否已经完成？若已完成，点Yes继续操作，若无，点No退出");
    if(quit) return;
    QMessageBox::information(this,"提示","下面请输入时间步进参数");
    QString startTime, endTime, maxStep, maxdt, patchSize;
    //新建对话框
    DialogTimeControl* dialogTimeControl = new DialogTimeControl(this);
    dialogTimeControl->setVisible(true);
    int ret = dialogTimeControl->exec();
    //点击cancel按钮将退出输入框
    if(ret == QDialog::Rejected){
        delete dialogTimeControl;
        QMessageBox::information(this,"提示","输入框已删除");
        return;
    }
    //正常输入信息，点击ok
    if(ret == QDialog::Accepted)
    {
        startTime = dialogTimeControl->getStartTime();
        endTime = dialogTimeControl->getEndTime();
        maxStep = dialogTimeControl->getMaxStep();
        maxdt = dialogTimeControl->getMaxdt();
        patchSize = dialogTimeControl->getPatchSize();
    }
    delete dialogTimeControl;
    QMessageBox::information(this,"提示","成功获取输入时间步进参数,下面将选择想要写入的.input文件");
    QString fileName = QFileDialog::getOpenFileName(this,"选择.input文件",
                                                    "/home/Dev",
                                                    ".input文件(*.input)",
                                                    nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    if(fileName.isEmpty() || fileName.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新输入并选择");
        return;
    }
    QMessageBox::information(this,"提示",".input文件已选好，下面将向该文件中写入时间步进参数信息");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        QTextStream in(&file);
        //下面输入HierarchyTimeIntegrator信息
        in << "HierarchyTimeIntegrator{\n"
           << QString("\tstart_time = %1\n").arg(startTime)
           << QString("\tend_time = %1\n").arg(endTime)
           << QString("\tmax_integrator_steps = %1\n").arg(maxStep)
           << QString("\tmax_dt = %1\n").arg(maxdt)
           << "\tgrow_dt = 1.0\n"
           << "\tGriddingAlgorithm{\n"
           << QString("\t\tpatch_size = %1\n").arg(patchSize)
           << "\t}\n}\n";
        //下面输入TimerManager信息
        in << "TimerManager{\n"
           << "\ttimer_list = \"*::*::*\"\n"
           << "\tprint_summed = TRUE\n"
           << "\tprint_max = TRUE\n"
           << "\tprint_threshold = 0\n"
           << "}\n";
        file.close();
        QMessageBox::information(this,"提示","已将时间步进参数信息写入.input文件\n时间步进参数设置完成");
    }

}

//点击菜单栏的程序运行->运行
void MainWindow::on_actionRunProgram_triggered()
{

    QMessageBox::information(this,"提示","请选择想要执行的程序");
    QString programName = QFileDialog::getOpenFileName(this,"选择程序",
                                                    "/home/Dev",
                                                    "",
                                                    nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    if(programName.isEmpty() || programName.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新输入并选择");
        return;
    }
    //选择.input文件
    QMessageBox::information(this,"提示","请选择程序所需的.input文件");
    QString inputFileName = QFileDialog::getOpenFileName(this,"选择.input文件",
                                                    "/home/Dev",
                                                    ".input文件(*.input)",
                                                    nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    if(inputFileName.isEmpty() || inputFileName.isNull()){
        QMessageBox::information(this,"提示","将回到主页面,请重新选择");
        return;
    }

    QString command = QString("%1 %2").arg(programName).arg(inputFileName);
    QProcess* m_process = new QProcess();
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_process , &QProcess::readyReadStandardOutput , this , [=]()
                                                                    {
                                                                        MainWindow::displayOutput(m_process);
                                                                    });
    m_process->start("bash", QStringList()<<"-c"<<command);
    if (!m_process->waitForStarted()) {
        qDebug() << "start failed:" << m_process->errorString();
    } else {
        qDebug() << "start success:";
    }
}

void MainWindow::displayOutput(QProcess* m_process){
    //qDebug() << m_process->readAllStandardOutput().data();
    ui->displayConsoleOutput->setPlainText(QString::fromUtf8(m_process->readAllStandardOutput().data()));
}

//该函数会弹出一个选择yes或no的提示框，如果选no了返回true，表示要退出
bool MainWindow::chooseToQuit(QString questionText){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "提示", questionText,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No){
        return true;
    }
    else{
        return false;
    }
}





void MainWindow::on_actionDrawSimulationGraph_triggered()
{
    QString command = "/opt/teravap2.6.0/bin/teravap";
    QProcess* m_process = new QProcess();
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_process , &QProcess::readyReadStandardOutput , this , [=]()
                                                                    {
                                                                        MainWindow::displayOutput(m_process);
                                                                    });
    m_process->start("bash", QStringList()<<"-c"<<command);
    if (!m_process->waitForStarted()) {
        qDebug() << "start failed:" << m_process->errorString();
    } else {
        qDebug() << "start success:";
    }
}
