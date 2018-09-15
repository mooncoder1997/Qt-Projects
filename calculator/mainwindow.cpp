#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_pushButton_clicked()
{
    float a,b,c,d;
    a = ui->textEdit->toPlainText().toFloat()+ui->textEdit_2->toPlainText().toFloat();
    b = ui->textEdit->toPlainText().toFloat()-ui->textEdit_2->toPlainText().toFloat();
    c = ui->textEdit->toPlainText().toFloat()*ui->textEdit_2->toPlainText().toFloat();
    d = ui->textEdit->toPlainText().toFloat()/ui->textEdit_2->toPlainText().toFloat();
    ui->textEdit_3->setText(" 和：" + QString::number(a) +
                            ",差：" + QString::number(b) +
                            ",积：" + QString::number(c) +
                            ",商：" + QString::number(d)
                            );
}

void MainWindow::on_pushButton_2_clicked()
{
    w2.show();
}
