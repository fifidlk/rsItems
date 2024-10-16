
//#include
#include <QGraphicsView>
#include <QGraphicsItem>
#include <rslineitem.h>
#include "rspolylineitem.h"
#include "rspolygonitem.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _scene=new QGraphicsScene ;

    ui->graphicsView->setScene(_scene);


}


void MainWindow::slot1(){

    QPoint pa=QPoint(10,15);
    QPoint pb=QPoint(100,150);
    rsLineItem *item;
    item    = new rsLineItem(pa,pb);
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    _scene->addItem(item);
}

void MainWindow::slot2(){

    QList<QPoint> points={{75,10},{30,30},{25,50},{80,110}} ;
    rsPolyLineItem *polygon = new rsPolyLineItem(points);
    polygon->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    _scene->addItem(polygon);
    polygon->enterAddMode();

}

void MainWindow::slot3(){

   QList<QPoint> points={{10,10},{20,30},{50,50},{70,100}} ;
     rsPolygonItem *polygon = new rsPolygonItem(points);
    polygon->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    _scene->addItem(polygon);
    polygon->enterAddMode();

}

void MainWindow::slot4(){}

void MainWindow::slot5(){}

MainWindow::~MainWindow()
{
    delete ui;
}
