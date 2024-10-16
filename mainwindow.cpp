
//#include
#include <QGraphicsView>
#include <QGraphicsItem>
#include <rslineitem.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene * scene=new QGraphicsScene ;
    QPoint pa=QPoint(10,15);
    QPoint pb=QPoint(100,150);

    rsLineItem *item;
    item    = new rsLineItem(pa,pb);

   // item = scene->addRect(0,0,20,80);
    scene->addItem(item);
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
 //   item->setFlags(QGraphicsItem::ItemIsSelectable);

    ui->graphicsView->setScene(scene);
   // ui-


}

MainWindow::~MainWindow()
{
    delete ui;
}
