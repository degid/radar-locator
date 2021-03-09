#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QPainter>
#include <QSharedPointer>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsItem>
#include <QObject>

#include <QDebug>

class GraphWidget;
struct Node;

class Equipment : public QObject, public QGraphicsItem
{
Q_OBJECT
public:
    Equipment(QString title, GraphWidget *graphWidget);
    ~Equipment();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setPosition(int);
    void setNode(QSharedPointer<Node> _node);
    void setStatus(bool _status) {status = _status;};
    bool getStatus() {return status;};
    QString getTitle(){return title;};

signals:
    void buttonPress(QSharedPointer<Node> node);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QString title;
    QWeakPointer<Node> node;
    bool status = false;
};

struct Node
{
    Node();
    Node(QString title, QSharedPointer<Node> parent);
    ~Node();

    Equipment *equipTmp;
    QSharedPointer<Node> parent;
    QString title;
    bool status;
    QMap<QString, QSharedPointer<Node>> nodes;

};

#endif // EQUIPMENT_H
