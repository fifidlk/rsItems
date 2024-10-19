#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include "rsgraphicsitem.h"
#include "qdebug.h"

// ***********************************************
//
rsGraphicsItem::rsGraphicsItem() : QObject() {

    _hId=-1;
    _addMode=false;

}

// ***********************************************
//
void rsGraphicsItem::enterAddMode(void) {

    if (_addModeAllowed) {
        _addMode=true;
        setCursor(QCursor(Qt::CrossCursor));

        grabMouse();
    }
}


// ***********************************************
// return the bounding rectangle
QRectF rsGraphicsItem::boundingRect() const {

    return _boundingRect;

}


// ***********************************************
//
void rsGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    if (_addMode) {                                 // Mode addition de points

        if (event->button()==Qt::RightButton) {     // click droit sort du mode
            _addMode=false;
            ungrabMouse();
            unsetCursor();
            qDebug() << " leaving add mode " ;
            return;
        }
        else if (event->button()==Qt::LeftButton) { // click Gauche ajoute un point
            qDebug() << "adding point";
            _points.append(QPoint(event->pos().x(),event->pos().y()));
            prepareGeometryChange();
            updateBoundingRect();
            return ;

        }
    }
    if (!_addMode && isSelected()) {                // mode normal
        if (event->button()==Qt::LeftButton) {      // click gauche gere les resize
            _hId=isMouseInHandle(event->pos());     // souris sur un handle ?
                                                    // si oui _hId permet la gestion par move Event
            if(_hId==-1){                           // si non transmettre event

                QGraphicsItem::mousePressEvent(event);
            }
            else setCursor(QCursor(Qt::SizeAllCursor)); // si oui changer curseur
        }
        if (event->button()==Qt::RightButton){       // click droit gere le menu contextuel
            QMenu* menu =new QMenu;
            menu->addAction("Ajouter des points",this,SLOT(enterAddMode(void)));
            menu->popup(QCursor::pos());
        }
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

