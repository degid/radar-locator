#include "display.h"
#include "displayscene.h"
#include "targetobject.h"

#include <QDebug>

Display::Display(QWidget *parent): QGraphicsView(parent)
{
    scene = new DisplayScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);

    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);

    setWindowTitle(tr("Radar screen"));

    setBackgroundBrush(Qt::black);




    QPen pen = QPen(Qt::green);

    int ItemCount = 12;
    for (int i = 0; i < ItemCount; i++) {
        TargetObject *target = new TargetObject(tr("Object \n") + QString::number(static_cast<int>(i+1)));
        scene->addItem(target);
    }

    startTimer(1000);
}

void Display::zoomIn()
{
    scaleView(qreal(1.2));
}

void Display::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void Display::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
    default:
        QGraphicsView::keyPressEvent(event);

    }
}

void Display::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    qDebug() << event;

    const QList<QGraphicsItem *> items = scene->items();
    for(auto *item : items) {
        item->advance(0);
    }


}

void Display::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2., -event->angleDelta().y() / 240.0));
}

void Display::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

//bool Display::eventFilter(QObject *watched, QEvent *event)
//{

//}
