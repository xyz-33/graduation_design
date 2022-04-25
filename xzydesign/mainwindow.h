#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString chooseDirectory(QString title);
    void copyFile(QString sourcePath, QString targetPath);
    void write_HYPRE_PCG_intoFile(QTextStream& in);
    void write_JAUMIN_CG_intoFile(QTextStream& in);
    void write_PETSc_Solver_intoFile(QTextStream& in);
    void write_SolverInfo_intoFile(QTextStream& in, QString solverType);
    int getBoundaryNumber(QString calculateType);
    void get_SolverTH_Boundarycondition(int boundaryNumber, QStringList& typeList, QStringList& indexList, QStringList& coefList);
    void get_SolverI_Boundarycondition(int boundaryNumber, QStringList& typeList, QStringList& indexList, QStringList& coefList);
    void get_SolverE_Boundarycondition(int boundaryNumber, QStringList& typeList, QStringList& indexList, QStringList& coefList);
    void write_BoundaryCondition_intoFile(QTextStream& in, int boundaryNumber, QStringList& typeList, QStringList& indexList, QStringList& coefList);
    bool chooseToQuit(QString questionText);
    ~MainWindow();

private slots:
    void on_action_k_triggered();

    void on_actionmphtxt_triggered();

    void on_actionMainControl_triggered();

    void on_actionFEM_triggered();

    void on_actionBoundaryCondition_triggered();

    void on_actionGridGeometry_triggered();

    void on_action_createInputFile_triggered();

    void on_actionTimeControl_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
