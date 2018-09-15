#include "myglwidget.h"
#include <QPainter>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


MyGLWidget::MyGLWidget(QWidget *parent)
        : QOpenGLWidget(parent)
{
    count = 0;
    // 打开文件
    QFile file("config.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);

    // 读取的内容存入数组
    QVector<QString> str_list;
    while (!in.atEnd()) {
        QString line = in.readLine();
        str_list.append(line);
    }

    QStringList line1 = str_list[0].split(",");
    QString frame_cntS = line1[0];
    QString fpsS = line1[1];
    frame_cnt = frame_cntS.toInt();
    int fps = fpsS.toInt();

    for (int i = 1; i < frame_cnt+1; i++)
    {
        QPixmap my_bitmap(800, 600);
        QPainter painter(&my_bitmap);
        QImage image;
        image.load("black.png");
        painter.drawImage(0, 0, image);

        for (int j = 1; j < str_list.length(); j++)
        {
            QStringList setting = str_list[j].split(",");
            QString frame_idS = setting[0];
            int frame_id = frame_idS.toInt();
            QString xS = setting[2];
            QString yS = setting[3];
            int x = xS.toInt();
            int y = yS.toInt();
            if (frame_id == i)
            {
                QImage image(setting[1]);
                painter.drawImage(x, y, image);
            }
        }
        my_bitmap.save("A" + QString::number(i) + ".png");
    }

    for (int i = 1; i <= frame_cnt; i++)
    {
        QImage image("A" + QString::number(i) + ".png");
        image_list.append(image);
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(picture()));
    timer->start(1000 / fps);
}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
    update();
    static QTime time;
    static int frames = 0;
    static bool started = false;

    if (!started || time.elapsed() > 1000) {
        qreal fps = frames * 1000. / time.elapsed();
        if (fps == 0)
            m_current_fps = "counting fps...";
        else
            m_current_fps = QString::fromLatin1("%3 FPS").arg((int) qRound(fps));

        time.start();
        started = true;
        frames = 0;
    } else {
        ++frames;
//        painter.drawText(10,15,m_current_fps);
    }
}

void MyGLWidget::picture()
{
    count += 1;
    if(count > frame_cnt)count=1;
    switch (count) {
        case 1:picName="A1.png";break;
        case 2:picName="A2.png";break;
        case 3:picName="A3.png";break;
        case 4:picName="A4.png";break;
        case 5:picName="A5.png";break;
        case 6:picName="A6.png";break;
    }
    image.load(picName);
    update();
}

