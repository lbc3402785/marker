#include "imagelabel.h"
#include <QVector>
#include <QDebug>
ImageLabel::ImageLabel(QWidget *parent): QLabel(parent)
{
    pic="";
    pictured=false;
}

QString ImageLabel::getPic() const
{
    return pic;
}

void ImageLabel::setPic(QString value)
{
    pic = value;
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
    QLabel::paintEvent(event);

//    QPen penNode; //设置点的样式
//    penNode.setColor(Qt::red); //改变颜色
    if(!landMarks.empty()){
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
