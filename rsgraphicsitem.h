#ifndef RSGRAPHICSITEM_H
#define RSGRAPHICSITEM_H

#include <QGraphicsItem>



class rsGraphicsItem : public QGraphicsItem
{
public:
    rsGraphicsItem();
    void enterAddMode(void) ;


     QRectF boundingRect(void) const  ;

    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)  {}


    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

protected :
    virtual void updateBoundingRect(void){}
    virtual void resize(QGraphicsSceneMouseEvent *event){}

    int isMouseInHandle(QPointF pos);
    QList<QPoint>  _points;
    QList<QRectF> _handles;

    QRectF _boundingRect;
    int _hId;               // identificateur du handle (point) de redim
    bool _addMode;          // flag pour mode addition de points

};

#endif // RSGRAPHICSITEM_H
