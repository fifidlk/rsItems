
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <qpainter.h>
#include "rslineitem.h"

#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

// ***********************************************
// create a resizable line from pA to pB
rsLineItem::rsLineItem(QPoint pA, QPoint pB) : QGraphicsItem() {

    _pA=pA;
    _pB=pB;
    updateBoundingRect();

}



// ***********************************************
// draw the line
void rsLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget){

    QBrush hBrush(Qt::SolidPattern);
    hBrush.setColor(Qt::blue);
    QPen hPen(Qt::black);

    painter->drawLine(_pA,_pB);
    if (this->isSelected()) {
        painter->setBrush(hBrush);
        painter->setPen(Qt::lightGray);

        painter->drawRect(_handleA);
        painter->drawRect(_handleB);
        // painter->drawRect(_boundingRect);
    }

}

// ***********************************************
// return the bounding rectangle
QRectF rsLineItem::boundingRect() const {

    return _boundingRect;

}

// ***********************************************
void rsLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    int hId;
    if ((hId=isMouseInHandle(event->pos()))) {

        _hId=hId;
    }
    else
        QGraphicsItem::mousePressEvent(event);

}

// ***********************************************
void rsLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    if (_hId) resize(event);
    else QGraphicsItem::mouseMoveEvent(event);
}

// ***********************************************
void rsLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    if (_hId) _hId=0; //resize(event);
    else QGraphicsItem::mouseReleaseEvent(event);
}


// ***********************************************
void rsLineItem::resize(QGraphicsSceneMouseEvent *event){

    if (_hId==1) {

        _pA.setX(event->pos().x());
        _pA.setY(event->pos().y());
    }
    if (_hId==2) {

        _pB.setX(event->pos().x());
        _pB.setY(event->pos().y());
    }

    prepareGeometryChange();
    updateBoundingRect();
}



// ***********************************************
// rend 1 si pos est dans le handler A
// rend 2 si pos est dans le handler B
// sinon rend 0

int  rsLineItem::isMouseInHandle(QPointF pos) {

    if (    pos.x()>=_handleA.x() &&
            pos.x()<=_handleA.x()+_handleA.width() &&
        pos.y()>= _handleA.y() &&
        pos.y()<= _handleA.y()+_handleA.height())
        return 1;

    if (    pos.x()>=_handleB.x() &&
        pos.x()<=_handleB.x()+_handleB.width() &&
        pos.y()>= _handleB.y() &&
        pos.y()<= _handleB.y()+_handleB.height())
        return 2;

    return 0;


}


// ***********************************************
// mets a jour le boundingRect en fn de _pa et _pb
void rsLineItem::updateBoundingRect(){

    int xMin,xMax,yMin,yMax,h,w;

    xMin= min(_pA.x(),_pB.x());
    xMax= max(_pA.x(),_pB.x());
    yMin= min (_pA.y(),_pB.y());
    yMax= max (_pA.y(),_pB.y());

    _boundingRect.setX(xMin-5);
    _boundingRect.setY(yMin-5);

    h=yMax-yMin; if (w<10) w=10;
    w=xMax-xMin; if (h<10) h=10;

    _boundingRect.setWidth(w+10);
    _boundingRect.setHeight(h+10);

    _handleA.setRect(_pA.x()-5,_pA.y()-5,10,10);
    _handleB.setRect(_pB.x()-5,_pB.y()-5,10,10);

}
