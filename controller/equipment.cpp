#include "equipment.h"

Equipment::Equipment(QString title, GraphWidget *graphWidget)
    : title(title)
{

}

Equipment::~Equipment()
{
    node = nullptr;
}

QRectF Equipment::boundingRect() const
{
    return QRectF(0, 0, 100, 20);
}

void Equipment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush Brush(Qt::lightGray);
    if(status){
        Brush.setColor(Qt::red);
    }// else {
    //    Brush.setColor(Qt::green);
    //}

    painter->fillRect(rec, Brush);
    painter->drawRect(rec);

    painter->setFont(QFont("consolas", 10, QFont::Normal));
    painter->drawText(10, 15, title);

}

void Equipment::setNode(QSharedPointer<Node> _node)
{
    node = _node;
}

void Equipment::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

//    QMap<QString, QSharedPointer<Node>>::Iterator it;
//    for(it = node->_node.begin(); it != node->_node.end(); it++){
//        qDebug() << it.key() << "EVENT MAP";
//    }

    emit buttonPress(node);

}

void Equipment::setPosition(int numPos=0)
{
    QPoint pos = QPoint(10, 13 + (20 * numPos * 1.5));
    setPos(pos);
}
