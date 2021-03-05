#include "targetobject.h"
#include <QDebug>

TargetObject::TargetObject(QString name): name(name)
{
    speed = QRandomGenerator::global()->generate() % 5 + 2;
    angle = QRandomGenerator::global()->generate() % 360;

    setRotation(angle);

    int StartX = 0;
    int StartY = 0;

    StartX = QRandomGenerator::global()->generate() % 300;
    StartY = QRandomGenerator::global()->generate() % 300;

    setPos(mapToParent(StartX, StartY));
}

QRectF TargetObject::boundingRect() const
{
    return QRectF(0, 0, 7, 7);
}

void TargetObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();

//    QPointF endLine = QPointF(rec.center().rx(), -30);
//    QLineF tail = QLineF(rec.center(), endLine);

    QPen greenPen = QPen(Qt::green);
    greenPen.setCosmetic(true);

    painter->setPen(greenPen);

// трекинг
//    painter->drawLine(tail);
//    painter->drawRect(rec);
//    //setTransformOriginPoint(rec.center().rx(), rec.center().ry());
//    painter->setPen(QPen(Qt::blue));


    painter->rotate(-angle);
    painter->drawRect(rec);

    QLineF footnote = QLineF(rec.center().rx(), rec.center().rx(), 25, 25);
    painter->drawLine(footnote);
    painter->setFont(QFont("consolas", 10, QFont::Normal));
    painter->drawText(22, 35, name);



// трекинг
    //painter->drawLine(tail);

//    painter->setPen(QPen(Qt::red));
//    painter->translate(rec.width(), 0);
//    painter->rotate(-angle);
//    painter->drawLine(tail);
}

void TargetObject::advance(int phase)
{
    setPos(mapToParent(0, speed));
    update();
}
