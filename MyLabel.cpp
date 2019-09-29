#include "MyLabel.h"
#include <QToolTip>
#include <QDebug>

#define DRAGDIS 5

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    setMouseTracking (true);
    Init ();
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    QPoint pos = ev->pos ();
    if(ev->button ()==Qt::LeftButton)
    {
        if(_isEditing)
        {
            for(int i=0;i<_Line.length ();i++)
            {
                int disTan = (pos-_Line.at (i)).manhattanLength ();
                if(disTan<=DRAGDIS)
                {
                    _changeIndex = i;
                    _mouseStyle = CrossCursor;
                    setCursor (Qt::CrossCursor);
                    break;
                }
            }
        }
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void MyLabel::mouseReleaseEvent(QMouseEvent *)
{
    _mouseStyle = ArrowCursor;
    setCursor(Qt::ArrowCursor);
    update();
}

void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos ();
    qDebug()<<pos;
    _isPointChange=false;  //还应该在这在给m 赋一次值 为了清空鼠标上一次在某个点上留下的值

    if(_isEditing)
    {
        for(int i=0;i<_Line.length ();i++)
        {
            int disTan = (pos-_Line.at (i)).manhattanLength ();
            if(disTan<=DRAGDIS)
            {
                QString zuo=QString("%1 %2").arg(pos.x()).arg(pos.y());
                QToolTip::showText(QPoint(event->globalPos()),zuo,this);  //显示鼠标坐标  更随鼠标用方框的形式
                _isPointChange = true;
                _changeIndex = i;
            }
        }
        if(_isPointChange)
        {
            setCursor (Qt::PointingHandCursor);
            update();  //刷新
        }
        else
        {
            setCursor(Qt::ArrowCursor);
            update();
        }
        if(_mouseStyle==CrossCursor)
        {
            //改变点的位置
            QPoint& changPos = _Line[_changeIndex];
            changPos.rx ()= event->pos().x();
            changPos.ry() = event->pos().y();
            update();
        }
    }
}


void MyLabel::paintEvent(QPaintEvent *)
{

        QPainter painters(this);
        QPen penNode; //设置点的样式
        penNode.setColor(Qt::red); //改变颜色
        int nodeWidth;
        for(int i=0;i<_Line.count ();i++)
        {
            if(_isPointChange && i == _changeIndex)
                nodeWidth = 10;
            else
                nodeWidth = 5;
            penNode.setWidth(nodeWidth);  //改变点的宽度
            painters.setPen(penNode);
            painters.drawPoint(_Line.at (i));
        }
        QPen penLine; //设置线的样式
        penLine.setWidth(2);
        penLine.setColor(Qt::blue);
        painters.setPen(penLine);
        QPolygon ply;   //多边形
        ply.append (_Line);
        painters.drawConvexPolygon(ply);  //绘制出多边形
}

void MyLabel::Init()
{

    _isEditing = false;
    _isPointChange = false;
    _mouseStyle = ArrowCursor;
    _changeIndex = 0;
    _Line.append (QPoint(17,150));
    _Line.append (QPoint(89,93));
    _Line.append (QPoint(199,49));
    _Line.append (QPoint(277,127));
    _Line.append (QPoint(100,300));

}
