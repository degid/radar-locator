#ifndef TARGETOBJECT_H
#define TARGETOBJECT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QMouseEvent>

class TargetObject : public QGraphicsItem
{
public:
    TargetObject(QString name);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int phase);

private:
    qreal angle;
    qreal speed;
    QString name;

};

#endif // TARGETOBJECT_H
