#ifndef DISPLAYSCENE_H
#define DISPLAYSCENE_H

#include <QObject>
#include <QGraphicsScene>

#include <QDebug>

class DisplayScene : public QGraphicsScene
{
public:
    DisplayScene(QObject *parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
};

#endif // DISPLAYSCENE_H
