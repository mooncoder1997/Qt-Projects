#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mqtt/qmqtt.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onMQTT_Connected();

    void onMQTT_Subscribed(const QString &topic);

    void onMQTT_Received(const QMQTT::Message &message);

    void on_pushButton_sub_clicked();

    void on_pushButton_pub_clicked();

private:
    Ui::MainWindow *ui;
    QMQTT::Client *client;
};

#endif // MAINWINDOW_H
