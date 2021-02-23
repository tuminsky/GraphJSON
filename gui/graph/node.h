#pragma once

#include <QGraphicsItem>

#include <vector>
#include <memory>

namespace gui {

class CustomGraphicsView;
class Edge;

class Node : public QGraphicsItem
{
  CustomGraphicsView* view_;
  QRectF shape_;
  std::vector<Edge*> edges_;
  QPointF new_pos_;

public:
  explicit Node(CustomGraphicsView* view, const QStringList& text);

  enum { Type = UserType + 1 };
  int type() const override;

  void add_edge(Edge* edge);
  std::vector<Edge*> edges();

  void calculateForces();
  bool advance();

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

protected:
  QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

} // namespace gui
