#ifndef QNSTGRAPHICSNODE_H
#define QNSTGRAPHICSNODE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneHoverEvent>

#include "StructuralEntity.h"
#include "StructuralEdge.h"

class StructuralNode : public QnstEntityWithEdges
{
public:
  StructuralNode(StructuralEntity* parent = 0);

  ~StructuralNode();

  virtual void fit(qreal padding);

  virtual void inside();

  virtual void adjust(bool avoidCollision = true);

protected:
  virtual void draw(QPainter* painter) = 0;
  virtual void delineate(QPainterPath* painter) const = 0;

  virtual void move(QGraphicsSceneMouseEvent* event);
  virtual void resize(QGraphicsSceneMouseEvent* event);

};

#endif // QNSTGRAPHICSNODE_H