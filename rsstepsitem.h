#ifndef RSSTEPSITEM_H
#define RSSTEPSITEM_H

#include <QGraphicsItem>
#include <QPen>
#include <QBrush>

#include <QLine>

#include "rsgraphicsitem.h"

class rsStepsItem : public rsGraphicsItem
{
public:
    rsStepsItem(QList<QPoint> points);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)  ;

    QPainterPath shape(void) const ;
    void setPen(QPen pen) {_pen=pen;}
    void setHeight(int size) {_stepHeight=size;}

private :

    void updateBoundingRect(void);
    void resize(QGraphicsSceneMouseEvent *event);
    QPen _pen;
    int _stepHeight=15;

};

#endif // RSSTEPSITEM_H
