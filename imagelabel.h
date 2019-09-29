#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QPen>

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageLabel(QWidget *parent = 0);
    QString getPic() const;
    void setPic(QString value);
    QVector<QPoint> landMarks;
private:
    QString pic;
    bool pictured;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // IMAGELABEL_H
