﻿#ifndef GRAPHWIDGET_H
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

private:
    QGraphicsScene *scene;
    QSignalMapper *mapper;
    QSharedPointer<Node> node;
    void addNode(QMap<QString, QSharedPointer<Node>> *map,
                 const QString name,
                 QSharedPointer<Node> parent);
    void readXML(const QString fileName);
    void changeLevel(QSharedPointer<Node> *);

};
#endif // GRAPHWIDGET_H
