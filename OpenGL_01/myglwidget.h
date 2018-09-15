#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include <QOpenGLWidget>
#include <QTimer>
#include "QLabel"

class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    MyGLWidget(QWidget *parent);
    ~MyGLWidget();

    QVector<QImage> image_list;

    int frame_cnt;

    QTimer *timer;
    int count;
//    QPixmap pix;
    QImage image;
    QString picName;
    QString m_current_fps;

    void paintEvent(QPaintEvent *e);

private slots:
    void picture();
};

#endif // MYGLWIDGET_H
