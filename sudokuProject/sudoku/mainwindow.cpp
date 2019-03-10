/*
 * Created on 2018-12-18
 * Author::Chen Haoyu & Zhao Yifan
 * Version:1.2
 * Title:Sudoku
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<fstream>                       //文件输出
using namespace std;
int MainWindow:: num[9][9];             //用于出题
int MainWindow::sudoku[10][10],MainWindow::flag[10][10];//用于解题
int MainWindow::num_of_solution;
static bool done=0;
static ofstream outfile;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    globalInitial();
}
MainWindow::~MainWindow()
{
    delete ui;
}
//**************************************************************************************************************
void MainWindow::globalInitial()    //全局初始化，包括重置num数组，所有单元格只接受数字输入，并添加只读属性
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            num[i][j]=0;
    ui->A11->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->A12->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->A13->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->A21->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->A22->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->A23->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->A31->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->A32->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->A33->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->B11->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->B12->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->B13->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->B21->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->B22->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->B23->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->B31->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->B32->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->B33->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->C11->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->C12->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->C13->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->C21->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->C22->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->C23->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->C31->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->C32->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->C33->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->D11->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->D12->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->D13->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->D21->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->D22->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->D23->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->D31->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->D32->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->D33->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->E11->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->E12->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->E13->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->E21->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->E22->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->E23->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->E31->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->E32->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->E33->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->F11->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->F12->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->F13->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->F21->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->F22->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->F23->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->F31->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->F32->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->F33->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->G11->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->G12->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->G13->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->G21->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->G22->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->G23->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->G31->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->G32->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->G33->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->H11->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->H12->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->H13->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->H21->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->H22->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->H23->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->H31->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->H32->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->H33->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->I11->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->I12->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->I13->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->I21->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->I22->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->I23->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->I31->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->I32->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->I33->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    set_readonly(true);
}
void MainWindow::newGameInitial()               //点击“做数独”按钮时执行，包括移除只读属性并清除所有单元格，设置字体颜色为黑色，重置num数组
{
   set_readonly(false);
   for(int i=0;i<9;i++)
       for(int j=0;j<9;j++)
           num[i][j]=0;
   ui->A11->clear();ui->A11->setStyleSheet("color:black");
   ui->A12->clear();ui->A12->setStyleSheet("color:black");
   ui->A13->clear();ui->A13->setStyleSheet("color:black");
   ui->A21->clear();ui->A21->setStyleSheet("color:black");
   ui->A22->clear();ui->A22->setStyleSheet("color:black");
   ui->A23->clear();ui->A23->setStyleSheet("color:black");
   ui->A31->clear();ui->A31->setStyleSheet("color:black");
   ui->A32->clear();ui->A32->setStyleSheet("color:black");
   ui->A33->clear();ui->A33->setStyleSheet("color:black");
   ui->B11->clear();ui->B11->setStyleSheet("color:black");
   ui->B12->clear();ui->B12->setStyleSheet("color:black");
   ui->B13->clear();ui->B13->setStyleSheet("color:black");
   ui->B21->clear();ui->B21->setStyleSheet("color:black");
   ui->B22->clear();ui->B22->setStyleSheet("color:black");
   ui->B23->clear();ui->B23->setStyleSheet("color:black");
   ui->B31->clear();ui->B31->setStyleSheet("color:black");
   ui->B32->clear();ui->B32->setStyleSheet("color:black");
   ui->B33->clear();ui->B33->setStyleSheet("color:black");
   ui->C11->clear();ui->C11->setStyleSheet("color:black");
   ui->C12->clear();ui->C12->setStyleSheet("color:black");
   ui->C13->clear();ui->C13->setStyleSheet("color:black");
   ui->C21->clear();ui->C21->setStyleSheet("color:black");
   ui->C22->clear();ui->C22->setStyleSheet("color:black");
   ui->C23->clear();ui->C23->setStyleSheet("color:black");
   ui->C31->clear();ui->C31->setStyleSheet("color:black");
   ui->C32->clear();ui->C32->setStyleSheet("color:black");
   ui->C33->clear();ui->C33->setStyleSheet("color:black");
   ui->D11->clear();ui->D11->setStyleSheet("color:black");
   ui->D12->clear();ui->D12->setStyleSheet("color:black");
   ui->D13->clear();ui->D13->setStyleSheet("color:black");
   ui->D21->clear();ui->D21->setStyleSheet("color:black");
   ui->D22->clear();ui->D22->setStyleSheet("color:black");
   ui->D23->clear();ui->D23->setStyleSheet("color:black");
   ui->D31->clear();ui->D31->setStyleSheet("color:black");
   ui->D32->clear();ui->D32->setStyleSheet("color:black");
   ui->D33->clear();ui->D33->setStyleSheet("color:black");
   ui->E11->clear();ui->E11->setStyleSheet("color:black");
   ui->E12->clear();ui->E12->setStyleSheet("color:black");
   ui->E13->clear();ui->E13->setStyleSheet("color:black");
   ui->E21->clear();ui->E21->setStyleSheet("color:black");
   ui->E22->clear();ui->E22->setStyleSheet("color:black");
   ui->E23->clear();ui->E23->setStyleSheet("color:black");
   ui->E31->clear();ui->E31->setStyleSheet("color:black");
   ui->E32->clear();ui->E32->setStyleSheet("color:black");
   ui->E33->clear();ui->E33->setStyleSheet("color:black");
   ui->F11->clear();ui->F11->setStyleSheet("color:black");
   ui->F12->clear();ui->F12->setStyleSheet("color:black");
   ui->F13->clear();ui->F13->setStyleSheet("color:black");
   ui->F21->clear();ui->F21->setStyleSheet("color:black");
   ui->F22->clear();ui->F22->setStyleSheet("color:black");
   ui->F23->clear();ui->F23->setStyleSheet("color:black");
   ui->F31->clear();ui->F31->setStyleSheet("color:black");
   ui->F32->clear();ui->F32->setStyleSheet("color:black");
   ui->F33->clear();ui->F33->setStyleSheet("color:black");
   ui->G11->clear();ui->G11->setStyleSheet("color:black");
   ui->G12->clear();ui->G12->setStyleSheet("color:black");
   ui->G13->clear();ui->G13->setStyleSheet("color:black");
   ui->G21->clear();ui->G21->setStyleSheet("color:black");
   ui->G22->clear();ui->G22->setStyleSheet("color:black");
   ui->G23->clear();ui->G23->setStyleSheet("color:black");
   ui->G31->clear();ui->G31->setStyleSheet("color:black");
   ui->G32->clear();ui->G32->setStyleSheet("color:black");
   ui->G33->clear();ui->G33->setStyleSheet("color:black");
   ui->H11->clear();ui->H11->setStyleSheet("color:black");
   ui->H12->clear();ui->H12->setStyleSheet("color:black");
   ui->H13->clear();ui->H13->setStyleSheet("color:black");
   ui->H21->clear();ui->H21->setStyleSheet("color:black");
   ui->H22->clear();ui->H22->setStyleSheet("color:black");
   ui->H23->clear();ui->H23->setStyleSheet("color:black");
   ui->H31->clear();ui->H31->setStyleSheet("color:black");
   ui->H32->clear();ui->H32->setStyleSheet("color:black");
   ui->H33->clear();ui->H33->setStyleSheet("color:black");
   ui->I11->clear();ui->I11->setStyleSheet("color:black");
   ui->I12->clear();ui->I12->setStyleSheet("color:black");
   ui->I13->clear();ui->I13->setStyleSheet("color:black");
   ui->I21->clear();ui->I21->setStyleSheet("color:black");
   ui->I22->clear();ui->I22->setStyleSheet("color:black");
   ui->I23->clear();ui->I23->setStyleSheet("color:black");
   ui->I31->clear();ui->I31->setStyleSheet("color:black");
   ui->I32->clear();ui->I32->setStyleSheet("color:black");
   ui->I33->clear();ui->I33->setStyleSheet("color:black");
}
void MainWindow::checkUniqueInitial()   //由陈浩宇提供）处理flag和sudoku数组，以便检查解的唯一性
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            flag[i][j]=1;
        }
    }
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            sudoku[i][j] = num[i][j]-10;     //num中值的范围是{0}∪[11,19]
            if(sudoku[i][j]==-10)
            {
                flag[i][j]=0;
                sudoku[i][j]=0;
            }
        }
    }
}
void MainWindow::checkUnique(int row,int col) //（由陈浩宇提供）回溯法 检查解的唯一性
{
    while(flag[row][col])//已经填数
    {
        col++;
        if((10==col))
        {
            row++;
            col=0;
        }
        if(row==9)
        {
            num_of_solution++;
            goto end;
        }
    }

    for(int i=1;i<10;i++)
    {
        sudoku[row][col]=i;
        if(check(row,col))
            checkUnique(row,col+1);
    }
    end:sudoku[row][col]=0;
}
bool judgeWhenSubmitted(int num[][9])    //点击“提交”时，执行该函数进行判断，可以用蓝色标记出错误的地方
{                                        //因为num可能为[10,19]中的值或负值，该函数中所有num中的数都写作abs(num[i][j])%10
    bool isRight=true;                   //非法的输入被变成负数，在输出函数中，负值作为蓝色输出
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(num[i][j]>10) continue;
            else if(num[i][j]==0) isRight=false;
            else
            {
                for(int m=0;m<9;m++)//行
                {
                    if(m==i) continue;
                    else if(abs(num[m][j])%10==abs(num[i][j])%10) {num[i][j]=-abs(num[i][j]);isRight=false;}
                }
                for(int n=0;n<9;n++)//列
                {
                    if(n==j) continue;
                    else if(abs(num[i][n])%10==abs(num[i][j])%10) {num[i][j]=-abs(num[i][j]);isRight=false;}
                }
                //宫
                int x=3*(i/3); int y=3*(j/3);
                for(int m=x;m<=x+2;m++)
                {
                    for(int n=y;n<=y+2;n++)
                    {
                        if(m==i&&n==j) continue;
                        else if(abs(num[m][n])%10==abs(num[i][j])%10) {num[i][j]=-abs(num[i][j]);isRight=false;}
                    }
                }
            }
        }
    }
    return isRight;
}
void MainWindow::upgradeHavingGeneratedSudoku()//该函数负责将num数组中的值输送到屏幕。本程序用num∈[11,19]来表示出题是给定的数，用红色显示
{
    QString tempStr;
    if(num[0][0]!=0)   {    ui->A11->setText(tempStr.setNum(num[0][0]-10));num[0][0]+=10;ui->A11->setReadOnly(true);ui->A11->setStyleSheet("color:red");}
    if(num[0][1]!=0)   {    ui->A12->setText(tempStr.setNum(num[0][1]-10));num[0][1]+=10;ui->A12->setReadOnly(true);ui->A12->setStyleSheet("color:red");}
    if(num[0][2]!=0)   {    ui->A13->setText(tempStr.setNum(num[0][2]-10));num[0][2]+=10;ui->A13->setReadOnly(true);ui->A13->setStyleSheet("color:red");}
    if(num[1][0]!=0)   {    ui->A21->setText(tempStr.setNum(num[1][0]-10));num[1][0]+=10;ui->A21->setReadOnly(true);ui->A21->setStyleSheet("color:red");}
    if(num[1][1]!=0)   {    ui->A22->setText(tempStr.setNum(num[1][1]-10));num[1][1]+=10;ui->A22->setReadOnly(true);ui->A22->setStyleSheet("color:red");}
    if(num[1][2]!=0)   {    ui->A23->setText(tempStr.setNum(num[1][2]-10));num[1][2]+=10;ui->A23->setReadOnly(true);ui->A23->setStyleSheet("color:red");}
    if(num[2][0]!=0)   {    ui->A31->setText(tempStr.setNum(num[2][0]-10));num[2][0]+=10;ui->A31->setReadOnly(true);ui->A31->setStyleSheet("color:red");}
    if(num[2][1]!=0)   {    ui->A32->setText(tempStr.setNum(num[2][1]-10));num[2][1]+=10;ui->A32->setReadOnly(true);ui->A32->setStyleSheet("color:red");}
    if(num[2][2]!=0)   {    ui->A33->setText(tempStr.setNum(num[2][2]-10));num[2][2]+=10;ui->A33->setReadOnly(true);ui->A33->setStyleSheet("color:red");}
    if(num[0][3]!=0)   {    ui->B11->setText(tempStr.setNum(num[0][3]-10));num[0][3]+=10;ui->B11->setReadOnly(true);ui->B11->setStyleSheet("color:red");}
    if(num[0][4]!=0)   {    ui->B12->setText(tempStr.setNum(num[0][4]-10));num[0][4]+=10;ui->B12->setReadOnly(true);ui->B12->setStyleSheet("color:red");}
    if(num[0][5]!=0)   {    ui->B13->setText(tempStr.setNum(num[0][5]-10));num[0][5]+=10;ui->B13->setReadOnly(true);ui->B13->setStyleSheet("color:red");}
    if(num[1][3]!=0)   {    ui->B21->setText(tempStr.setNum(num[1][3]-10));num[1][3]+=10;ui->B21->setReadOnly(true);ui->B21->setStyleSheet("color:red");}
    if(num[1][4]!=0)   {    ui->B22->setText(tempStr.setNum(num[1][4]-10));num[1][4]+=10;ui->B22->setReadOnly(true);ui->B22->setStyleSheet("color:red");}
    if(num[1][5]!=0)   {    ui->B23->setText(tempStr.setNum(num[1][5]-10));num[1][5]+=10;ui->B23->setReadOnly(true);ui->B23->setStyleSheet("color:red");}
    if(num[2][3]!=0)   {    ui->B31->setText(tempStr.setNum(num[2][3]-10));num[2][3]+=10;ui->B31->setReadOnly(true);ui->B31->setStyleSheet("color:red");}
    if(num[2][4]!=0)   {    ui->B32->setText(tempStr.setNum(num[2][4]-10));num[2][4]+=10;ui->B32->setReadOnly(true);ui->B32->setStyleSheet("color:red");}
    if(num[2][5]!=0)   {    ui->B33->setText(tempStr.setNum(num[2][5]-10));num[2][5]+=10;ui->B33->setReadOnly(true);ui->B33->setStyleSheet("color:red");}
    if(num[0][6]!=0)   {    ui->C11->setText(tempStr.setNum(num[0][6]-10));num[0][6]+=10;ui->C11->setReadOnly(true);ui->C11->setStyleSheet("color:red");}
    if(num[0][7]!=0)   {    ui->C12->setText(tempStr.setNum(num[0][7]-10));num[0][7]+=10;ui->C12->setReadOnly(true);ui->C12->setStyleSheet("color:red");}
    if(num[0][8]!=0)   {    ui->C13->setText(tempStr.setNum(num[0][8]-10));num[0][8]+=10;ui->C13->setReadOnly(true);ui->C13->setStyleSheet("color:red");}
    if(num[1][6]!=0)   {    ui->C21->setText(tempStr.setNum(num[1][6]-10));num[1][6]+=10;ui->C21->setReadOnly(true);ui->C21->setStyleSheet("color:red");}
    if(num[1][7]!=0)   {    ui->C22->setText(tempStr.setNum(num[1][7]-10));num[1][7]+=10;ui->C22->setReadOnly(true);ui->C22->setStyleSheet("color:red");}
    if(num[1][8]!=0)   {    ui->C23->setText(tempStr.setNum(num[1][8]-10));num[1][8]+=10;ui->C23->setReadOnly(true);ui->C23->setStyleSheet("color:red");}
    if(num[2][6]!=0)   {    ui->C31->setText(tempStr.setNum(num[2][6]-10));num[2][6]+=10;ui->C31->setReadOnly(true);ui->C31->setStyleSheet("color:red");}
    if(num[2][7]!=0)   {    ui->C32->setText(tempStr.setNum(num[2][7]-10));num[2][7]+=10;ui->C32->setReadOnly(true);ui->C32->setStyleSheet("color:red");}
    if(num[2][8]!=0)   {    ui->C33->setText(tempStr.setNum(num[2][8]-10));num[2][8]+=10;ui->C33->setReadOnly(true);ui->C33->setStyleSheet("color:red");}
    if(num[3][0]!=0)   {    ui->D11->setText(tempStr.setNum(num[3][0]-10));num[3][0]+=10;ui->D11->setReadOnly(true);ui->D11->setStyleSheet("color:red");}
    if(num[3][1]!=0)   {    ui->D12->setText(tempStr.setNum(num[3][1]-10));num[3][1]+=10;ui->D12->setReadOnly(true);ui->D12->setStyleSheet("color:red");}
    if(num[3][2]!=0)   {    ui->D13->setText(tempStr.setNum(num[3][2]-10));num[3][2]+=10;ui->D13->setReadOnly(true);ui->D13->setStyleSheet("color:red");}
    if(num[4][0]!=0)   {    ui->D21->setText(tempStr.setNum(num[4][0]-10));num[4][0]+=10;ui->D21->setReadOnly(true);ui->D21->setStyleSheet("color:red");}
    if(num[4][1]!=0)   {    ui->D22->setText(tempStr.setNum(num[4][1]-10));num[4][1]+=10;ui->D22->setReadOnly(true);ui->D22->setStyleSheet("color:red");}
    if(num[4][2]!=0)   {    ui->D23->setText(tempStr.setNum(num[4][2]-10));num[4][2]+=10;ui->D23->setReadOnly(true);ui->D23->setStyleSheet("color:red");}
    if(num[5][0]!=0)   {    ui->D31->setText(tempStr.setNum(num[5][0]-10));num[5][0]+=10;ui->D31->setReadOnly(true);ui->D31->setStyleSheet("color:red");}
    if(num[5][1]!=0)   {    ui->D32->setText(tempStr.setNum(num[5][1]-10));num[5][1]+=10;ui->D32->setReadOnly(true);ui->D32->setStyleSheet("color:red");}
    if(num[5][2]!=0)   {    ui->D33->setText(tempStr.setNum(num[5][2]-10));num[5][2]+=10;ui->D33->setReadOnly(true);ui->D33->setStyleSheet("color:red");}
    if(num[3][3]!=0)   {    ui->E11->setText(tempStr.setNum(num[3][3]-10));num[3][3]+=10;ui->E11->setReadOnly(true);ui->E11->setStyleSheet("color:red");}
    if(num[3][4]!=0)   {    ui->E12->setText(tempStr.setNum(num[3][4]-10));num[3][4]+=10;ui->E12->setReadOnly(true);ui->E12->setStyleSheet("color:red");}
    if(num[3][5]!=0)   {    ui->E13->setText(tempStr.setNum(num[3][5]-10));num[3][5]+=10;ui->E13->setReadOnly(true);ui->E13->setStyleSheet("color:red");}
    if(num[4][3]!=0)   {    ui->E21->setText(tempStr.setNum(num[4][3]-10));num[4][3]+=10;ui->E21->setReadOnly(true);ui->E21->setStyleSheet("color:red");}
    if(num[4][4]!=0)   {    ui->E22->setText(tempStr.setNum(num[4][4]-10));num[4][4]+=10;ui->E22->setReadOnly(true);ui->E22->setStyleSheet("color:red");}
    if(num[4][5]!=0)   {    ui->E23->setText(tempStr.setNum(num[4][5]-10));num[4][5]+=10;ui->E23->setReadOnly(true);ui->E23->setStyleSheet("color:red");}
    if(num[5][3]!=0)   {    ui->E31->setText(tempStr.setNum(num[5][3]-10));num[5][3]+=10;ui->E31->setReadOnly(true);ui->E31->setStyleSheet("color:red");}
    if(num[5][4]!=0)   {    ui->E32->setText(tempStr.setNum(num[5][4]-10));num[5][4]+=10;ui->E32->setReadOnly(true);ui->E32->setStyleSheet("color:red");}
    if(num[5][5]!=0)   {    ui->E33->setText(tempStr.setNum(num[5][5]-10));num[5][5]+=10;ui->E33->setReadOnly(true);ui->E33->setStyleSheet("color:red");}
    if(num[3][6]!=0)   {    ui->F11->setText(tempStr.setNum(num[3][6]-10));num[3][6]+=10;ui->F11->setReadOnly(true);ui->F11->setStyleSheet("color:red");}
    if(num[3][7]!=0)   {    ui->F12->setText(tempStr.setNum(num[3][7]-10));num[3][7]+=10;ui->F12->setReadOnly(true);ui->F12->setStyleSheet("color:red");}
    if(num[3][8]!=0)   {    ui->F13->setText(tempStr.setNum(num[3][8]-10));num[3][8]+=10;ui->F13->setReadOnly(true);ui->F13->setStyleSheet("color:red");}
    if(num[4][6]!=0)   {    ui->F21->setText(tempStr.setNum(num[4][6]-10));num[4][6]+=10;ui->F21->setReadOnly(true);ui->F21->setStyleSheet("color:red");}
    if(num[4][7]!=0)   {    ui->F22->setText(tempStr.setNum(num[4][7]-10));num[4][7]+=10;ui->F22->setReadOnly(true);ui->F22->setStyleSheet("color:red");}
    if(num[4][8]!=0)   {    ui->F23->setText(tempStr.setNum(num[4][8]-10));num[4][8]+=10;ui->F23->setReadOnly(true);ui->F23->setStyleSheet("color:red");}
    if(num[5][6]!=0)   {    ui->F31->setText(tempStr.setNum(num[5][6]-10));num[5][6]+=10;ui->F31->setReadOnly(true);ui->F31->setStyleSheet("color:red");}
    if(num[5][7]!=0)   {    ui->F32->setText(tempStr.setNum(num[5][7]-10));num[5][7]+=10;ui->F32->setReadOnly(true);ui->F32->setStyleSheet("color:red");}
    if(num[5][8]!=0)   {    ui->F33->setText(tempStr.setNum(num[5][8]-10));num[5][8]+=10;ui->F33->setReadOnly(true);ui->F33->setStyleSheet("color:red");}
    if(num[6][0]!=0)   {    ui->G11->setText(tempStr.setNum(num[6][0]-10));num[6][0]+=10;ui->G11->setReadOnly(true);ui->G11->setStyleSheet("color:red");}
    if(num[6][1]!=0)   {    ui->G12->setText(tempStr.setNum(num[6][1]-10));num[6][1]+=10;ui->G12->setReadOnly(true);ui->G12->setStyleSheet("color:red");}
    if(num[6][2]!=0)   {    ui->G13->setText(tempStr.setNum(num[6][2]-10));num[6][2]+=10;ui->G13->setReadOnly(true);ui->G13->setStyleSheet("color:red");}
    if(num[7][0]!=0)   {    ui->G21->setText(tempStr.setNum(num[7][0]-10));num[7][0]+=10;ui->G21->setReadOnly(true);ui->G21->setStyleSheet("color:red");}
    if(num[7][1]!=0)   {    ui->G22->setText(tempStr.setNum(num[7][1]-10));num[7][1]+=10;ui->G22->setReadOnly(true);ui->G22->setStyleSheet("color:red");}
    if(num[7][2]!=0)   {    ui->G23->setText(tempStr.setNum(num[7][2]-10));num[7][2]+=10;ui->G23->setReadOnly(true);ui->G23->setStyleSheet("color:red");}
    if(num[8][0]!=0)   {    ui->G31->setText(tempStr.setNum(num[8][0]-10));num[8][0]+=10;ui->G31->setReadOnly(true);ui->G31->setStyleSheet("color:red");}
    if(num[8][1]!=0)   {    ui->G32->setText(tempStr.setNum(num[8][1]-10));num[8][1]+=10;ui->G32->setReadOnly(true);ui->G32->setStyleSheet("color:red");}
    if(num[8][2]!=0)   {    ui->G33->setText(tempStr.setNum(num[8][2]-10));num[8][2]+=10;ui->G33->setReadOnly(true);ui->G33->setStyleSheet("color:red");}
    if(num[6][3]!=0)   {    ui->H11->setText(tempStr.setNum(num[6][3]-10));num[6][3]+=10;ui->H11->setReadOnly(true);ui->H11->setStyleSheet("color:red");}
    if(num[6][4]!=0)   {    ui->H12->setText(tempStr.setNum(num[6][4]-10));num[6][4]+=10;ui->H12->setReadOnly(true);ui->H12->setStyleSheet("color:red");}
    if(num[6][5]!=0)   {    ui->H13->setText(tempStr.setNum(num[6][5]-10));num[6][5]+=10;ui->H13->setReadOnly(true);ui->H13->setStyleSheet("color:red");}
    if(num[7][3]!=0)   {    ui->H21->setText(tempStr.setNum(num[7][3]-10));num[7][3]+=10;ui->H21->setReadOnly(true);ui->H21->setStyleSheet("color:red");}
    if(num[7][4]!=0)   {    ui->H22->setText(tempStr.setNum(num[7][4]-10));num[7][4]+=10;ui->H22->setReadOnly(true);ui->H22->setStyleSheet("color:red");}
    if(num[7][5]!=0)   {    ui->H23->setText(tempStr.setNum(num[7][5]-10));num[7][5]+=10;ui->H23->setReadOnly(true);ui->H23->setStyleSheet("color:red");}
    if(num[8][3]!=0)   {    ui->H31->setText(tempStr.setNum(num[8][3]-10));num[8][3]+=10;ui->H31->setReadOnly(true);ui->H31->setStyleSheet("color:red");}
    if(num[8][4]!=0)   {    ui->H32->setText(tempStr.setNum(num[8][4]-10));num[8][4]+=10;ui->H32->setReadOnly(true);ui->H32->setStyleSheet("color:red");}
    if(num[8][5]!=0)   {    ui->H33->setText(tempStr.setNum(num[8][5]-10));num[8][5]+=10;ui->H33->setReadOnly(true);ui->H33->setStyleSheet("color:red");}
    if(num[6][6]!=0)   {    ui->I11->setText(tempStr.setNum(num[6][6]-10));num[6][6]+=10;ui->I11->setReadOnly(true);ui->I11->setStyleSheet("color:red");}
    if(num[6][7]!=0)   {    ui->I12->setText(tempStr.setNum(num[6][7]-10));num[6][7]+=10;ui->I12->setReadOnly(true);ui->I12->setStyleSheet("color:red");}
    if(num[6][8]!=0)   {    ui->I13->setText(tempStr.setNum(num[6][8]-10));num[6][8]+=10;ui->I13->setReadOnly(true);ui->I13->setStyleSheet("color:red");}
    if(num[7][6]!=0)   {    ui->I21->setText(tempStr.setNum(num[7][6]-10));num[7][6]+=10;ui->I21->setReadOnly(true);ui->I21->setStyleSheet("color:red");}
    if(num[7][7]!=0)   {    ui->I22->setText(tempStr.setNum(num[7][7]-10));num[7][7]+=10;ui->I22->setReadOnly(true);ui->I22->setStyleSheet("color:red");}
    if(num[7][8]!=0)   {    ui->I23->setText(tempStr.setNum(num[7][8]-10));num[7][8]+=10;ui->I23->setReadOnly(true);ui->I23->setStyleSheet("color:red");}
    if(num[8][6]!=0)   {    ui->I31->setText(tempStr.setNum(num[8][6]-10));num[8][6]+=10;ui->I31->setReadOnly(true);ui->I31->setStyleSheet("color:red");}
    if(num[8][7]!=0)   {    ui->I32->setText(tempStr.setNum(num[8][7]-10));num[8][7]+=10;ui->I32->setReadOnly(true);ui->I32->setStyleSheet("color:red");}
    if(num[8][8]!=0)   {    ui->I33->setText(tempStr.setNum(num[8][8]-10));num[8][8]+=10;ui->I33->setReadOnly(true);ui->I33->setStyleSheet("color:red");}
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->BtnSolve->setEnabled(false);
}
void MainWindow::upgradeWhenFailed()//当判断为“失败”时执行该函数，负责将判断时被转为负值的num转回正值，且用蓝色显示错误的数
{
    QString tempStr;
        if(num[0][0]<0)   {    ui->A11->setText(tempStr.setNum(-num[0][0]));ui->A11->setReadOnly(false);ui->A11->setStyleSheet("color:blue");}
        if(num[0][1]<0)   {    ui->A12->setText(tempStr.setNum(-num[0][1]));ui->A12->setReadOnly(false);ui->A12->setStyleSheet("color:blue");}
        if(num[0][2]<0)   {    ui->A13->setText(tempStr.setNum(-num[0][2]));ui->A13->setReadOnly(false);ui->A13->setStyleSheet("color:blue");}
        if(num[1][0]<0)   {    ui->A21->setText(tempStr.setNum(-num[1][0]));ui->A21->setReadOnly(false);ui->A21->setStyleSheet("color:blue");}
        if(num[1][1]<0)   {    ui->A22->setText(tempStr.setNum(-num[1][1]));ui->A22->setReadOnly(false);ui->A22->setStyleSheet("color:blue");}
        if(num[1][2]<0)   {    ui->A23->setText(tempStr.setNum(-num[1][2]));ui->A23->setReadOnly(false);ui->A23->setStyleSheet("color:blue");}
        if(num[2][0]<0)   {    ui->A31->setText(tempStr.setNum(-num[2][0]));ui->A31->setReadOnly(false);ui->A31->setStyleSheet("color:blue");}
        if(num[2][1]<0)   {    ui->A32->setText(tempStr.setNum(-num[2][1]));ui->A32->setReadOnly(false);ui->A32->setStyleSheet("color:blue");}
        if(num[2][2]<0)   {    ui->A33->setText(tempStr.setNum(-num[2][2]));ui->A33->setReadOnly(false);ui->A33->setStyleSheet("color:blue");}
        if(num[0][3]<0)   {    ui->B11->setText(tempStr.setNum(-num[0][3]));ui->B11->setReadOnly(false);ui->B11->setStyleSheet("color:blue");}
        if(num[0][4]<0)   {    ui->B12->setText(tempStr.setNum(-num[0][4]));ui->B12->setReadOnly(false);ui->B12->setStyleSheet("color:blue");}
        if(num[0][5]<0)   {    ui->B13->setText(tempStr.setNum(-num[0][5]));ui->B13->setReadOnly(false);ui->B13->setStyleSheet("color:blue");}
        if(num[1][3]<0)   {    ui->B21->setText(tempStr.setNum(-num[1][3]));ui->B21->setReadOnly(false);ui->B21->setStyleSheet("color:blue");}
        if(num[1][4]<0)   {    ui->B22->setText(tempStr.setNum(-num[1][4]));ui->B22->setReadOnly(false);ui->B22->setStyleSheet("color:blue");}
        if(num[1][5]<0)   {    ui->B23->setText(tempStr.setNum(-num[1][5]));ui->B23->setReadOnly(false);ui->B23->setStyleSheet("color:blue");}
        if(num[2][3]<0)   {    ui->B31->setText(tempStr.setNum(-num[2][3]));ui->B31->setReadOnly(false);ui->B31->setStyleSheet("color:blue");}
        if(num[2][4]<0)   {    ui->B32->setText(tempStr.setNum(-num[2][4]));ui->B32->setReadOnly(false);ui->B32->setStyleSheet("color:blue");}
        if(num[2][5]<0)   {    ui->B33->setText(tempStr.setNum(-num[2][5]));ui->B33->setReadOnly(false);ui->B33->setStyleSheet("color:blue");}
        if(num[0][6]<0)   {    ui->C11->setText(tempStr.setNum(-num[0][6]));ui->C11->setReadOnly(false);ui->C11->setStyleSheet("color:blue");}
        if(num[0][7]<0)   {    ui->C12->setText(tempStr.setNum(-num[0][7]));ui->C12->setReadOnly(false);ui->C12->setStyleSheet("color:blue");}
        if(num[0][8]<0)   {    ui->C13->setText(tempStr.setNum(-num[0][8]));ui->C13->setReadOnly(false);ui->C13->setStyleSheet("color:blue");}
        if(num[1][6]<0)   {    ui->C21->setText(tempStr.setNum(-num[1][6]));ui->C21->setReadOnly(false);ui->C21->setStyleSheet("color:blue");}
        if(num[1][7]<0)   {    ui->C22->setText(tempStr.setNum(-num[1][7]));ui->C22->setReadOnly(false);ui->C22->setStyleSheet("color:blue");}
        if(num[1][8]<0)   {    ui->C23->setText(tempStr.setNum(-num[1][8]));ui->C23->setReadOnly(false);ui->C23->setStyleSheet("color:blue");}
        if(num[2][6]<0)   {    ui->C31->setText(tempStr.setNum(-num[2][6]));ui->C31->setReadOnly(false);ui->C31->setStyleSheet("color:blue");}
        if(num[2][7]<0)   {    ui->C32->setText(tempStr.setNum(-num[2][7]));ui->C32->setReadOnly(false);ui->C32->setStyleSheet("color:blue");}
        if(num[2][8]<0)   {    ui->C33->setText(tempStr.setNum(-num[2][8]));ui->C33->setReadOnly(false);ui->C33->setStyleSheet("color:blue");}
        if(num[3][0]<0)   {    ui->D11->setText(tempStr.setNum(-num[3][0]));ui->D11->setReadOnly(false);ui->D11->setStyleSheet("color:blue");}
        if(num[3][1]<0)   {    ui->D12->setText(tempStr.setNum(-num[3][1]));ui->D12->setReadOnly(false);ui->D12->setStyleSheet("color:blue");}
        if(num[3][2]<0)   {    ui->D13->setText(tempStr.setNum(-num[3][2]));ui->D13->setReadOnly(false);ui->D13->setStyleSheet("color:blue");}
        if(num[4][0]<0)   {    ui->D21->setText(tempStr.setNum(-num[4][0]));ui->D21->setReadOnly(false);ui->D21->setStyleSheet("color:blue");}
        if(num[4][1]<0)   {    ui->D22->setText(tempStr.setNum(-num[4][1]));ui->D22->setReadOnly(false);ui->D22->setStyleSheet("color:blue");}
        if(num[4][2]<0)   {    ui->D23->setText(tempStr.setNum(-num[4][2]));ui->D23->setReadOnly(false);ui->D23->setStyleSheet("color:blue");}
        if(num[5][0]<0)   {    ui->D31->setText(tempStr.setNum(-num[5][0]));ui->D31->setReadOnly(false);ui->D31->setStyleSheet("color:blue");}
        if(num[5][1]<0)   {    ui->D32->setText(tempStr.setNum(-num[5][1]));ui->D32->setReadOnly(false);ui->D32->setStyleSheet("color:blue");}
        if(num[5][2]<0)   {    ui->D33->setText(tempStr.setNum(-num[5][2]));ui->D33->setReadOnly(false);ui->D33->setStyleSheet("color:blue");}
        if(num[3][3]<0)   {    ui->E11->setText(tempStr.setNum(-num[3][3]));ui->E11->setReadOnly(false);ui->E11->setStyleSheet("color:blue");}
        if(num[3][4]<0)   {    ui->E12->setText(tempStr.setNum(-num[3][4]));ui->E12->setReadOnly(false);ui->E12->setStyleSheet("color:blue");}
        if(num[3][5]<0)   {    ui->E13->setText(tempStr.setNum(-num[3][5]));ui->E13->setReadOnly(false);ui->E13->setStyleSheet("color:blue");}
        if(num[4][3]<0)   {    ui->E21->setText(tempStr.setNum(-num[4][3]));ui->E21->setReadOnly(false);ui->E21->setStyleSheet("color:blue");}
        if(num[4][4]<0)   {    ui->E22->setText(tempStr.setNum(-num[4][4]));ui->E22->setReadOnly(false);ui->E22->setStyleSheet("color:blue");}
        if(num[4][5]<0)   {    ui->E23->setText(tempStr.setNum(-num[4][5]));ui->E23->setReadOnly(false);ui->E23->setStyleSheet("color:blue");}
        if(num[5][3]<0)   {    ui->E31->setText(tempStr.setNum(-num[5][3]));ui->E31->setReadOnly(false);ui->E31->setStyleSheet("color:blue");}
        if(num[5][4]<0)   {    ui->E32->setText(tempStr.setNum(-num[5][4]));ui->E32->setReadOnly(false);ui->E32->setStyleSheet("color:blue");}
        if(num[5][5]<0)   {    ui->E33->setText(tempStr.setNum(-num[5][5]));ui->E33->setReadOnly(false);ui->E33->setStyleSheet("color:blue");}
        if(num[3][6]<0)   {    ui->F11->setText(tempStr.setNum(-num[3][6]));ui->F11->setReadOnly(false);ui->F11->setStyleSheet("color:blue");}
        if(num[3][7]<0)   {    ui->F12->setText(tempStr.setNum(-num[3][7]));ui->F12->setReadOnly(false);ui->F12->setStyleSheet("color:blue");}
        if(num[3][8]<0)   {    ui->F13->setText(tempStr.setNum(-num[3][8]));ui->F13->setReadOnly(false);ui->F13->setStyleSheet("color:blue");}
        if(num[4][6]<0)   {    ui->F21->setText(tempStr.setNum(-num[4][6]));ui->F21->setReadOnly(false);ui->F21->setStyleSheet("color:blue");}
        if(num[4][7]<0)   {    ui->F22->setText(tempStr.setNum(-num[4][7]));ui->F22->setReadOnly(false);ui->F22->setStyleSheet("color:blue");}
        if(num[4][8]<0)   {    ui->F23->setText(tempStr.setNum(-num[4][8]));ui->F23->setReadOnly(false);ui->F23->setStyleSheet("color:blue");}
        if(num[5][6]<0)   {    ui->F31->setText(tempStr.setNum(-num[5][6]));ui->F31->setReadOnly(false);ui->F31->setStyleSheet("color:blue");}
        if(num[5][7]<0)   {    ui->F32->setText(tempStr.setNum(-num[5][7]));ui->F32->setReadOnly(false);ui->F32->setStyleSheet("color:blue");}
        if(num[5][8]<0)   {    ui->F33->setText(tempStr.setNum(-num[5][8]));ui->F33->setReadOnly(false);ui->F33->setStyleSheet("color:blue");}
        if(num[6][0]<0)   {    ui->G11->setText(tempStr.setNum(-num[6][0]));ui->G11->setReadOnly(false);ui->G11->setStyleSheet("color:blue");}
        if(num[6][1]<0)   {    ui->G12->setText(tempStr.setNum(-num[6][1]));ui->G12->setReadOnly(false);ui->G12->setStyleSheet("color:blue");}
        if(num[6][2]<0)   {    ui->G13->setText(tempStr.setNum(-num[6][2]));ui->G13->setReadOnly(false);ui->G13->setStyleSheet("color:blue");}
        if(num[7][0]<0)   {    ui->G21->setText(tempStr.setNum(-num[7][0]));ui->G21->setReadOnly(false);ui->G21->setStyleSheet("color:blue");}
        if(num[7][1]<0)   {    ui->G22->setText(tempStr.setNum(-num[7][1]));ui->G22->setReadOnly(false);ui->G22->setStyleSheet("color:blue");}
        if(num[7][2]<0)   {    ui->G23->setText(tempStr.setNum(-num[7][2]));ui->G23->setReadOnly(false);ui->G23->setStyleSheet("color:blue");}
        if(num[8][0]<0)   {    ui->G31->setText(tempStr.setNum(-num[8][0]));ui->G31->setReadOnly(false);ui->G31->setStyleSheet("color:blue");}
        if(num[8][1]<0)   {    ui->G32->setText(tempStr.setNum(-num[8][1]));ui->G32->setReadOnly(false);ui->G32->setStyleSheet("color:blue");}
        if(num[8][2]<0)   {    ui->G33->setText(tempStr.setNum(-num[8][2]));ui->G33->setReadOnly(false);ui->G33->setStyleSheet("color:blue");}
        if(num[6][3]<0)   {    ui->H11->setText(tempStr.setNum(-num[6][3]));ui->H11->setReadOnly(false);ui->H11->setStyleSheet("color:blue");}
        if(num[6][4]<0)   {    ui->H12->setText(tempStr.setNum(-num[6][4]));ui->H12->setReadOnly(false);ui->H12->setStyleSheet("color:blue");}
        if(num[6][5]<0)   {    ui->H13->setText(tempStr.setNum(-num[6][5]));ui->H13->setReadOnly(false);ui->H13->setStyleSheet("color:blue");}
        if(num[7][3]<0)   {    ui->H21->setText(tempStr.setNum(-num[7][3]));ui->H21->setReadOnly(false);ui->H21->setStyleSheet("color:blue");}
        if(num[7][4]<0)   {    ui->H22->setText(tempStr.setNum(-num[7][4]));ui->H22->setReadOnly(false);ui->H22->setStyleSheet("color:blue");}
        if(num[7][5]<0)   {    ui->H23->setText(tempStr.setNum(-num[7][5]));ui->H23->setReadOnly(false);ui->H23->setStyleSheet("color:blue");}
        if(num[8][3]<0)   {    ui->H31->setText(tempStr.setNum(-num[8][3]));ui->H31->setReadOnly(false);ui->H31->setStyleSheet("color:blue");}
        if(num[8][4]<0)   {    ui->H32->setText(tempStr.setNum(-num[8][4]));ui->H32->setReadOnly(false);ui->H32->setStyleSheet("color:blue");}
        if(num[8][5]<0)   {    ui->H33->setText(tempStr.setNum(-num[8][5]));ui->H33->setReadOnly(false);ui->H33->setStyleSheet("color:blue");}
        if(num[6][6]<0)   {    ui->I11->setText(tempStr.setNum(-num[6][6]));ui->I11->setReadOnly(false);ui->I11->setStyleSheet("color:blue");}
        if(num[6][7]<0)   {    ui->I12->setText(tempStr.setNum(-num[6][7]));ui->I12->setReadOnly(false);ui->I12->setStyleSheet("color:blue");}
        if(num[6][8]<0)   {    ui->I13->setText(tempStr.setNum(-num[6][8]));ui->I13->setReadOnly(false);ui->I13->setStyleSheet("color:blue");}
        if(num[7][6]<0)   {    ui->I21->setText(tempStr.setNum(-num[7][6]));ui->I21->setReadOnly(false);ui->I21->setStyleSheet("color:blue");}
        if(num[7][7]<0)   {    ui->I22->setText(tempStr.setNum(-num[7][7]));ui->I22->setReadOnly(false);ui->I22->setStyleSheet("color:blue");}
        if(num[7][8]<0)   {    ui->I23->setText(tempStr.setNum(-num[7][8]));ui->I23->setReadOnly(false);ui->I23->setStyleSheet("color:blue");}
        if(num[8][6]<0)   {    ui->I31->setText(tempStr.setNum(-num[8][6]));ui->I31->setReadOnly(false);ui->I31->setStyleSheet("color:blue");}
        if(num[8][7]<0)   {    ui->I32->setText(tempStr.setNum(-num[8][7]));ui->I32->setReadOnly(false);ui->I32->setStyleSheet("color:blue");}
        if(num[8][8]<0)   {    ui->I33->setText(tempStr.setNum(-num[8][8]));ui->I33->setReadOnly(false);ui->I33->setStyleSheet("color:blue");}
}
void MainWindow::set_readonly(bool a)//设置全部单元格的只读属性
{
    ui->A11->setReadOnly(a);
    ui->A12->setReadOnly(a);
    ui->A13->setReadOnly(a);
    ui->A21->setReadOnly(a);
    ui->A22->setReadOnly(a);
    ui->A23->setReadOnly(a);
    ui->A31->setReadOnly(a);
    ui->A32->setReadOnly(a);
    ui->A33->setReadOnly(a);
    ui->B11->setReadOnly(a);
    ui->B12->setReadOnly(a);
    ui->B13->setReadOnly(a);
    ui->B21->setReadOnly(a);
    ui->B22->setReadOnly(a);
    ui->B23->setReadOnly(a);
    ui->B31->setReadOnly(a);
    ui->B32->setReadOnly(a);
    ui->B33->setReadOnly(a);
    ui->C11->setReadOnly(a);
    ui->C12->setReadOnly(a);
    ui->C13->setReadOnly(a);
    ui->C21->setReadOnly(a);
    ui->C22->setReadOnly(a);
    ui->C23->setReadOnly(a);
    ui->C31->setReadOnly(a);
    ui->C32->setReadOnly(a);
    ui->C33->setReadOnly(a);
    ui->D11->setReadOnly(a);
    ui->D12->setReadOnly(a);
    ui->D13->setReadOnly(a);
    ui->D21->setReadOnly(a);
    ui->D22->setReadOnly(a);
    ui->D23->setReadOnly(a);
    ui->D31->setReadOnly(a);
    ui->D32->setReadOnly(a);
    ui->D33->setReadOnly(a);
    ui->E11->setReadOnly(a);
    ui->E12->setReadOnly(a);
    ui->E13->setReadOnly(a);
    ui->E21->setReadOnly(a);
    ui->E22->setReadOnly(a);
    ui->E23->setReadOnly(a);
    ui->E31->setReadOnly(a);
    ui->E32->setReadOnly(a);
    ui->E33->setReadOnly(a);
    ui->F11->setReadOnly(a);
    ui->F12->setReadOnly(a);
    ui->F13->setReadOnly(a);
    ui->F21->setReadOnly(a);
    ui->F22->setReadOnly(a);
    ui->F23->setReadOnly(a);
    ui->F31->setReadOnly(a);
    ui->F32->setReadOnly(a);
    ui->F33->setReadOnly(a);
    ui->G11->setReadOnly(a);
    ui->G12->setReadOnly(a);
    ui->G13->setReadOnly(a);
    ui->G21->setReadOnly(a);
    ui->G22->setReadOnly(a);
    ui->G23->setReadOnly(a);
    ui->G31->setReadOnly(a);
    ui->G32->setReadOnly(a);
    ui->G33->setReadOnly(a);
    ui->H11->setReadOnly(a);
    ui->H12->setReadOnly(a);
    ui->H13->setReadOnly(a);
    ui->H21->setReadOnly(a);
    ui->H22->setReadOnly(a);
    ui->H23->setReadOnly(a);
    ui->H31->setReadOnly(a);
    ui->H32->setReadOnly(a);
    ui->H33->setReadOnly(a);
    ui->I11->setReadOnly(a);
    ui->I12->setReadOnly(a);
    ui->I13->setReadOnly(a);
    ui->I21->setReadOnly(a);
    ui->I22->setReadOnly(a);
    ui->I23->setReadOnly(a);
    ui->I31->setReadOnly(a);
    ui->I32->setReadOnly(a);
    ui->I33->setReadOnly(a);
}
bool checkWhenGenerating(int temp[][9])//使用回溯法生成数独是调用，检查填入当前数之后是否合法
{
    //检查行
    for(int i = 0; i < 9; i++)
    {
        int tempArr[9] = {0};

        for(int j = 0; j < 9; j++)
        {
            if(temp[i][j] != 0)
            {
                if(tempArr[temp[i][j] - 1] == 0)
                {
                    tempArr[temp[i][j] - 1] = 1;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    //检查列
    for(int j = 0; j < 9; j++)
    {
        int tempArr[9] = {0};

        for(int i = 0; i < 9; i++)
        {
            if(temp[i][j] != 0)
            {
                if(tempArr[temp[i][j] - 1] == 0)
                {
                    tempArr[temp[i][j] - 1] = 1;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    //检查宫
    for(int m = 0; m < 9; m += 3)
    {
        for(int n = 0; n < 9; n += 3)
        {
            int tempArr[9] = {0};

            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    if(temp[m + i][n + j] != 0)
                    {
                        if(tempArr[temp[m + i][n + j] - 1] == 0)
                        {
                            tempArr[temp[m + i][n + j] - 1] = 1;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
void generateNewGame(int n,int num[][9])//回溯法生成新游戏，用于中等和困难模式
{                                       //跳过了右上、中间、左下三个宫里的数，这三个宫相互独立，所以通过将1~9分别随机填入三个宫产生
    if(81==n)
    {
        done=1;                         //当这个标记为1时，跳过后续所有递归
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                num[i][j]+=10;          //全部+10处理是为了适应“题给常数为11~19间的数”这一规则
        return;
    }
    else if     (n==6||n==7||n==8||n==30||n==31||n==32||n==54||n==55||n==56||
                n==15||n==16||n==17||n==39||n==40||n==41||n==63||n==64||n==65||
                n==24||n==25||n==26||n==48||n==49||n==50||n==72||n==73||n==74)
        generateNewGame(n+1,num);
    else
    {
        for(int i = 1; i < 10; i++)
        {
            num[n/9][n%9]=i;
            if(checkWhenGenerating(num) && !done) generateNewGame(n+1,num);
            if(done) break;
        }
        if(!done) num[n/9][n%9]=0;
        return;
    }
}
void MainWindow::on_pushButton_clicked()
{
    newGameInitial();
    if(ui->REasy->isChecked()) //简单模式通过对一个模板赋值实现，题目有非常明显的规律，解不具有唯一性
    {
        srand(static_cast<unsigned int>(time(0)));
        int temp[9]={0};
        for(int i=0;i<9;i++)
            {
                temp[i]=1+rand()%9;
                for(int j=0;j<i;j++)
                    if(temp[j]==temp[i])
                    {
                        i--;
                        break;
                    }
            }
        char model[9][9] = {
            { 'i','g','h','c','a','b','f','d','e' },{ 'c','a','b','f','d','e','i','g','h' },{ 'f','d','e','i','g','h','c','a','b' },{ 'g','h','i','a','b','c','d','e','f' },{ 'a','b','c','d','e','f','g','h','i' },{ 'd','e','f','g','h','i','a','b','c' },{ 'h','i','g','b','c','a','e','f','d' },
            { 'b','c','a','e','f','d','h','i','g' },{ 'e','f','d','h','i','g','b','c','a' }
        };
        for (int i = 0; i<9; i++)
            {
                for (int j = 0; j<9; j++)
                {
                    if (model[i][j] == 'a') num[i][j] = temp[0]+10;
                    else if (model[i][j] == 'b') num[i][j] = temp[1]+10;
                    else if (model[i][j] == 'c') num[i][j] = temp[2]+10;
                    else if (model[i][j] == 'd') num[i][j] = temp[3]+10;
                    else if (model[i][j] == 'e') num[i][j] = temp[4]+10;
                    else if (model[i][j] == 'f') num[i][j] = temp[5]+10;
                    else if (model[i][j] == 'g') num[i][j] = temp[6]+10;
                    else if (model[i][j] == 'h') num[i][j] = temp[7]+10;
                    else if (model[i][j] == 'i') num[i][j] = temp[8]+10;
                }
            }
        for(int count=1;count<=40;count++)
        {
            int i=rand()%9;
            int j=rand()%9;
            if(num[i][j]!=0) num[i][j]=0;
            else count--;
        }
    }
    else //中等和困难难度采用回溯法出题，区别在于挖空的多少
    {
        srand(static_cast<unsigned int>(time(0)));  //给对角线上的三个宫随机赋值
        int tempseed[27];
        for(int i=0;i<9;i++)
        {
            tempseed[i]=rand()%9+1;
            for(int j=0;j<i;j++)
                if(tempseed[i]==tempseed[j]){tempseed[i]=0; i--; break;}
        }
        for(int i=9;i<18;i++)
        {
            tempseed[i]=rand()%9+1;
            for(int j=9;j<i;j++)
                if(tempseed[i]==tempseed[j]){tempseed[i]=0; i--; break;}
        }
        for(int i=18;i<27;i++)
        {
            tempseed[i]=rand()%9+1;
            for(int j=18;j<i;j++)
                if(tempseed[i]==tempseed[j]){tempseed[i]=0; i--; break;}
        }
        num[0][6]=tempseed[0];num[0][7]=tempseed[1];num[0][8]=tempseed[2];num[1][6]=tempseed[3];num[1][7]=tempseed[4];num[1][8]=tempseed[5];num[2][6]=tempseed[6];num[2][7]=tempseed[7];num[2][8]=tempseed[8];
        num[3][3]=tempseed[9];num[3][4]=tempseed[10];num[3][5]=tempseed[11];num[4][3]=tempseed[12];num[4][4]=tempseed[13];num[4][5]=tempseed[14];num[5][3]=tempseed[15];num[5][4]=tempseed[16];num[5][5]=tempseed[17];
        num[6][0]=tempseed[18];num[6][1]=tempseed[19];num[6][2]=tempseed[20];num[7][0]=tempseed[21];num[7][1]=tempseed[22];num[7][2]=tempseed[23];num[8][0]=tempseed[24];num[8][1]=tempseed[25];num[8][2]=tempseed[26];
        done=0;
        generateNewGame(0,num);
        int temp[9][9];
        for(int i=0;i<9;i++) for(int j=0;j<9;j++) temp[i][j]=num[i][j]; //存储此时num的情况
 label: if(ui->RMedium->isChecked())
        {            
            for(int count=1;count<=35;count++)
            {
                int i=rand()%9;
                int j=rand()%9;
                if(num[i][j]!=0) num[i][j]=0;
                else count--;
            }
        }
        else //困难难度
        {
            for(int count=1;count<=45;count++)
            {
                int i=rand()%9;
                int j=rand()%9;
                if(num[i][j]!=0) num[i][j]=0;
                else count--;
            }
        }
        num_of_solution=0;
        checkUniqueInitial();
        checkUnique(0,0);
        if(num_of_solution!=1)   //如果不具有唯一解
        {
            for(int i=0;i<9;i++)
                for(int j=0;j<9;j++)
                    num[i][j]=temp[i][j];  //恢复挖空之前的num
            srand(static_cast<unsigned int>(time(0)));
            goto label;  //重新挖空
        }
    }
    upgradeHavingGeneratedSudoku();
}
void MainWindow::on_pushButton_2_clicked() //按下“提交”按钮时，判断当前答案是否正确。
{
   if(judgeWhenSubmitted(num))             //如果成功，重置“做数独”按钮，可以开始新游戏
   {
       ui->result->setText("Succeed");
       ui->pushButton->setEnabled(true);
   }
   else                                    //如果失败，用蓝色输出错误之处
   {
       ui->result->setText("Failed");
       upgradeWhenFailed();
   }
}
//**************************************************************************************************************
//以上做数独部分由赵逸凡完成↑
//以下解数独部分由陈浩宇完成↓
//**************************************************************************************************************
int MainWindow::check(int row,int col) //用于回溯法解数独，检查当前情形是否合法
{
    //检查行
     for(int i=0;i<9;i++)
     {
        if(col==i)
        continue;
        if(sudoku[row][i]==sudoku[row][col])
        return 0;
     }
     //检查列
     for(int i=0;i<9;i++)
     {
        if(row==i)
        continue;
        if(sudoku[i][col]==sudoku[row][col])
        return 0;
      }
      //检查宫格
     int min_row=3*(row/3);
     int min_col=3*(col/3);
     for(int i=min_row;i<min_row+3;i++)
     {
        for(int j=min_col;j<min_col+3;j++)
        {
            if((i==row)&&(j==col))
            continue;
            if(sudoku[i][j]==sudoku[row][col])
            return 0;
         }
       }
     return 1;
}
void MainWindow::solve(int row,int col)//回溯法解数独，与checkUnique()基本相同
{
    while(flag[row][col])//已经填数
    {
        col++;
        if((10==col))
        {
            row++;
            col=0;
        }
        if(row==9)
        {
            outfile<<"One possible version:"<<endl;
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<9;j++)
                {
                    outfile<<sudoku[i][j]<<"\t";
                }
                outfile<<endl;
            }
            num_of_solution++;
            goto end;
        }
    }

    for(int i=1;i<10;i++)
    {
        sudoku[row][col]=i;
        if(check(row,col))
            solve(row,col+1);
    }
    end:sudoku[row][col]=0;
}
void MainWindow::on_BtnSolve_clicked()//点击“解数独”按钮时，关闭做数独功能
{
    ui->BtnSubmit->setEnabled(true);
    ui->BtnSolve->setEnabled(false);
    ui->pushButton->setEnabled(false);
    set_readonly(false);
}
void MainWindow::on_BtnSubmit_clicked()//点击“提交”时，解数独并输出到"result.tsv"文件。
{
    num_of_solution=0;
    outfile.open("result.tsv");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            flag[i][j]=1;
        }
    }
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            sudoku[i][j] = num[i][j];
            if(sudoku[i][j]==0)
            {
                flag[i][j]=0;
            } //为0（未填数）标记为0
        }
    }//读入二维数组
    solve(0,0);
    if(num_of_solution==1)
        outfile<<"ONLY one solution"<<endl;
    else if(num_of_solution==0)
        outfile<<"No solution"<<endl;
    ui->BtnSubmit->setEnabled(false);
    ui->result->setText("Done");
    QMessageBox::about(NULL, "Done", "Output has been saved as \"result.tsv\".");
}
//**************************************************************************************************************

//以下为81个单元格的输入与num数组的关联↓
//**************************************************************************************************************
void MainWindow::on_A11_textChanged()
{
    bool ok;ui->A11->setStyleSheet("color:black");
    QString valueStr=ui->A11->text();
    num[0][0]= valueStr.toInt(&ok);
}
void MainWindow::on_A12_textChanged()
{
    bool ok;ui->A12->setStyleSheet("color:black");
    QString valueStr=ui->A12->text();
    num[0][1]= valueStr.toInt(&ok);
}
void MainWindow::on_A13_textChanged()
{
    bool ok;ui->A13->setStyleSheet("color:black");
    QString valueStr=ui->A13->text();
    num[0][2]= valueStr.toInt(&ok);
}
void MainWindow::on_A21_textChanged()
{
    bool ok;ui->A21->setStyleSheet("color:black");
    QString valueStr=ui->A21->text();
    num[1][0]= valueStr.toInt(&ok);
}
void MainWindow::on_A22_textChanged()
{
    bool ok;ui->A22->setStyleSheet("color:black");
    QString valueStr=ui->A22->text();
    num[1][1]= valueStr.toInt(&ok);
}
void MainWindow::on_A23_textChanged()
{
    bool ok;ui->A23->setStyleSheet("color:black");
    QString valueStr=ui->A23->text();
    num[1][2]= valueStr.toInt(&ok);
}
void MainWindow::on_A31_textChanged()
{
    bool ok;ui->A31->setStyleSheet("color:black");
    QString valueStr=ui->A31->text();
    num[2][0]= valueStr.toInt(&ok);
}
void MainWindow::on_A32_textChanged()
{
    bool ok;ui->A32->setStyleSheet("color:black");
    QString valueStr=ui->A32->text();
    num[2][1]= valueStr.toInt(&ok);
}
void MainWindow::on_A33_textChanged()
{
    bool ok;ui->A33->setStyleSheet("color:black");
    QString valueStr=ui->A33->text();
    num[2][2]= valueStr.toInt(&ok);
}
void MainWindow::on_B11_textChanged()
{
    bool ok;ui->B11->setStyleSheet("color:black");
    QString valueStr=ui->B11->text();
    num[0][3]= valueStr.toInt(&ok);
}
void MainWindow::on_B12_textChanged()
{
    bool ok;ui->B12->setStyleSheet("color:black");
    QString valueStr=ui->B12->text();
    num[0][4]= valueStr.toInt(&ok);
}
void MainWindow::on_B13_textChanged()
{
    bool ok;ui->B13->setStyleSheet("color:black");
    QString valueStr=ui->B13->text();
    num[0][5]= valueStr.toInt(&ok);
}
void MainWindow::on_B21_textChanged()
{
    bool ok;ui->B21->setStyleSheet("color:black");
    QString valueStr=ui->B21->text();
    num[1][3]= valueStr.toInt(&ok);
}
void MainWindow::on_B22_textChanged()
{
    bool ok;ui->B22->setStyleSheet("color:black");
    QString valueStr=ui->B22->text();
    num[1][4]= valueStr.toInt(&ok);
}
void MainWindow::on_B23_textChanged()
{
    bool ok;ui->B23->setStyleSheet("color:black");
    QString valueStr=ui->B23->text();
    num[1][5]= valueStr.toInt(&ok);
}
void MainWindow::on_B31_textChanged()
{
    bool ok;ui->B31->setStyleSheet("color:black");
    QString valueStr=ui->B31->text();
    num[2][3]= valueStr.toInt(&ok);
}
void MainWindow::on_B32_textChanged()
{
    bool ok;ui->B32->setStyleSheet("color:black");
    QString valueStr=ui->B32->text();
    num[2][4]= valueStr.toInt(&ok);
}
void MainWindow::on_B33_textChanged()
{
    bool ok;ui->B33->setStyleSheet("color:black");
    QString valueStr=ui->B33->text();
    num[2][5]= valueStr.toInt(&ok);
}
void MainWindow::on_C11_textChanged()
{
    bool ok;ui->C11->setStyleSheet("color:black");
    QString valueStr=ui->C11->text();
    num[0][6]= valueStr.toInt(&ok);
}
void MainWindow::on_C12_textChanged()
{
    bool ok;ui->C12->setStyleSheet("color:black");
    QString valueStr=ui->C12->text();
    num[0][7]= valueStr.toInt(&ok);
}
void MainWindow::on_C13_textChanged()
{
    bool ok;ui->C13->setStyleSheet("color:black");
    QString valueStr=ui->C13->text();
    num[0][8]= valueStr.toInt(&ok);
}
void MainWindow::on_C21_textChanged()
{
    bool ok;ui->C21->setStyleSheet("color:black");
    QString valueStr=ui->C21->text();
    num[1][6]= valueStr.toInt(&ok);
}
void MainWindow::on_C22_textChanged()
{
    bool ok;ui->C22->setStyleSheet("color:black");
    QString valueStr=ui->C22->text();
    num[1][7]= valueStr.toInt(&ok);
}
void MainWindow::on_C23_textChanged()
{
    bool ok;ui->C23->setStyleSheet("color:black");
    QString valueStr=ui->C23->text();
    num[1][8]= valueStr.toInt(&ok);
}
void MainWindow::on_C31_textChanged()
{
    bool ok;ui->C31->setStyleSheet("color:black");
    QString valueStr=ui->C31->text();
    num[2][6]= valueStr.toInt(&ok);
}
void MainWindow::on_C32_textChanged()
{
    bool ok;ui->C32->setStyleSheet("color:black");
    QString valueStr=ui->C32->text();
    num[2][7]= valueStr.toInt(&ok);
}
void MainWindow::on_C33_textChanged()
{
    bool ok;ui->C33->setStyleSheet("color:black");
    QString valueStr=ui->C33->text();
    num[2][8]= valueStr.toInt(&ok);
}
void MainWindow::on_D11_textChanged()
{
    bool ok;ui->D11->setStyleSheet("color:black");
    QString valueStr=ui->D11->text();
    num[3][0]= valueStr.toInt(&ok);
}
void MainWindow::on_D12_textChanged()
{
    bool ok;ui->D12->setStyleSheet("color:black");
    QString valueStr=ui->D12->text();
    num[3][1]= valueStr.toInt(&ok);
}
void MainWindow::on_D13_textChanged()
{
    bool ok;ui->D13->setStyleSheet("color:black");
    QString valueStr=ui->D13->text();
    num[3][2]= valueStr.toInt(&ok);
}
void MainWindow::on_D21_textChanged()
{
    bool ok;ui->D21->setStyleSheet("color:black");
    QString valueStr=ui->D21->text();
    num[4][0]= valueStr.toInt(&ok);
}
void MainWindow::on_D22_textChanged()
{
    bool ok;ui->D22->setStyleSheet("color:black");
    QString valueStr=ui->D22->text();
    num[4][1]= valueStr.toInt(&ok);
}
void MainWindow::on_D23_textChanged()
{
    bool ok;ui->D23->setStyleSheet("color:black");
    QString valueStr=ui->D23->text();
    num[4][2]= valueStr.toInt(&ok);
}
void MainWindow::on_D31_textChanged()
{
    bool ok;ui->D31->setStyleSheet("color:black");
    QString valueStr=ui->D31->text();
    num[5][0]= valueStr.toInt(&ok);
}
void MainWindow::on_D32_textChanged()
{
    bool ok;ui->D32->setStyleSheet("color:black");
    QString valueStr=ui->D32->text();
    num[5][1]= valueStr.toInt(&ok);
}
void MainWindow::on_D33_textChanged()
{
    bool ok;ui->D33->setStyleSheet("color:black");
    QString valueStr=ui->D33->text();
    num[5][2]= valueStr.toInt(&ok);
}
void MainWindow::on_E11_textChanged()
{
    bool ok;ui->E11->setStyleSheet("color:black");
    QString valueStr=ui->E11->text();
    num[3][3]= valueStr.toInt(&ok);
}
void MainWindow::on_E12_textChanged()
{
    bool ok;ui->E12->setStyleSheet("color:black");
    QString valueStr=ui->E12->text();
    num[3][4]= valueStr.toInt(&ok);
}
void MainWindow::on_E13_textChanged()
{
    bool ok;ui->E13->setStyleSheet("color:black");
    QString valueStr=ui->E13->text();
    num[3][5]= valueStr.toInt(&ok);
}
void MainWindow::on_E21_textChanged()
{
    bool ok;ui->E21->setStyleSheet("color:black");
    QString valueStr=ui->E21->text();
    num[4][3]= valueStr.toInt(&ok);
}
void MainWindow::on_E22_textChanged()
{
    bool ok;ui->E22->setStyleSheet("color:black");
    QString valueStr=ui->E22->text();
    num[4][4]= valueStr.toInt(&ok);
}
void MainWindow::on_E23_textChanged()
{
    bool ok;ui->E23->setStyleSheet("color:black");
    QString valueStr=ui->E23->text();
    num[4][5]= valueStr.toInt(&ok);
}
void MainWindow::on_E31_textChanged()
{
    bool ok;ui->E31->setStyleSheet("color:black");
    QString valueStr=ui->E31->text();
    num[5][3]= valueStr.toInt(&ok);
}
void MainWindow::on_E32_textChanged()
{
    bool ok;ui->E32->setStyleSheet("color:black");
    QString valueStr=ui->E32->text();
    num[5][4]= valueStr.toInt(&ok);
}
void MainWindow::on_E33_textChanged()
{
    bool ok;ui->E33->setStyleSheet("color:black");
    QString valueStr=ui->E33->text();
    num[5][5]= valueStr.toInt(&ok);
}
void MainWindow::on_F11_textChanged()
{
    bool ok;ui->F11->setStyleSheet("color:black");
    QString valueStr=ui->F11->text();
    num[3][6]= valueStr.toInt(&ok);
}
void MainWindow::on_F12_textChanged()
{
    bool ok;ui->F12->setStyleSheet("color:black");
    QString valueStr=ui->F12->text();
    num[3][7]= valueStr.toInt(&ok);
}
void MainWindow::on_F13_textChanged()
{
    bool ok;ui->F13->setStyleSheet("color:black");
    QString valueStr=ui->F13->text();
    num[3][8]= valueStr.toInt(&ok);
}
void MainWindow::on_F21_textChanged()
{
    bool ok;ui->F21->setStyleSheet("color:black");
    QString valueStr=ui->F21->text();
    num[4][6]= valueStr.toInt(&ok);
}
void MainWindow::on_F22_textChanged()
{
    bool ok;ui->F22->setStyleSheet("color:black");
    QString valueStr=ui->F22->text();
    num[4][7]= valueStr.toInt(&ok);
}
void MainWindow::on_F23_textChanged()
{
    bool ok;ui->F23->setStyleSheet("color:black");
    QString valueStr=ui->F23->text();
    num[4][8]= valueStr.toInt(&ok);
}
void MainWindow::on_F31_textChanged()
{
    bool ok;ui->F31->setStyleSheet("color:black");
    QString valueStr=ui->F31->text();
    num[5][6]= valueStr.toInt(&ok);
}
void MainWindow::on_F32_textChanged()
{
    bool ok;ui->F32->setStyleSheet("color:black");
    QString valueStr=ui->F32->text();
    num[5][7]= valueStr.toInt(&ok);
}
void MainWindow::on_F33_textChanged()
{
    bool ok;ui->F33->setStyleSheet("color:black");
    QString valueStr=ui->F33->text();
    num[5][8]= valueStr.toInt(&ok);
}
void MainWindow::on_G11_textChanged()
{
    bool ok;ui->G11->setStyleSheet("color:black");
    QString valueStr=ui->G11->text();
    num[6][0]= valueStr.toInt(&ok);
}
void MainWindow::on_G12_textChanged()
{
    bool ok;ui->G12->setStyleSheet("color:black");
    QString valueStr=ui->G12->text();
    num[6][1]= valueStr.toInt(&ok);
}
void MainWindow::on_G13_textChanged()
{
    bool ok;ui->G13->setStyleSheet("color:black");
    QString valueStr=ui->G13->text();
    num[6][2]= valueStr.toInt(&ok);
}
void MainWindow::on_G21_textChanged()
{
    bool ok;ui->G21->setStyleSheet("color:black");
    QString valueStr=ui->G21->text();
    num[7][0]= valueStr.toInt(&ok);
}
void MainWindow::on_G22_textChanged()
{
    bool ok;ui->G22->setStyleSheet("color:black");
    QString valueStr=ui->G22->text();
    num[7][1]= valueStr.toInt(&ok);
}
void MainWindow::on_G23_textChanged()
{
    bool ok;ui->G23->setStyleSheet("color:black");
    QString valueStr=ui->G23->text();
    num[7][2]= valueStr.toInt(&ok);
}
void MainWindow::on_G31_textChanged()
{
    bool ok;ui->G31->setStyleSheet("color:black");
    QString valueStr=ui->G31->text();
    num[8][0]= valueStr.toInt(&ok);
}
void MainWindow::on_G32_textChanged()
{
    bool ok;ui->G32->setStyleSheet("color:black");
    QString valueStr=ui->G32->text();
    num[8][1]= valueStr.toInt(&ok);
}
void MainWindow::on_G33_textChanged()
{
    bool ok;ui->G33->setStyleSheet("color:black");
    QString valueStr=ui->G33->text();
    num[8][2]= valueStr.toInt(&ok);
}
void MainWindow::on_H11_textChanged()
{
    bool ok;ui->H11->setStyleSheet("color:black");
    QString valueStr=ui->H11->text();
    num[6][3]= valueStr.toInt(&ok);
}
void MainWindow::on_H12_textChanged()
{
    bool ok;ui->H12->setStyleSheet("color:black");
    QString valueStr=ui->H12->text();
    num[6][4]= valueStr.toInt(&ok);
}
void MainWindow::on_H13_textChanged()
{
    bool ok;ui->H13->setStyleSheet("color:black");
    QString valueStr=ui->H13->text();
    num[6][5]= valueStr.toInt(&ok);
}
void MainWindow::on_H21_textChanged()
{
    bool ok;ui->H21->setStyleSheet("color:black");
    QString valueStr=ui->H21->text();
    num[7][3]= valueStr.toInt(&ok);
}
void MainWindow::on_H22_textChanged()
{
    bool ok;ui->H22->setStyleSheet("color:black");
    QString valueStr=ui->H22->text();
    num[7][4]= valueStr.toInt(&ok);
}
void MainWindow::on_H23_textChanged()
{
    bool ok;ui->H23->setStyleSheet("color:black");
    QString valueStr=ui->H23->text();
    num[7][5]= valueStr.toInt(&ok);
}
void MainWindow::on_H31_textChanged()
{
    bool ok;ui->H31->setStyleSheet("color:black");
    QString valueStr=ui->H31->text();
    num[8][3]= valueStr.toInt(&ok);
}
void MainWindow::on_H32_textChanged()
{
    bool ok;ui->H32->setStyleSheet("color:black");
    QString valueStr=ui->H32->text();
    num[8][4]= valueStr.toInt(&ok);
}
void MainWindow::on_H33_textChanged()
{
    bool ok;ui->H33->setStyleSheet("color:black");
    QString valueStr=ui->H33->text();
    num[8][5]= valueStr.toInt(&ok);
}
void MainWindow::on_I11_textChanged()
{
    bool ok;ui->I11->setStyleSheet("color:black");
    QString valueStr=ui->I11->text();
    num[6][6]= valueStr.toInt(&ok);
}
void MainWindow::on_I12_textChanged()
{
    bool ok;ui->I12->setStyleSheet("color:black");
    QString valueStr=ui->I12->text();
    num[6][7]= valueStr.toInt(&ok);
}
void MainWindow::on_I13_textChanged()
{
    bool ok;ui->I13->setStyleSheet("color:black");
    QString valueStr=ui->I13->text();
    num[6][8]= valueStr.toInt(&ok);
}
void MainWindow::on_I21_textChanged()
{
    bool ok;ui->I21->setStyleSheet("color:black");
    QString valueStr=ui->I21->text();
    num[7][6]= valueStr.toInt(&ok);
}
void MainWindow::on_I22_textChanged()
{
    bool ok;ui->I22->setStyleSheet("color:black");
    QString valueStr=ui->I22->text();
    num[7][7]= valueStr.toInt(&ok);
}
void MainWindow::on_I23_textChanged()
{
    bool ok;ui->I23->setStyleSheet("color:black");
    QString valueStr=ui->I23->text();
    num[7][8]= valueStr.toInt(&ok);
}
void MainWindow::on_I31_textChanged()
{
    bool ok;ui->I31->setStyleSheet("color:black");
    QString valueStr=ui->I31->text();
    num[8][6]= valueStr.toInt(&ok);
}
void MainWindow::on_I32_textChanged()
{
    bool ok;ui->I32->setStyleSheet("color:black");
    QString valueStr=ui->I32->text();
    num[8][7]= valueStr.toInt(&ok);
}
void MainWindow::on_I33_textChanged()
{
    bool ok;ui->I33->setStyleSheet("color:black");
    QString valueStr=ui->I33->text();
    num[8][8]= valueStr.toInt(&ok);
}


