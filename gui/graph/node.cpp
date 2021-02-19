#include "node.h"

#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QPainter>

namespace gui {

Node::Node(const QRectF& pos, const QString& text)
  : pos_(pos)
{
  setFlag(ItemIsMovable);

  auto proxy = new QGraphicsProxyWidget(this);
  auto label = new QLabel(text);

  auto font = label->font();
  font.setPointSize(16);
  label->setFont(font);
  proxy->setWidget(label);

  auto node_center = boundingRect().center();
  node_center.rx() -= label->rect().width() / 2;
  node_center.ry() -= label->rect().height() / 2;

  proxy->setPos(node_center);
}

QRectF Node::boundingRect() const { return pos_; }

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
  QPen pen;
  pen.setWidth(2);

  painter->setPen(pen);
  painter->drawEllipse(pos_);
}



} // namespace gui
