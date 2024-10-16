#ifndef RSLINEITEM_H
#define RSLINEITEM_H

#include <QGraphicsItem>
#include <QPen>
#include <QBrush>

#include <QLine>

class rsLineItem : public QGraphicsItem
{
public:
    rsLineItem(QPoint pA, QPoint pB);

    QRectF boundingRect(void) const  ;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)  ;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private :
    QPoint _pA,_pB;
    QRectF _boundingRect;
    QRectF _handleA,_handleB;

    void updateBoundingRect(void);
    void resize(QGraphicsSceneMouseEvent *event);
    int isMouseInHandle(QPointF pos);
    int _hId;   // identificateur du handle (point) de redim

};

#endif // RSLINEITEM_H
