#pragma once

#include <QGraphicsItem>

namespace gui {

class Node;

class Edge : public QGraphicsItem
{
  Node* from_;
  Node* to_;
  QPointF from_point_;
  QPointF to_point_;
  const double arrow_size_;

public:
  explicit Edge(Node* from, Node* to);

  enum { Type = UserType + 1 };
  int type() const override;

  Node* source_node();
  Node* dest_node();

  void adjust();

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

} // namespace gui
