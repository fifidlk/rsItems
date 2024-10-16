
#include <QGraphicsItem>
#include "rsgraphicsitem.h"
#include <QGraphicsSceneMouseEvent>
#include <qpainter.h>
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
// mets a jour le boundingRect en fn de _pa et _pb
void rsLineItem::updateBoundingRect(){

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

