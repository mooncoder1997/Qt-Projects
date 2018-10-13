#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include <QProcess>
#include "laser_frame_decoder.h"



#include <QtGui/QPixmap>
#include <QtGui/QPainter>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     serial = new QSerialPort;
    mytimer = new QTimer( );//新建定时器
     connect(mytimer,SIGNAL(timeout()),this,SLOT(timerUpDate()));//关联定时器计满信号和相应的槽函数

data_frames="";
    // rec_buf=new QByteArray("");

















}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::timerUpDate()

{

QDateTime time = QDateTime::currentDateTime();

QDateTime dateTime = QDateTime::currentDateTime();
 dateTime.setTimeSpec(Qt::LocalTime);
 uint secondsLocal= dateTime.toTime_t()+8*3600;  //secondsLocal =0;
 dateTime.setTimeSpec(Qt::UTC);
 uint secondsUTC = dateTime.toTime_t();   //secondsUTC = 28800;8小时

   dateTime = QDateTime::fromTime_t(secondsLocal);;
 QString sUTCTime = dateTime.toString("yyyy-MM-dd hh:mm:ss");
 this->setWindowTitle(sUTCTime);
 //ui->time_lab->setText(sUTCTime);

ui->data_frame->setText(data_frames);



///////////////////////////////display laser data
///

QString str_tmp="";

int width=1000;
int height=1000;
uchar* data24 = new uchar[ width * height*3];
  laser_image = QImage(data24, width, height, QImage::Format_RGB888); //封装QImage

for (int i=0;i<  width * height*3;i++)
{
  data24[i]=100;
}
QPainter painter;//注意不要加入(this)，this指针直接在mainwindow绘图

painter.begin(&laser_image);//这句话把图像和绘图结合起来了。
QPen pen(Qt::yellow);
painter.setPen(pen);
painter.drawRect(500-10,500-10,10,10);

pen.setColor(Qt::green);
painter.setPen(pen);


for(int i=9;i<400;i++)
{

  float xita=(i/my_laser_data.data_n)*22.5+(i%my_laser_data.data_n)*(22.5/my_laser_data.data_n);
  xita=(2*3.1415926*xita)/360;
  float r=500;
  r=my_laser_data.distance[i]*0.01;
  int x=r*cos(xita) ;
  int y=r*sin(xita) ;
painter.drawPoint(x+500,y+500);

 str_tmp=str_tmp+"\t"+QString::number(i, 'f', 0)+"="+QString::number(my_laser_data.distance[i], 'f', 0);
}

ui->all_data->setText(str_tmp);




   painter.end();

   QImage newImg = laser_image.scaled(ui->label->width(), ui->label->height());//image是老图像。newImg是缩放后的新图像。
   ui->label->setPixmap(QPixmap::fromImage(newImg));



//在标签上显示时间

}

//=============================================================================
// 校验码计算
// *Start_Byte：开始字节
// Num_Bytes：被计算数据的长度
// 返回值： 16位的校验码
//=============================================================================
int   MainWindow::CRC16(QByteArray buf1)
{
    int Checksum = 0;
   int Num_Bytes= buf1.length()-2;
    while (Num_Bytes--)
    {	// 计算CRC
        Checksum += (unsigned int)(buf1[Num_Bytes])&0x00ff;
    }
    return Checksum&0x00ffff;
}








void MainWindow::Read_Data()
{
    QByteArray buf;
    buf = serial->readAll();




    if(!buf.isEmpty())
    {
         rec_buf.append(buf);
       // ui->rec_str->setText(rec_buf.toHex(' '));
    /////////////////////////
        //deal rec_buf
        int index_aa=rec_buf.indexOf(0xaa);
        int dat_0x61=0;
        int   c1=rec_buf[index_aa+3]&0x00ff;
        int    c2=rec_buf[index_aa+4]&0x00ff;
        int    c3=rec_buf[index_aa+5]&0x00ff;
        if(index_aa!=-1)
        {




          c1=c1;
            if(
               c2==0x61&&
               c3==0xad
                    )
            {
                int frame_len=rec_buf.at(index_aa+1)*256
                        +rec_buf.at(index_aa+2);
                if(rec_buf.length()>(index_aa+frame_len+2))
                {
                 QByteArray buf1=rec_buf.mid(index_aa,frame_len+2);

                unsigned int check_1=CRC16(buf1);
                unsigned int check_2=(unsigned int)buf1.at(frame_len)&0x00ff;

                check_2=check_2*256;
                check_2=check_2+(unsigned int)buf1.at(frame_len+1)&0x00ff;
      //          if(check_1==check_2)
                {
                  unsigned int tmp= (unsigned int)(buf1.at(frame_len+1))&0x00ff;

                  check_2=check_2+tmp;
                  ui->rec_str->setText(buf1.toHex(' '));
                  QString str_tmp;
                  str_tmp=str_tmp.number(buf1.length());
                  data_frames=data_frames+buf1.toHex(' ')+"("+str_tmp +")"+"\r\n";
                  rec_buf=rec_buf.mid(index_aa+frame_len+2);
                  data_frames_now=buf1;



                  my_laser_data.decoder_data( data_frames_now);
                  QString myinf="";
                     str_tmp="";
                  myinf=myinf.number(my_laser_data.data_n);
                  myinf=myinf+ "  index="+str_tmp.number(my_laser_data.data_index);

                  myinf=myinf+ "  start_angle="+str_tmp.number(my_laser_data.start_angle*0.01);
                  myinf=myinf+ "  angle_offset="+str_tmp.number(my_laser_data.angle_offset*0.01);
                  myinf=myinf+ "  angle ="+str_tmp.number((my_laser_data.start_angle+my_laser_data.angle_offset)*0.01);

                  ui->rec_str_2->append(myinf);







                  }//  check1 ==check2


                }

            }
            else
            {
                rec_buf=rec_buf.mid(index_aa+1);

            }

        }
        //else
        //{
          //   ui->rec_str->setText(rec_buf.toHex(' '));
       // }





    }


}

void MainWindow::on_open_port_clicked()
{
    serial->close();

   //设置串口名
   serial->setPortName(ui->port_name->toPlainText());
   //打开串口
   serial->open(QIODevice::ReadWrite);
   //设置波特率
   serial->setBaudRate(230400);
   //设置数据位数
   serial->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    serial->setParity(QSerialPort::NoParity);
   //设置停止位
   serial->setStopBits(QSerialPort::OneStop);
   //设置流控制
   serial->setFlowControl(QSerialPort::NoFlowControl);

   QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::Read_Data);
}

void MainWindow::on_close_port_clicked()
{
    serial->close();
}

void MainWindow::on_get_data_inf_clicked()
{
    laser_frame_decoder  aa;
    aa.decoder_data( data_frames_now);
    QString myinf="";
     QString tmp="";
    myinf=myinf.number(aa.data_n);
    myinf=myinf+ "\r\nangle_offset="+tmp.number(aa.angle_offset);

    for(int i=0;i<aa.data_n;i++)
    {
          myinf=myinf+"\tangle=\t"+tmp.number(((i)*22.5)/(i+1)+aa.angle_offset);
          myinf=myinf+"\r\ndis=\t"+tmp.number(aa.distance[i]);

          myinf=myinf+"\r\n";
    }

  //  QString myinf=aa.print_inf();
    ui->rec_str_2->setText(myinf);

}

void MainWindow::on_pushButton_clicked()
{
    mytimer->start(200);
}
