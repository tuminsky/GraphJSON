#pragma once

#include <QGraphicsItem>

#include <vector>
#include <memory>

namespace gui {

class Edge;

class Node : public QGraphicsItem
{
  QRectF shape_;
  std::vector<Edge*> edges_;

public:
  explicit Node(double x, double y, const QString& text = {});

  void add_edge(Edge* edge);

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

} // namespace gui
