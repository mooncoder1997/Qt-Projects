## 一、树莓派安装Qt
1. 使用win32DiskImager烧写TF卡映像
2. 在命令终端执行
```
sudo apt-get update
```
3. 在命令终端执行（如果需等待时间过长，可先Ctrl + C跳过此步骤，如后续安装失败再执行此步骤）
```
sudo rpi-update
```
4. 安装Qt5-Default
```
sudo apt-get install qt5-default
```
5. 安装Qt Creator
```
sudo apt-get install qtcreator
```

## 二、配置环境
安装好qt5-default和qtcreator后，在Programming中可打开Qt Creator。点击Tool -> External -> configure，在左侧菜单栏点击Build & Run -> Compilers，点击Add -> GCC -> C++，在Compiler path中选择gcc所在目录。
![编译器配置.jpg](https://upload-images.jianshu.io/upload_images/9969251-12aaa22c796f43f8.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
然后在Kits中，选择GCC编译器。
![Kits.jpg](https://upload-images.jianshu.io/upload_images/9969251-f7cedc06cca33dd5.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 三、连接LED灯
![树莓派引脚对照表.png](https://upload-images.jianshu.io/upload_images/9969251-b52be2d777b15005.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
我们使用wiringPi驱动库来作为控制树莓派GPIO的驱动，wiringPi的GPIO编码顺序如图所示，本次我们使用wiringPi 0也就是GPIO.0 这个引脚，将LED的正极引脚皆在GPIO.0上，将LED的负极引脚接在GND上。

## 四、Qt工程
新建Qt工程，在.pro文件最后一行加入wiringPi驱动库的引用
```
LIBS += -lwiringPi
```
加入wiringPi驱动的头文件
```
#include "wiringPi.h"
```
在连接LED时，我们选择编号为0的引脚作为输出，所以我们首先要初始化改IO口，设置其为输出模式。
```
MainWindow::MainWindow(QWidget *parent) : 
    QMainWindos(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wiringPiSetup();
    pinMode(0, OUTPUT);
}
```
初始化改IO口之后，就可以对它进行操作输出高低电平。在mainwindow.ui中放置两个Push Button控件，分别右键点击Go to slot -> clicked()
![ui.jpg](https://upload-images.jianshu.io/upload_images/9969251-c8765225d7634cc4.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
在LED ON按钮的槽函数中，我们需要使该IO口输出高电平，从而点亮LED灯，在LED OFF按钮的槽函数中，使该IO口输出低电平，熄灭LED灯。
```
// LED ON按钮，点击后IO口输出高电平，点亮LED
void MainWindow::on_pushButton_ledon_clicked()
{
    digitalWrite(0, HIGH);
}

// LED OFF按钮，点击后IO口输出高电平，熄灭LED
void MainWindow::on)pushButton_ledoff_clicked()
{
    digitalWrite(0, LOW);
}
```


