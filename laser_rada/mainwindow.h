#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QMainWindow>
#include "laser_frame_decoder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


 QSerialPort *serial;
 QByteArray rec_buf;
 int    CRC16(QByteArray buf1);
 QString  data_frames;
  QByteArray data_frames_now;

  laser_frame_decoder my_laser_data;
QImage laser_image;
 QTimer *mytimer;
private:
    Ui::MainWindow *ui;

private slots:
    void timerUpDate();
    void Read_Data();

    void on_open_port_clicked();
    void on_close_port_clicked();
    void on_get_data_inf_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
