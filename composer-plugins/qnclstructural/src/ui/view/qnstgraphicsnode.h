#ifndef QNSTGRAPHICSNODE_H
#define QNSTGRAPHICSNODE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneHoverEvent>

#include "qnstgraphicsentity.h"
#include "qnstgraphicsedge.h"

class QnstGraphicsNode : public QnstGraphicsEntity
{
public:
    QnstGraphicsNode(QnstGraphicsEntity* parent = 0);

    ~QnstGraphicsNode();

    QVector<QnstGraphicsEdge*> getnstGraphicsEdges();

    void addnstGraphicsEdge(QnstGraphicsEdge* edge);

    void removenstGraphicsEdge(QnstGraphicsEdge* edge);

    virtual void fit(qreal padding);

    virtual void inside();

    void adjust(bool avoidCollision = true);

protected:
    virtual void draw(QPainter* painter) = 0;

    virtual void delineate(QPainterPath* painter) const = 0;

    virtual void move(QGraphicsSceneMouseEvent* event);

    virtual void resize(QGraphicsSceneMouseEvent* event);

private:
    QVector<QnstGraphicsEdge*> edges;

};

#endif // QNSTGRAPHICSNODE_H
