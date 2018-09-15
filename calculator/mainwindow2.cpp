#include "mainwindow2.h"
#include "ui_mainwindow2.h"

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    first = 0;
    second = 0;
    result = 0;
    flag1 = 0;
    b = 1;
}

MainWindow2::~MainWindow2()
{
    delete ui;
}
// 1
void MainWindow2::on_pushButton_clicked()
{
    str += ui->pushButton->text();
    temp = str.toFloat();
    ui->lineEdit->setText(QString::number(temp));
}
// 2
void MainWindow2::on_pushButton_2_clicked()
{
    str += ui->pushButton_2->text();
    temp = str.toFloat();
    ui->lineEdit->setText(QString::number(temp));
}
// 3
void MainWindow2::on_pushButton_3_clicked()
{
    str += ui->pushButton_3->text();
    temp = str.toFloat();
    ui->lineEdit->setText(QString::number(temp));
}
// .
void MainWindow2::on_pushButton_4_clicked()
{
    str += ui->pushButton_4->text();
    temp = str.toFloat();
    ui->lineEdit->setText(QString::number(temp));
}
// +
void MainWindow2::on_pushButton_5_clicked()
{
    flag = '+';
    if(flag1 == 0)
    {
        first = temp;
        temp = 0;
    }
    str = "";
    ui->lineEdit_2->insert(ui->lineEdit->text() + "+");
}
// 4
void MainWindow2::on_pushButton_10_clicked()
{
    str += ui->pushButton_10->text();
    temp = str.toFloat();
    ui->lineEdit->setText(QString::number(temp));
}
// 5
void MainWindow2::on_pushButton_8_clicked()
{
    str += ui->pushButton_8->text();
    temp = str.toFloat();
    ui->lineEdit->setText(QString::number(temp));
}
// 6
void MainWindow2::on_pushButton_7_clicked()
{
    str += ui->pushButton_7->text();
    temp = str.toFloat();
    ui->lineEdit->setText(QString::number(temp));
}
// ln
void MainWindow2::on_pushButton_9_clicked()
{
    flag = 'l';
    if(flag1 == 0)
    {
        first = temp;
        temp = 0;
    }
    str = "";
    ui->lineEdit_2->insert("ln");
}
// -
void MainWindow2::on_pushButton_6_clicked()
{
    flag = '-';
    if(flag1 == 0)
    {
        first = temp;
        temp = 0;
    }
    str = "";
    ui->lineEdit_2->insert(ui->lineEdit->text() + "-");
}
// 7
void MainWindow2::on_pushButton_15_clicked()
{
    str += ui->pushButton_15->text();
    temp = str.toFloat();
    ui->lineEdit->setText(QString::number(temp));
}
// 8
void MainWindow2::on_pushButton_13_clicked()
{
    str += ui->pushButton_13->text();
    temp = str.toFloat();
    ui->lineEdit->setText(QString::number(temp));
}
// 9
void MainWindow2::on_pushButton_12_clicked()
{
    str += ui->pushButton_12->text();
    temp = str.toFloat();
    ui->lineEdit->setText(QString::number(temp));
}
// genhao
void MainWindow2::on_pushButton_14_clicked()
{
    ui->lineEdit_2->insert(ui->lineEdit->text() + "√");
}
// *
void MainWindow2::on_pushButton_11_clicked()
{
    flag = '*';
    if(flag1 == 0)
    {
        first = temp;
        temp = 0;
    }
    str = "";
    ui->lineEdit_2->insert(ui->lineEdit->text() + "*");
}
// 0
void MainWindow2::on_pushButton_20_clicked()
{
    str += ui->pushButton_20->text();
    temp = str.toFloat();
    ui->lineEdit->setText(QString::number(temp));
}
// sin
void MainWindow2::on_pushButton_18_clicked()
{
    flag = 's';
    if(flag1 == 0)
    {
        first = temp;
        temp = 0;
    }
    str = "";
    ui->lineEdit_2->insert("sin");
}
// cos
void MainWindow2::on_pushButton_17_clicked()
{
    flag = 'c';
    if(flag1 == 0)
    {
        first = temp;
        temp = 0;
    }
    str = "";
    ui->lineEdit_2->insert("cos");
}
// ^
void MainWindow2::on_pushButton_19_clicked()
{
    flag = '^';
    if(flag1 == 0)
    {
        first = temp;
        temp = 0;
    }
    str = "";
    ui->lineEdit_2->insert(ui->lineEdit->text() + "^");
}
// /
void MainWindow2::on_pushButton_16_clicked()
{
    flag = '/';
    if(flag1 == 0)
    {
        first = temp;
        temp = 0;
    }
    str = "";
    ui->lineEdit_2->insert(ui->lineEdit->text() + "/");
}
// tan
void MainWindow2::on_pushButton_25_clicked()
{
    flag = 't';
    if(flag1 == 0)
    {
        first = temp;
        temp = 0;
    }
    str = "";
    ui->lineEdit_2->insert("tan");
}
// cot
void MainWindow2::on_pushButton_23_clicked()
{
    flag = 'o';
    if(flag1 == 0)
    {
        first = temp;
        temp = 0;
    }
    str = "";
    ui->lineEdit_2->insert("cot");
}
// =
void MainWindow2::on_pushButton_22_clicked()
{
    ui->lineEdit_2->insert(ui->lineEdit->text() + "=");
    second = temp;
    switch (flag) {
    case '+':result = first + second;
        break;
    case '-':result = first - second;
        break;
    case '*':result = first * second;
        break;
    case '/':result = first / second;
        break;
    case 's':result = sin(first*(Pi/180));
        break;
    case 'c':result = cos(first*(Pi/180));
        break;
    case 't':result = tan(first*(Pi/180));
        break;
    case '0':result = 1/(first*(Pi/180));
        break;
    case 'l':result = log(first);
        break;
    case '^':
        for (int i = 0;i < second;i++)
            b *= first;
        result = b;
        break;
    }
    ui->lineEdit->setText(QString::number(result));
    first = result;
    flag1 = 1;
    temp = 0;
    b = 1;
    ui->lineEdit_2->insert(QString::number(result));
}
// 清零
void MainWindow2::on_pushButton_21_clicked()
{
    first = 0;
    second = 0;
    result = 0;
    temp = 0;
    flag1 = 0;
    str = "";
    ui->lineEdit->setText(QString::number(result));
    ui->lineEdit_2->setText("");
}
