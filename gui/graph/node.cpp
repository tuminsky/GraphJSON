#include "node.h"
#include "edge.h"
#include "gui/customgraphicsview/customgraphicsview.h"

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QPainter>

namespace gui {

Node::Node(const QStringList& text)
  : shape_(0, 0, 0, 0)
{
  setFlag(ItemIsMovable);
  setFlag(ItemSendsGeometryChanges);

  auto proxy = new QGraphicsProxyWidget(this);
  auto label = new QLabel(text.join('\n'));

  auto font = label->font();
  font.setPointSize(16);
  label->setFont(font);
  label->setAttribute(Qt::WA_TranslucentBackground);
  proxy->setWidget(label);

  prepareGeometryChange();

  const auto diametr = std::max(label->rect().width(), label->rect().height());
  shape_.setX(-(diametr / 2.0));
  shape_.setY(-(diametr / 2.0));
  shape_.setWidth(diametr);
  shape_.setHeight(diametr);

  auto node_center = boundingRect().center();
  node_center.rx() -= label->rect().width() / 2;
  node_center.ry() -= label->rect().height() / 2;

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
