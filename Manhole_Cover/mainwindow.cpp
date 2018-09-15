#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 通过域名获取ip
    QString yuming ="clouddata.usr.cn";
    QHostInfo info = QHostInfo::fromName(yuming);
    QString ip;
    foreach (QHostAddress address, info.addresses()) {
        if (address.protocol()==QAbstractSocket::IPv4Protocol) {
            ip = address.toString();
            }
    }

    // 连接到透传云MQTT服务器
    client = new QMQTT::Client(QHostAddress(ip), 1883);
    client->setClientId("APP:mooncoder1997");
    client->setKeepAlive(600);
    client->setCleanSession(true);
    client->setUsername("mooncoder1997");
    client->setPassword("771ac8f98cec26f9e39957bde110ba44");
    client->connectToHost();

    // MQTT槽函数
    connect(client, SIGNAL(connected()), this, SLOT(onMQTT_Connected()));
    connect(client, SIGNAL(subscribed(const QString &)), this, SLOT(onMQTT_Subscribed(QString)));
    connect(client, SIGNAL(received(const QMQTT::Message &)), this, SLOT(onMQTT_Received(QMQTT::Message)));
    connect(client, SIGNAL(disconnected()), this, SLOT(onMQTT_Disconnect()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 连接成功 槽函数
void MainWindow::onMQTT_Connected()
{
    ui->label_state->setText("服务器通讯状态 -> 成功建立连接！！！");
    ui->plainTextEdit_state->appendPlainText("成功连接到MQTT服务器！！！");
}

// 订阅成功 槽函数
void MainWindow::onMQTT_Subscribed(const QString &topic)
{
    if (topic == node1) {
        ui->plainTextEdit_state->appendPlainText("已订阅 -> 节点1");
    }
}

// 消息到来 槽函数
void MainWindow::onMQTT_Received(const QMQTT::Message &message)
{
    // 节点1
    if (message.topic() == node1) {
        ui->plainTextEdit_data->appendPlainText("节点1 -> " + message.payload());
    }

    // 节点2
    if (message.topic() == node2) {
        ui->plainTextEdit_data->appendPlainText("节点2 -> " + message.payload());
    }

    // 节点3
    if (message.topic() == node3) {
        ui->plainTextEdit_data->appendPlainText("节点3 -> " + message.payload());
    }

    /*
    if (message.topic() == node1_State) {
        QString Jnode1_State = message.payload();
        QByteArray a = Jnode1_State.toLatin1();
        QJsonParseError jsonError;
        QJsonDocument json = QJsonDocument::fromJson(a, &jsonError);
        if (jsonError.error == QJsonParseError::NoError) {
            if (json.isObject()) {
                QJsonObject rootObj = json.object();
                QJsonValue JdevStatus = rootObj.value("devStatus");
                QString devStatus = JdevStatus.toString();
                QMessageBox::about(this, "x", devStatus);
            }
        }
    }
    */
}

// 断开连接 槽函数
void MainWindow::onMQTT_Disconnect()
{
    ui->label_state->setText("服务器通讯状态 -> 已断开连接！！！");
    ui->plainTextEdit_state->appendPlainText("已断开连接，重连请点击“重新连接”按钮！！！");
}

// 断开连接 按钮
void MainWindow::on_pushButton_disconnect_clicked()
{
    client->disconnectFromHost();
}

// 重新连接 按钮
void MainWindow::on_pushButton_Reconnect_clicked()
{
    client->connectToHost();
}

// 自动连接所有节点 按钮
void MainWindow::on_pushButton_SubAll_clicked()
{
    // 订阅设备数据
    client->subscribe(node1, 0);

    // 订阅设备上下线状态
//    client->subscribe("$USR/JsonTx/mooncoder1997/+", 0);
}
