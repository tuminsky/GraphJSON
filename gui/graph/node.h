#pragma once

#include <QGraphicsItem>

#include <vector>
#include <memory>

namespace gui {

class CustomGraphicsView;
class Edge;

class Node : public QGraphicsItem
{
  QRectF shape_;
  std::vector<Edge*> edges_;

public:
  explicit Node(const QStringList& text);

  void add_edge(Edge* edge);
  std::vector<Edge*> edges();

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

protected:
  QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

} // namespace gui
