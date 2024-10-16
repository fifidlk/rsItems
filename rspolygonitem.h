#ifndef RSPOLYGONITEM_H
#define RSPOLYGONITEM_H

#include "rsgraphicsitem.h"

class rsPolygonItem : public rsGraphicsItem
{
public:
    rsPolygonItem(QList<QPoint> points);

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)  ;



private :

    void updateBoundingRect(void);
    void resize(QGraphicsSceneMouseEvent *event);
    void addPoint(QPoint pos);

};

#endif // RSPOLYGONITEM_H
