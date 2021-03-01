#include "node.h"
#include "edge.h"
#include "gui/customgraphicsview/customgraphicsview.h"

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QPainter>

namespace gui {

Node::Node(const QStringList& text)
  : shape_(-150, -150, 300, 300)
{
  auto proxy = new QGraphicsProxyWidget(this);
  auto label = new QLabel(text.join('\n'));

  auto font = label->font();
  font.setPointSize(16);
  label->setFont(font);
  label->setAttribute(Qt::WA_TranslucentBackground);
  proxy->setWidget(label);

  const auto label_rect = label->rect();
  QPointF node_center(0.0, 0.0);
  node_center.rx() -= label_rect.width() / 2.0;
  node_center.ry() -= label_rect.height() / 2.0;

  proxy->setPos(node_center);
}

void Node::add_edge(Edge* edge) { edges_.push_back(edge); }

std::vector<Edge*> Node::edges() { return edges_; }

QRectF Node::boundingRect() const { return shape_; }

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::lightGray);
  painter->drawEllipse(shape_);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant& value)
{
  switch (change) {
  case ItemPositionHasChanged:
    for (auto edge : edges_)
      edge->adjust();
    break;
  default: break;
  }

  return QGraphicsItem::itemChange(change, value);
}

} // namespace gui
