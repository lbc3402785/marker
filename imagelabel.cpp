#include "imagelabel.h"
#include <QVector>
#include <QDebug>
#include <QToolTip>
#include <iostream>
#define DRAGDIS 5
ImageLabel::ImageLabel(QWidget *parent): QLabel(parent)
{
    pic="";
    isEditing=false;
    editIndex=-1;
    isPointChange=false;
}

QString ImageLabel::getPic() const
{
    return pic;
}

void ImageLabel::setPic(QString value)
{
    pic = value;
}

bool ImageLabel::getIsEditing() const
{
    return isEditing;
}

void ImageLabel::setIsEditing(bool value)
{
    isEditing = value;
    if(isEditing){
        setMouseTracking (true);
        oldLandMarks=landMarks;
    }else{
        setMouseTracking (false);
    }
}

bool ImageLabel::getIsLoaded() const
{
    return isLoaded;
}

void ImageLabel::setIsLoaded(bool value)
{
    isLoaded = value;
}

bool ImageLabel::getIsPictured() const
{
    return isPictured;
}

void ImageLabel::setIsPictured(bool value)
{
    isPictured = value;
}



inline void drawPolyline(QPainter& painters,QVector<QPoint> &v,int start,int end,bool closed=false)
{
    QPolygon ply;   //多边形
    for(int i=start;i<=end;i++)
    {
        ply.append(v[i]);
    }

    if(closed)painters.drawConvexPolygon(ply);  //绘制出多边形
    else painters.drawPolyline(ply);
}
void ImageLabel::paintEvent(QPaintEvent *event)
{
    if(pic.length()>0){
        setPixmap(QPixmap(pic));
    }

    QLabel::paintEvent(event);

//    QPen penNode; //设置点的样式
//    penNode.setColor(Qt::red); //改变颜色
    if(pic.length()>0&&!landMarks.empty()){
        QPainter painters(this);
        QPen penNode; //设置点的样式
        penNode.setColor(Qt::red); //改变颜色
        int nodeWidth=5;
        for(int i=0;i<landMarks.size();i++)
        {
            penNode.setWidth(nodeWidth);  //改变点的宽度
            painters.setPen(penNode);
            painters.drawPoint(landMarks.at (i));
        }
        QPen penLine; //设置线的样式
        penLine.setWidth(2);
        penLine.setColor(Qt::blue);
        painters.setPen(penLine);
        drawPolyline(painters,landMarks,0,16);      // Jaw line
        drawPolyline(painters,landMarks,17, 21);    // Left eyebrow
        drawPolyline(painters,landMarks,22, 26);    // Right eyebrow
        drawPolyline(painters,landMarks,27, 30);    // Nose bridge
        drawPolyline(painters, landMarks, 30, 35, true);    // Lower nose
        drawPolyline(painters, landMarks, 36, 41, true);    // Left eye
        drawPolyline(painters, landMarks, 42, 47, true);    // Right Eye
        drawPolyline(painters, landMarks, 48, 59, true);    // Outer lip
        drawPolyline(painters, landMarks, 60, 67, true);    // Inner lip
    }

}

void ImageLabel::resizeEvent(QResizeEvent *event)
{
   //const QPixmap* pix=this->pixmap();
    if(this->pixmap()){
        qDebug()<<this->pos();

        //std::cout<<pix->rect().left()<<","<<pix->rect().top()<<std::endl;
    }
//    if(pic.length()>0){
//        setPixmap(QPixmap(pic));
//    }
//    this->clear();
    //    this->update(0,0,event->size().width(),event->size().height());
}

void ImageLabel::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos ();
    if(event->button ()==Qt::LeftButton)
    {
        if(isEditing)
        {
            for(int i=0;i<landMarks.length ();i++)
            {
                int disTan = (pos-landMarks.at (i)).manhattanLength ();
                if(disTan<=DRAGDIS)
                {
                    editIndex = i;
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

void ImageLabel::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    editIndex=-1;
    update();
}

void ImageLabel::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos ();
    isPointChange=false;
    if(isEditing)
    {
        if(editIndex!=-1){
            QString zuo=QString("%1 %2").arg(pos.x()).arg(pos.y());
            QToolTip::showText(QPoint(event->globalPos()),zuo,this);
        }else{
            for(int i=0;i<landMarks.length ();i++)
            {
                int disTan = (pos-landMarks.at (i)).manhattanLength ();
                if(disTan<=DRAGDIS)
                {
                    QString zuo=QString("%1 %2").arg(pos.x()).arg(pos.y());
                    QToolTip::showText(QPoint(event->globalPos()),zuo,this);  //显示鼠标坐标  更随鼠标用方框的形式
                    //_isPointChange = true;
                    //editIndex = i;
                }
            }
        }

        if(isPointChange)
        {
            setCursor (Qt::PointingHandCursor);
            update();  //刷新
        }
        else
        {
            setCursor(Qt::ArrowCursor);
            update();
        }
        if(editIndex!=-1)
        {
            //改变点的位置
            QPoint& changPos = landMarks[editIndex];
            changPos.rx ()= event->pos().x();
            changPos.ry() = event->pos().y();
            update();
        }
    }
}
