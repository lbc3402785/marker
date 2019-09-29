#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QPen>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
    bool _isEditing;

    enum MOUSESTYLE {ArrowCursor=0,CrossCursor};


protected:
    void mousePressEvent (QMouseEvent *);
    void mouseReleaseEvent (QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);

    void paintEvent (QPaintEvent *);

private:
    void Init();
    QVector<QPoint> _Line;
    MOUSESTYLE _mouseStyle;
    int _changeIndex;
    bool _isPointChange;

signals:

private slots:
};

#endif // MYLABEL_H
