
#include <QGraphicsView>
#include <QGraphicsItem>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene * scene=new QGraphicsScene ;
    QGraphicsItem * item;

    item = scene->addRect(0,0,20,80);
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
 //   item->setFlags(QGraphicsItem::ItemIsSelectable);

    ui->graphicsView->setScene(scene);
   // ui-


}

MainWindow::~MainWindow()
{
    delete ui;
}
