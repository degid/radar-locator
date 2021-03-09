#include <QApplication>
#include <QMainWindow>
#include <graphwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GraphWidget *widget = new GraphWidget;
    QMainWindow mainWindow;
    mainWindow.setCentralWidget(widget);
    mainWindow.setWindowTitle("Mnemonic diagram");
    mainWindow.show();
    return a.exec();
}
