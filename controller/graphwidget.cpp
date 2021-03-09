#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-10, -10, 800, 600);
    setScene(scene);
    setMinimumSize(400, 400);

    node = QSharedPointer<Node>(new Node);

    readXML("../controller/schemas");

    setStartLevel();
    randStatus();

    startTimer(100);
}


void GraphWidget::readXML(const QString fileName)
{
    QDir dir(fileName);
    dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::Hidden);
    QFileInfoList listSchemas = dir.entryInfoList();

    for (QFileInfo fileInfo : listSchemas) {
        QFile file(fileInfo.absoluteFilePath());
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            qDebug() << fileInfo.absoluteFilePath();
            qDebug() << "The file cannot be opened.";
        } else {
            QXmlStreamReader xmlReader;
            xmlReader.setDevice(&file);
            xmlReader.readNext();
            QString name = "";
            QString nameState = "";

            while (!xmlReader.atEnd()) {
                if(xmlReader.isStartElement()){
                    if(xmlReader.name() == "control"){
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes()){
                            if(attr.name().toString() == "name") {
                                node->title = attr.value().toString();
                            }
                        }
                    } else if(xmlReader.name() == "equipment") {
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes()){
                            if(attr.name().toString() == "name") {
                                name = attr.value().toString();
                                addNode(&node->nodes, name, true, node);
                            }
                        }

                    } else if(xmlReader.name() == "state") {
                        nameState = xmlReader.readElementText();
                        addNode(&node->nodes[name]->nodes, nameState, false, node->nodes[name]);
                    }
                }

                xmlReader.readNext();
            }
        }
        file.close();
    }
}


void GraphWidget::addNode(QMap<QString, QSharedPointer<Node>> *map,
                          const QString name,
                          bool isTree,
                          QSharedPointer<Node> parent)
{
    map->insert(name, QSharedPointer<Node>(new Node{name, parent, isTree}));
}


void GraphWidget::changeLevelNext(QSharedPointer<Node> _node)
{
    disconnect(_node->equipTmp, SIGNAL(buttonPress(QSharedPointer<Node>)), this, SLOT(changeLevelNext(QSharedPointer<Node>)));
    changeLevel(&_node);
}



void GraphWidget::changeLevelPrev(QSharedPointer<Node> _node)
{
    disconnect(_node->equipTmp, SIGNAL(buttonPress(QSharedPointer<Node>)), this, SLOT(changeLevelPrev(QSharedPointer<Node>)));
    changeLevel(&_node->parent);
}

void GraphWidget::changeLevel(QSharedPointer<Node> *_node)
{
    scene->clear();

    int pos = 0;

    if(_node->isNull()) {
        setStartLevel();
        return;
    }

    _node->get()->equipTmp = new Equipment(_node->get()->title, this);
    _node->get()->equipTmp->setNode(*_node);
    _node->get()->equipTmp->setPosition(pos);
    scene->addItem(_node->get()->equipTmp);

    connect(_node->get()->equipTmp, SIGNAL(buttonPress(QSharedPointer<Node>)),
            this, SLOT(changeLevelPrev(QSharedPointer<Node>)));

    pos += 2;
    QMapIterator<QString, QSharedPointer<Node>> it(_node->get()->nodes);
    while (it.hasNext()) {
        it.next();
        it.value()->equipTmp = new Equipment(it.value()->title, this);
        it.value()->equipTmp->setNode(it.value());
        it.value()->equipTmp->setPosition(pos);
        scene->addItem(it.value()->equipTmp);

        if(it.value()->isTree){
            connect(it.value()->equipTmp, SIGNAL(buttonPress(QSharedPointer<Node>)),
                    this, SLOT(changeLevelNext(QSharedPointer<Node>)));
        } else {
            connect(it.value()->equipTmp, SIGNAL(buttonPress(QSharedPointer<Node>)),
                    this, SLOT(setStatus(QSharedPointer<Node>)));
        }

        pos++;
    }
}

void GraphWidget::setStartLevel()
{
    node->equipTmp = new Equipment(node->title, this);
    node->equipTmp->setNode(node);

    node->equipTmp->setPosition(0);
    scene->addItem(node->equipTmp);

    connect(node->equipTmp, SIGNAL(buttonPress(QSharedPointer<Node>)), this, SLOT(changeLevelNext(QSharedPointer<Node>)));
}

void GraphWidget::randStatus()
{

}

void GraphWidget::setStatus(QSharedPointer<Node> node)
{

    qDebug() << "status wi" << node->equipTmp->getTitle();
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);


}
