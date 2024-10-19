#ifndef RSGRAPHICSITEM_H
#define RSGRAPHICSITEM_H

#include <qpainter.h>
#include <QGraphicsItem>



class rsGraphicsItem :  public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    rsGraphicsItem();
    void setBrush(QBrush brush) {_brush=brush;}
    void setPen(QPen pen) {_pen=pen;}

     QRectF boundingRect(void) const  ;

    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)  {}


    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:

    void enterAddMode(void) ;

protected :
    virtual void updateBoundingRect(void){}
    virtual void resize(QGraphicsSceneMouseEvent *event){}

    int isMouseInHandle(QPointF pos);
    QList<QPoint>  _points;
    QList<QRectF> _handles;

    QRectF _boundingRect;
    int _hId;               // identificateur du handle (point) de redim
    bool _addMode=false;          // flag pour mode addition de points
    bool _addModeAllowed=true;   //
    QBrush _brush;
    QPen _pen;

};

#endif // RSGRAPHICSITEM_H
