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
    QVector<QPoint> oldLandMarks;
    bool getIsEditing() const;
    void setIsEditing(bool value);
    bool getIsLoaded() const;
    void setIsLoaded(bool value);

    bool getIsPictured() const;
    void setIsPictured(bool value);

private:
    QString pic;
    bool isEditing;
    bool isPictured;
    bool isLoaded;
    bool isPointChange;
    int editIndex;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // IMAGELABEL_H
