#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "rsgraphicsitem.h"
#include "rspolylineitem.h"


#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

// ***********************************************
//
rsPolyLineItem::rsPolyLineItem(QList<QPoint> points) {

    _points=points;
    updateBoundingRect();

}


// ***********************************************
// draw the polyline
void rsPolyLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget){

    QBrush hBrush(Qt::SolidPattern);
    hBrush.setColor(Qt::blue);
    QPen hPen(Qt::black);
    int i;

    QPoint points[_points.length()];

    for (i=0; i<_points.length();i++) points[i]=_points[i];
    painter->drawPolyline(points,_points.length());

    if (this->isSelected()) {
        painter->setBrush(hBrush);
        painter->setPen(Qt::lightGray);
        QRectF handles[_handles.length()];
        for (i=0; i<_handles.length();i++) handles[i]=_handles[i];
        painter->drawRects(handles,_handles.length());
    }

}
// ***********************************************
// mets a jour le boundingRect en fn de _points
void rsPolyLineItem::updateBoundingRect(){

    if (_points.length()<1) return ;

    int xMin,xMax,yMin,yMax,h,w;

    QPoint point;
    xMin=xMax=_points[0].x();
    yMin=yMax=_points[0].y();

    _handles.clear();

    foreach (point,_points) {

        xMin= min(xMin,point.x());
        xMax= max(xMax,point.x());
        yMin= min (yMin,point.y());
        yMax= max (yMax,point.y());
        _handles.append(QRect(point.x()-5,point.y()-5,10,10));
    }

    _boundingRect.setX(xMin-5);
    _boundingRect.setY(yMin-5);

    h=yMax-yMin; if (w<10) w=10;
    w=xMax-xMin; if (h<10) h=10;

    _boundingRect.setWidth(w+10);
    _boundingRect.setHeight(h+10);

}

// ***********************************************
void rsPolyLineItem::resize(QGraphicsSceneMouseEvent *event){

    if (_hId>-1) {

        _points[_hId].setX(event->pos().x());
        _points[_hId].setY(event->pos().y());

        prepareGeometryChange();
        updateBoundingRect();
    }
}
