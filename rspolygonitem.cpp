#include "rspolygonitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "rsgraphicsitem.h"
#include "rspolylineitem.h"


#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))



// ***********************************************
//
rsPolygonItem::rsPolygonItem(QList<QPoint> points) {

    _points=points;
    updateBoundingRect();

}


// ***********************************************
// draw the polygon
void rsPolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                           QWidget *widget){

    QBrush hBrush(Qt::SolidPattern);
    hBrush.setColor(Qt::blue);
    QPen hPen(Qt::black);
    int i;

    QPoint points[_points.length()];

    for (i=0; i<_points.length();i++) points[i]=_points[i];
    painter->setBrush(_brush);
//    _brush.setColor(QColor(100,100,100));
//    painter->setPen(120,120,120);
    painter->drawPolygon(points,_points.length());

    if (this->isSelected()) {
        painter->setBrush(hBrush);
         QRectF handles[_handles.length()];

        painter->setPen(Qt::lightGray);

        for (i=0; i<_handles.length();i++) handles[i]=_handles[i];
        painter->drawRects(handles,_handles.length());

        // painter->setPen(Qt::red);
        // hBrush.setColor(Qt::red);
        // painter->drawRect(handles[0]);

    }

}


// ***********************************************
// mets a jour le boundingRect en fn de _points
void rsPolygonItem::updateBoundingRect(){

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

QPainterPath rsPolygonItem::shape() const{

    QPainterPath path;
    QPolygon polygon;
    QPoint point;
    foreach (point,_points) {
        polygon << point;
    }
    path.addPolygon(polygon);
    return path;
}

// ***********************************************
void rsPolygonItem::resize(QGraphicsSceneMouseEvent *event){

    if (_hId>-1) {

        _points[_hId].setX(event->pos().x());
        _points[_hId].setY(event->pos().y());

        prepareGeometryChange();
        updateBoundingRect();
    }
}
