#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new QMQTT::Client(QHostAddress("47.93.187.183"), 1883);
    client->connectToHost();
    connect(client, SIGNAL(connected()), this, SLOT(onMQTT_Connected()));
    connect(client, SIGNAL(subscribed(const QString &)), this, SLOT(onMQTT_Subscribed(QString)));
    connect(client, SIGNAL(received(const QMQTT::Message &)), this, SLOT(onMQTT_Received(QMQTT::Message)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMQTT_Connected()
{
    ui->label_state->setText("连接状态 -> 连接成功！！！");
    ui->plainTextEdit->appendPlainText("连接成功！！！");
}

void MainWindow::onMQTT_Subscribed(const QString &topic)
{
    ui->plainTextEdit->appendPlainText("已订阅 -> " + topic);
}

void MainWindow::onMQTT_Received(const QMQTT::Message &message)
{
    ui->plainTextEdit->appendPlainText("主题: " + message.topic());
    ui->plainTextEdit->appendPlainText("消息: " + message.payload());
}

// 订阅按钮槽函数
void MainWindow::on_pushButton_sub_clicked()
{
    QString topicSub = ui->lineEdit_topicSub->text();
    quint8 qosSub = ui->comboBox_qosSub->currentIndex();
    client->subscribe(topicSub, qosSub);
}

// 发布按钮槽函数
void MainWindow::on_pushButton_pub_clicked()
{
    QString topicPub = ui->lineEdit_topicPub->text();
    QString messagePub = ui->lineEdit_mes->text();
    QMQTT::Message msg(0, topicPub.toLatin1(), messagePub.toLatin1());
    client->publish(msg);
}
