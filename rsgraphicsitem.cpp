#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include "rsgraphicsitem.h"
#include "qdebug.h"

rsGraphicsItem::rsGraphicsItem() {

    _hId=-1;
    _addMode=false;

}

// ***********************************************
//
void rsGraphicsItem::enterAddMode(void) {

    _addMode=true;
    setCursor(QCursor(Qt::CrossCursor));

    grabMouse();
}


// ***********************************************
// return the bounding rectangle
QRectF rsGraphicsItem::boundingRect() const {

    return _boundingRect;

}


// ***********************************************
//
void rsGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    if (_addMode) {
        if (event->button()==Qt::RightButton) {
            _addMode=false;
            ungrabMouse();
            unsetCursor();
            qDebug() << " leaving add mode " ;
        }
        else if (event->button()==Qt::LeftButton) {
            qDebug() << "adding point";
            _points.append(QPoint(event->pos().x(),event->pos().y()));
            prepareGeometryChange();
            updateBoundingRect();

        }
    }
    if (!_addMode) {
        _hId=isMouseInHandle(event->pos());

        if(_hId==-1){

            QGraphicsItem::mousePressEvent(event);
        }
        else setCursor(QCursor(Qt::SizeAllCursor));
    }

}

// ***********************************************
void rsGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    if (_hId>-1) resize(event);
    else QGraphicsItem::mouseMoveEvent(event);
}

// ***********************************************
void rsGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    if (_hId>-1) {
        _hId=-1; //resize(event)
        unsetCursor();
    }
    else QGraphicsItem::mouseReleaseEvent(event);
}

// ***********************************************
// rend l'id d'un rectangle dans _handles si pos y correspond
// sinon rend -1

int  rsGraphicsItem::isMouseInHandle(QPointF pos) {

    int i;
    for (i=0 ; i< _handles.length() ; i++) {

        if (    pos.x()>=_handles[i].x() &&
            pos.x()<=_handles[i].x()+_handles[i].width() &&
            pos.y()>= _handles[i].y() &&
            pos.y()<= _handles[i].y()+_handles[i].height())
            return i;

    }



    return -1;


}
