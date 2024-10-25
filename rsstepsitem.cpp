#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include "rsgraphicsitem.h"
#include "rsstepsitem.h"
#include <QDebug>

#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))


rsStepsItem::rsStepsItem(QList<QPoint> points) {
    _points=points;
    _addModeAllowed=false;
    updateBoundingRect();

}



// ***********************************************
// draw the line
void rsStepsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget){

    QBrush hBrush(Qt::SolidPattern);
    hBrush.setColor(Qt::blue);
    QPen hPen(Qt::black);
   // QPointF points[_zzPoints.length()];


    int nbSteps;
    float x0,x1,y0,y1;
    float lSegment,d=_stepHeight;


    // recuperation des points du segment
    x0= _points[0].x();
    y0= _points[0].y();
    x1= _points[1].x();
    y1= _points[1].y();

    // calcul de la longueur du segment
    lSegment=sqrt(pow((x1-x0),2)+pow((y1-y0),2));
    nbSteps=lSegment/(2*d);
    nbSteps+=1;
    d=(lSegment)/(2*nbSteps);  // hauteur des creneaux adaptée a la longueur d segment



    float a0,b0;            // calcul de la droite D0 y0=a0*x0+b0
    a0=(y0-y1)/(x0-x1);
    b0= y0-(a0*x0);

    float a1,b1;      // calcul de la droite paralelle D1 a une distance d

    a1=a0;
    b1=b0-(d*sqrtf(pow(a0,2)+1));

    // qDebug() << "prod : " << d*sqrtf(pow(a0,2)+1) ;

    float a2,b2;           // droite qui coupe D0 a 45° en (x0,y0)
    a2=(a0-1)/(a0+1);
    b2=y0-a2*x0;

    float ix1,iy1,ix2,iy2 ;   // point P1 d'intersection entre D1 et D2
    ix1=(b2-b1)/(a1-a2);
    iy1=a2*ix1+b2;

    float a3,b3;           // droite D3 coupe D2 a 90° en Pi (ix,iy)
    a3=-1/a2;
    b3=iy1-a3*ix1;

    ix2=(b3-b0)/(a0-a3);   // point P2 intersection D3 D0
    iy2=a3*ix2+b3;

    QPointF p1,p2;

    // p1.setX(x0);            // trace droite de ref
    // p1.setY(y0);
    // p2.setX(x1);
    // p2.setY(y1);
    // painter->drawLine(p1,p2);

    // p1.setY(a0*x0+b1);
    // p2.setX(x1);
    // p2.setY(a0*x1+b1);
    // p1.setX(x0);            // trace parallelle
    // painter->drawLine(p1,p2);


    painter->setPen(_pen);
    ix2=x0; iy2=y0;         // boucle de tracé d'un segment

    int i;
    for (i=0; i<nbSteps; i++) {

        b2=iy2-a2*ix2;            // trace D2 de D0 a D1
        ix1=(b2-b1)/(a1-a2);    // intersection avec D1
        iy1=a2*ix1+b2;
        p1.setX(ix2);
        p1.setY(iy2);
        p2.setX(ix1);
        p2.setY(iy1);
        painter->drawLine(p1,p2);

        b3=iy1-a3*ix1       ;    // droite a 90° de D2 passant par I1
        ix2=(b3-b0)/(a0-a3);
        iy2=a3*ix2+b3;

         p1.setX(ix1);
         p1.setY(iy1);
        p2.setX(ix2);
        p2.setY(iy2);
         painter->drawLine(p1,p2);
    }



     // painter->drawLine(_points[0],_points[1]);
        if (this->isSelected()) {
            painter->setBrush(hBrush);
            painter->setPen(Qt::lightGray);

            painter->drawRect(_handles[0]);
            painter->drawRect(_handles[1]);
 //           painter->drawPolygon(_zzPoints);
        }

}



// ***********************************************
void rsStepsItem::resize(QGraphicsSceneMouseEvent *event){

    if (_hId>-1) {

        _points[_hId].setX(event->pos().x());
        _points[_hId].setY(event->pos().y());

        prepareGeometryChange();
        updateBoundingRect();
    }
}



QPainterPath rsStepsItem::shape() const{

    QPainterPath path;
    QPolygon polygon;
    QPoint point;
    foreach (point,_zzPoints) {
        polygon << point;
    }
    path.addPolygon(polygon);
    return path;
}


// ***********************************************
// mets a jour le boundingRect en fn de _pa et _pb
void rsStepsItem::updateBoundingRect(){

    int xMin,xMax,yMin,yMax,h,w;
     float x0,x1,y0,y1;
    float lSegment,d=_stepHeight+10;
     QPoint point;

    _zzPoints.clear();
    // recuperation des points du segment
    x0= _points[0].x();
    y0= _points[0].y();
    x1= _points[1].x();
    y1= _points[1].y();


    float a0,b0;            // calcul de la droite D0 y0=a0*x0+b0
    a0=(y0-y1)/(x0-x1);
    b0= y0-(a0*x0);

    float a1,b1;            // calcul de la droite paralelle D1 a une distance d

    a1=a0;
    b1=b0-(d*sqrtf(pow(a0,2)+1));

    float a2,b2;           // droite D2 coupe D0 a 90° en P0 (x0,y0)
    a2=-1/a0;
    b2=y0-a2*x0;

    float a3,b3;           // droite D3 coupe D0 a 90° en P0 (x1,y1)
    a3=-1/a0;
    b3=y1-a3*x1;

    point.setX(x0);
    point.setY(y0);
    _zzPoints << point;

    float ix,iy ;
    ix=(b2-b1)/(a1-a2);     // point d'intersection entre D1 et D2
    iy=a2*ix+b2;
    point.setX(ix);
    point.setY(iy);
    _zzPoints << point;

    ix=(b3-b1)/(a1-a3) ;    // point d'intersection entre D1 et D3
    iy=a3*ix+b3;
    point.setX(ix);
    point.setY(iy);
    _zzPoints << point;

    point.setX(x1);
    point.setY(y1);
    _zzPoints << point;







    xMin= min(_points[0].x(),_points[1].x());
    xMax= max(_points[0].x(),_points[1].x());
    yMin= min (_points[0].y(),_points[1].y());
    yMax= max (_points[0].y(),_points[1].y());

    _boundingRect.setX(xMin-5);
    _boundingRect.setY(yMin-5);

    h=yMax-yMin; if (w<10) w=10;
    w=xMax-xMin; if (h<10) h=10;

    _boundingRect.setWidth(w+10);
    _boundingRect.setHeight(h+10);

    _handles.clear();
    _handles.append(QRect(_points[0].x()-5,_points[0].y()-5,10,10));
    _handles.append(QRect(_points[1].x()-5,_points[1].y()-5,10,10));

}
