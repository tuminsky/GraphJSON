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
  explicit Node(QPointF pos, const QStringList& text);

  void add_edge(Edge* edge);
  const std::vector<Edge*> edges() const;

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

} // namespace gui
