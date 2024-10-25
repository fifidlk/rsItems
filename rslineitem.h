#ifndef RSLINEITEM_H
#define RSLINEITEM_H

#include <QGraphicsItem>
#include "rsgraphicsitem.h"
#include <QPen>
#include <QBrush>

#include <QLine>

class rsLineItem : public rsGraphicsItem
{
public:
    rsLineItem(QPoint pA, QPoint pB);

    //QRectF boundingRect(void) const  ;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)  ;

    QPainterPath shape(void) const ;

private :
//    QRectF _handleA,_handleB;

    void updateBoundingRect(void);
    void resize(QGraphicsSceneMouseEvent *event);

};

#endif // RSLINEITEM_H
