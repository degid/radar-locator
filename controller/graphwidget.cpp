#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-10, -10, 800, 600);
    setScene(scene);
    setMinimumSize(400, 400);
    //setWindowTitle(tr("Mnemonic diagram"));
    setWindowTitle("Mnemonic diagram");

    node = QSharedPointer<Node>(new Node);

    readXML("../controller/schemas");

    node->equip->setPosition(0);
    scene->addItem(node->equip);

    connect(node->equip, SIGNAL(buttonPress(QSharedPointer<Node>)), this, SLOT(changeLevel(QSharedPointer<Node>)));

    QMap<QString, QSharedPointer<Node>>::Iterator it1 = node->_node.begin();
    for (; it1 != node->_node.end(); it1++) {
        connect(it1.value()->equip, SIGNAL(buttonPress(QSharedPointer<Node>)), this, SLOT(changeLevel(QSharedPointer<Node>)));

        QMap<QString, QSharedPointer<Node>>::Iterator it2;
        it2 = it1.value()->_node.begin();

        for (;it2 != it1.value()->_node.end() ; it2++ ) {
            connect(it2.value()->equip, SIGNAL(buttonPress(QSharedPointer<Node>)), this, SLOT(setStatus(QSharedPointer<Node>)));
        }
    }
}

void GraphWidget::addNode(QMap<QString, QSharedPointer<Node>> *map,
                          const QString name,
                          QSharedPointer<Node> parent)
{
    map->insert(
                name,
                QSharedPointer<Node>(
                    new Node{
                        new Equipment(name, this),
                        parent,
                        QMap<QString, QSharedPointer<Node>>()
                    }
                    )
                );

    parent->_node[name]->equip->setNode(parent->_node[name]);
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
                                node->equip = new Equipment(attr.value().toString(), this);
                                node->equip->setNode(node);
                                node->parent = nullptr;
                            }
                        }
                    } else if(xmlReader.name() == "equipment") {
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes()){
                            if(attr.name().toString() == "name") {
                                name = attr.value().toString();
                                addNode(&node->_node, name, node);
                            }
                        }

                    } else if(xmlReader.name() == "state") {
                        nameState = xmlReader.readElementText();
                        addNode(&node->_node[name]->_node, nameState, node->_node[name]);
                    }
                }

                xmlReader.readNext();
            }
        }
        file.close();
    }
}



void GraphWidget::changeLevel(QSharedPointer<Node> node)
{
    scene->clear();
    QMap<QString, QSharedPointer<Node>>::Iterator it = node->_node.begin();
    for (int i = 0; it != node->_node.end(); it++, i++ ) {
        it.value()->equip->setPosition(i);
        scene->addItem(it.value()->equip);
    }
}

void GraphWidget::setStatus(QSharedPointer<Node> node)
{

    qDebug() << "status wi" << node->equip->getTitle();
}
