#pragma once

#include <QGraphicsItem>

namespace gui {

class Node;

class Edge : public QGraphicsItem
{
  Node* from_;
  Node* to_;

public:
  explicit Edge(Node* from, Node* to);

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

} // namespace gui
