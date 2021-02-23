#include "node.h"
#include "edge.h"

#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QPainter>

namespace gui {

Node::Node(QPointF pos, const QStringList& text)
  : shape_(pos.x(), pos.y(), 0, 0)
{
//  setFlag(ItemIsMovable);

  auto proxy = new QGraphicsProxyWidget(this);
  auto label = new QLabel(text.join('\n'));

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


void Node::add_edge(Edge* edge) { edges_.push_back(edge); }

const std::vector<Edge*> Node::edges() const { return edges_; }


QRectF Node::boundingRect() const { return shape_; }

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::lightGray);
  painter->drawEllipse(shape_);
}


} // namespace gui
