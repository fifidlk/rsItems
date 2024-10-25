
//#include
#include <QGraphicsView>
#include <QGraphicsItem>
#include <rslineitem.h>
#include "rspolylineitem.h"
#include "rspolygonitem.h"
#include "rsstepsitem.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _scene=new QGraphicsScene ;

    ui->toolButton->setIcon(QIcon(":/Sans titre.png"));
    ui->graphicsView->setScene(_scene);


}


void MainWindow::slot1(){

    // QPixmap map(":/Frames/bouldersW.png");
    // QBrush brush(Qt::blue);
    // brush.setTexture(map);
    // brush.setStyle(Qt::TexturePattern);


    QList<QPoint> points={{10,10},{10,70},{70,70},{70,10}} ;
    rsLineItem *line = new rsLineItem(points[0],points[1]);
     line->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    _scene->addItem(line);
}

void MainWindow::slot2(){

    QPixmap map(":/Frames/boulders.png");
    QBrush brush(Qt::blue);
    brush.setTexture(map);
    brush.setStyle(Qt::TexturePattern);


    QList<QPoint> points={{10,10},{10,70},{70,70},{70,10}} ;
    rsPolygonItem *polygon = new rsPolygonItem(points);
    polygon->setBrush(brush);
    polygon->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    _scene->addItem(polygon);
    // polygon->enterAddMode();

}

void MainWindow::slot3(){

    QPixmap map(":/Frames/galetsW.png");
    QBrush brush(Qt::blue);
    brush.setTexture(map);
    brush.setStyle(Qt::TexturePattern);


   QList<QPoint> points={{10,10},{20,30},{50,50},{70,100}} ;
     rsPolygonItem *polygon = new rsPolygonItem(points);
   polygon->setBrush(brush);
    polygon->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    _scene->addItem(polygon);
//    polygon->enterAddMode();

}

void MainWindow::slot4(){

    QPixmap map(":/Frames/WORK.png");
    QBrush brush(Qt::blue);
    brush.setTexture(map);
    brush.setStyle(Qt::TexturePattern);


    QList<QPoint> points={{10,10},{10,70},{70,70},{70,10}} ;
    rsPolygonItem *polygon = new rsPolygonItem(points);
    polygon->setBrush(brush);
    polygon->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    _scene->addItem(polygon);
    // polygon->enterAddMode();
}

void MainWindow::slot5(){

    QPixmap map(":/Frames/WORK.png");
    QPen pen(Qt::blue);
    pen.setWidth(3);


    QList<QPoint> points={{10,15},{100,200},{70,70},{70,10}} ;
    rsStepsItem *steps = new rsStepsItem(points);
    steps->setPen(pen);
    steps->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    _scene->addItem(steps);

}

MainWindow::~MainWindow()
{
    delete ui;
}
