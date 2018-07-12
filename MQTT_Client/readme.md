### 一、MQTT协议简介
MQTT消息报文的方式包括connect, disconnect, subscribe, unsubscribe, publish等（类似于HTTP请求行的方法字段）。MQTT的消息模型为publish-subscribe （发布-订阅模式），接收者(subscriber)向中介(broker)提交订阅自己感兴趣的内容，发送者(broker)把消息发送给中介，再由中介发送给订阅者。这种模式这种通信模式的好处是接收者和发送者轻耦合，双方都只需与中介打交道，不需要关心另一方是谁和在哪里，并且方便接收者、发送者数量的增加和减少，很适用于分布式环境中。
其典型模式如图所示：
![MQTT协议说明图.png](https://upload-images.jianshu.io/upload_images/9969251-959ce1a6081bbd07.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 二、环境说明
 - Windows 10 x64
 - Qt 5.11.1
 - MinGW_32bit

### 三、编译MQTT源码
目前Qt5.11中已经提供了类似TCP或者UDP的MQTT类，但是想要在低于此版本的Qt中使用MQTT协议，就需要自行编译开源MQTT消息服务EMQTT为Qt提供的QMQTT源码。
1.下载qmqtt源码
[qmqtt下载地址](http://github.com/emqtt/qmqtt)
```
git clone https://github.com/emqtt/qmqtt
```

 2.编译qmqtt源码
下载qmqtt源码后，直接点击qmqtt文件夹下的Qt工程文件，右键点击工程 -> 构建，编译中如图两个警告可暂时忽略。
![编译MQTT源码.png](https://upload-images.jianshu.io/upload_images/9969251-dc3eca3927a5c8c1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

3.编译完成后会生成一个Debug目录，如下图所示：
![编译输出目录.png](https://upload-images.jianshu.io/upload_images/9969251-8917b793c3c9124b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

4.新建一个工程，打开该工程的目录文件夹，将上一步Debug目录下的“include“文件夹、”lib“文件夹复制到新建的工程目录，将qmqtt源码文件夹下”src/mqtt“文件夹复制到新建的工程目录。新建的工程文件夹如下图所示：
![新建工程目录.png](https://upload-images.jianshu.io/upload_images/9969251-6830b146df7bbe2d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

5.工程配置
在Qt中打开新建的工程，在.pro文件中加入
```
QT += network
```
右键点击工程 -> 添加库，选择外部库
![选择外部库.png](https://upload-images.jianshu.io/upload_images/9969251-482edd47986f6816.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

点击下一步，点击“浏览”，定位到工程目录下的lib文件夹
![lib文件夹.png](https://upload-images.jianshu.io/upload_images/9969251-7a7daf20952e43aa.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

选择.a文件
![添加外部库.png](https://upload-images.jianshu.io/upload_images/9969251-e67e4bb6d224e359.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![汇总.png](https://upload-images.jianshu.io/upload_images/9969251-4350eea7346a8194.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

将lib目录下的两个.a文件均以此方式添加为外部库。

在mainwindow.h中加入头文件引用
```
#include "mqtt/qmqtt.h"
```
编译工程，编译中会有报错提示，定位到错误位置，错误为两处头文件的引用，将两处#include <qmqtt_global.h>均改为#include "qmqtt_global.h"即可成功编译。
6.编写MQTT客户端
在mainwindow.h中定义MQTT事件的槽函数：
```
// 槽函数定义
private slots:
    void onMQTT_Connected();
    void onMQTT_Subscribed(const QString &topic);
    void onMQTT_Received(const QMQTT::Message &message);
```
新建MQTT客户端并连接槽函数：
```
QMQTT::Client *client;
client = new QMQTT::Client(QHostAddress("127.0.0.1"), 1883);
client->connectToHost();
connect(client, SIGNAL(connected()), this, SLOT(onMQTT_Connected()));
connect(client, SIGNAL(subscribed(const QString &)), this, SLOT(onMQTT_Subscribed(QString)));
connect(client, SIGNAL(received(const QMQTT::Message &)), this, SLOT(onMQTT_Received(QMQTT::Message)));
```
MQTT槽函数的实现：
```
// 成功连接到MQTT服务器
void MainWindow::onMQTT_Connected(){}
// 成功订阅主题
void MainWindow::onMQTT_Subscribed(const QString &topic)
{
    ui->plainTextEdit->appendPlainText(topic);
}
// 接收到消息
void MainWindow::onMQTT_Received(const QMQTT::Message &message)
{
    ui->plainTextEdit->appendPlainText(message.topic());
    ui->plainTextEdit->appendPlainText(message.payload());
}
```
订阅主题：
```
QString topicSub = "test";
quint8 qosSub = 0;
client->subscribe(topicSub, qosSub);
```
发布主题：
```
QString topicPub = "test";
QString messagePub = "123";
QMQTT::Message msg(0, topicPub.toLatin1(), messagePub.toLatin1());
client->publish(msg);
```
7.MQTT客户端测试
![MQTT测试.png](https://upload-images.jianshu.io/upload_images/9969251-6f4482fa5a0f4bc8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

[点击下载该工程代码](https://github.com/mooncoder1997/Qt-Projects/tree/master/MQTT_Client)