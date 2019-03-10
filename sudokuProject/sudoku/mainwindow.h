#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExp>
#include <QRegExpValidator>
#include<fstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static int num[9][9];
    static int sudoku[10][10],flag[10][10];
    static int num_of_solution;
private slots:
    void on_A11_textChanged();
    void on_A12_textChanged();
    void on_A13_textChanged();
    void on_A21_textChanged();
    void on_A22_textChanged();
    void on_A23_textChanged();
    void on_A31_textChanged();
    void on_A32_textChanged();
    void on_A33_textChanged();
    void on_B11_textChanged();
    void on_B12_textChanged();
    void on_B13_textChanged();
    void on_B21_textChanged();
    void on_B22_textChanged();
    void on_B23_textChanged();
    void on_B31_textChanged();
    void on_B32_textChanged();
    void on_B33_textChanged();
    void on_C11_textChanged();
    void on_C12_textChanged();
    void on_C13_textChanged();
    void on_C21_textChanged();
    void on_C22_textChanged();
    void on_C23_textChanged();
    void on_C31_textChanged();
    void on_C32_textChanged();
    void on_C33_textChanged();
    void on_D11_textChanged();
    void on_D12_textChanged();
    void on_D13_textChanged();
    void on_D21_textChanged();
    void on_D22_textChanged();
    void on_D23_textChanged();
    void on_D31_textChanged();
    void on_D32_textChanged();
    void on_D33_textChanged();
    void on_E11_textChanged();
    void on_E12_textChanged();
    void on_E13_textChanged();
    void on_E21_textChanged();
    void on_E22_textChanged();
    void on_E23_textChanged();
    void on_E31_textChanged();
    void on_E32_textChanged();
    void on_E33_textChanged();
    void on_F11_textChanged();
    void on_F12_textChanged();
    void on_F13_textChanged();
    void on_F21_textChanged();
    void on_F22_textChanged();
    void on_F23_textChanged();
    void on_F31_textChanged();
    void on_F32_textChanged();
    void on_F33_textChanged();
    void on_G11_textChanged();
    void on_G12_textChanged();
    void on_G13_textChanged();
    void on_G21_textChanged();
    void on_G22_textChanged();
    void on_G23_textChanged();
    void on_G31_textChanged();
    void on_G32_textChanged();
    void on_G33_textChanged();
    void on_I11_textChanged();
    void on_I12_textChanged();
    void on_I13_textChanged();
    void on_I21_textChanged();
    void on_I22_textChanged();
    void on_I23_textChanged();
    void on_I31_textChanged();
    void on_I32_textChanged();
    void on_I33_textChanged();
    void on_H11_textChanged();
    void on_H12_textChanged();
    void on_H13_textChanged();
    void on_H21_textChanged();
    void on_H22_textChanged();
    void on_H23_textChanged();
    void on_H31_textChanged();
    void on_H32_textChanged();
    void on_H33_textChanged();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void globalInitial();
    void upgradeHavingGeneratedSudoku();
    void set_readonly(bool a);
    void newGameInitial();

    void upgradeWhenFailed();
    void on_BtnSolve_clicked();

    void on_BtnSubmit_clicked();
    int check(int row,int col);
    void solve(int row,int col);

    void checkUnique(int row,int col);
    void checkUniqueInitial();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
