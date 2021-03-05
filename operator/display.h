#ifndef DISPLAY_H
#define DISPLAY_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Display : public QGraphicsView
{
    Q_OBJECT
public:
    Display(QWidget *parent=0);

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void scaleView(qreal scaleFactor);

private:
    QGraphicsScene *scene;
};

#endif // DISPLAY_H
