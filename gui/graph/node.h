#pragma once

#include <QGraphicsItem>

#include <memory>

namespace gui {

//class Edge;

class Node : public QGraphicsItem
{
  QRectF pos_;

public:
  explicit Node(const QRectF& pos, const QString& text = {});

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

};

} // namespace gui
