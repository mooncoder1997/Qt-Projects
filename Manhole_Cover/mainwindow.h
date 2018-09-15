#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mqtt/qmqtt.h"
#include "QHostInfo"
#include "QJsonParseError"
#include "QJsonDocument"
#include "QJsonObject"
#include "QMessageBox"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString node1 = "$USR/DevTx/356566075954255";
    QString node2 = "";
    QString node3 = "";

    QString node1_State = "$USR/JsonTx/mooncoder1997/356566075954255";
    QString node2_State = "";
    QString node3_State = "";

private slots:
    void onMQTT_Connected();

    void onMQTT_Subscribed(const QString &topic);

    void onMQTT_Received(const QMQTT::Message &message);

    void onMQTT_Disconnect();

    void on_pushButton_disconnect_clicked();

    void on_pushButton_Reconnect_clicked();

    void on_pushButton_SubAll_clicked();

private:
    Ui::MainWindow *ui;
    QMQTT::Client *client;
};

#endif // MAINWINDOW_H
