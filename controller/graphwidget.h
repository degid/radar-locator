#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QDir>
#include <QGraphicsView>
#include <QXmlStreamReader>
#include <QSignalMapper>

#include "equipment.h"

#include <QDebug>

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);


private slots:
    void changeLevelNext(QSharedPointer<Node>);
    void changeLevelPrev(QSharedPointer<Node>);
    void setStatus(QSharedPointer<Node>);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QGraphicsScene *scene;
    QSignalMapper *mapper;
    QSharedPointer<Node> node;
    void addNode(QMap<QString, QSharedPointer<Node>> *map,
                 const QString name,
                 bool isTree,
                 QSharedPointer<Node> parent);
    void readXML(const QString fileName);
    void changeLevel(QSharedPointer<Node> *);
    void setStartLevel();
    void randStatus();

};
#endif // GRAPHWIDGET_H
