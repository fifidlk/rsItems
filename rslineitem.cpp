
#include <QGraphicsItem>
#include "rsgraphicsitem.h"
#include <QGraphicsSceneMouseEvent>
#include <qpainter.h>
#include <math.h>
#include "rslineitem.h"

#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

// ***********************************************
// create a resizable line from pA to pB
rsLineItem::rsLineItem(QPoint pA, QPoint pB) : rsGraphicsItem() {

    _points << pA;
    _points << pB;
    _addModeAllowed=false;
    updateBoundingRect();

}



// ***********************************************
// draw the line
void rsLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget){

    QBrush hBrush(Qt::SolidPattern);
    hBrush.setColor(Qt::blue);
    QPen hPen(Qt::black);

    painter->drawLine(_points[0],_points[1]);
    if (this->isSelected()) {
        painter->setBrush(hBrush);
        painter->setPen(Qt::lightGray);

        painter->drawRect(_handles[0]);
        painter->drawRect(_handles[1]);
        // painter->drawRect(_boundingRect);
    }

}



// ***********************************************
void rsLineItem::resize(QGraphicsSceneMouseEvent *event){

    if (_hId>-1) {

        _points[_hId].setX(event->pos().x());
        _points[_hId].setY(event->pos().y());

    prepareGeometryChange();
    updateBoundingRect();
    }
}


// ***********************************************
//
QPainterPath rsLineItem::shape() const{

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
void rsLineItem::updateBoundingRect(){

    float x0,x1,y0,y1;
    float lSegment,d=15;
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

    int xMin,xMax,yMin,yMax,h,w;

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

