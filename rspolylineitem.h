#ifndef RSPOLYLINEITEM_H
#define RSPOLYLINEITEM_H

#include <QGraphicsItem>
#include "rsgraphicsitem.h"
#include <QPen>
#include <QBrush>

#include <QLine>

#include "rsgraphicsitem.h"

class rsPolyLineItem : public rsGraphicsItem
{
public:
    rsPolyLineItem(QList<QPoint> points);

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)  ;



private :

    void updateBoundingRect(void);
    void resize(QGraphicsSceneMouseEvent *event);
    void addPoint(QPoint pos);

};

#endif // RSPOLYLINEITEM_H
