#include "node.h"

#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QPainter>

#include "edge.h"

namespace gui {

Node::Node(double x, double y, const QString& text)
  : shape_(x, y, 0, 0)
{
  auto proxy = new QGraphicsProxyWidget(this);
  auto label = new QLabel(text);

  auto font = label->font();
  font.setPointSize(16);
  label->setFont(font);
  label->setAttribute(Qt::WA_TranslucentBackground);
  proxy->setWidget(label);

  prepareGeometryChange();

  const auto diametr = std::max(label->rect().width(), label->rect().height());
  shape_.setWidth(diametr);
  shape_.setHeight(diametr);

  auto node_center = boundingRect().center();
  node_center.rx() -= label->rect().width() / 2;
  node_center.ry() -= label->rect().height() / 2;

  proxy->setPos(node_center);
}


void Node::add_edge(Edge* edge)
{
  edges_.push_back(edge);
  edge->adjust();
}


QRectF Node::boundingRect() const { return shape_; }

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::lightGray);
  painter->drawEllipse(shape_);
}


} // namespace gui
