#include "node.h"
#include "edge.h"
#include "gui/customgraphicsview/customgraphicsview.h"

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QPainter>

namespace gui {

Node::Node(CustomGraphicsView* view, const QStringList& text)
  : view_(view)
  , shape_(0, 0, 0, 0)
{
  setFlag(ItemIsMovable);

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


int Node::type() const { return Type; }

void Node::add_edge(Edge* edge) { edges_.push_back(edge); }

std::vector<Edge*> Node::edges() { return edges_; }


void Node::calculateForces()
{
  if (!scene()) {
    new_pos_ = pos();
    return;
  }

  // sum up all the forces repulsive of this elemen
  qreal xvel = 0, yvel = 0;

  for (const auto item : scene()->items()) {
    auto node = qgraphicsitem_cast<Node*>(item);

    if (!node) continue;

    const auto vec = mapToItem(node, 0, 0);
    const auto dx = vec.x();
    const auto dy = vec.y();
    const auto l = 2.0 * (dx * dx + dy * dy);
    const auto radius1 = node->boundingRect().width() / 2;
    const auto radius2 = shape_.width() / 2;

    if (l > 0) {
      xvel += (dx * std::abs(radius1 - radius2)) / l;
      yvel += (dx * std::abs(radius1 - radius2)) / l;
    }
  }

  // subtract all forces attracting elements
  const auto weight = (edges_.size() + 1) * 10;

  for (const auto edge : edges_) {
    QPointF vec;

    if (edge->source_node() == this)
      vec = mapToItem(edge->dest_node(), 0, 0);
    else
      vec = mapToItem(edge->source_node(), 0, 0);

    xvel -= vec.x() / weight;
    yvel -= vec.y() / weight;
  }

  if (std::abs(xvel) < 0.1 && std::abs(0.1))
    xvel = yvel = 0;

  const auto rect = scene()->sceneRect();
  new_pos_ = pos() + QPointF(xvel, yvel);
  new_pos_.setX(std::min(
    std::max(new_pos_.x(), rect.left() + 10),
    rect.right() - 10
  ));
  new_pos_.setY(std::min(
    std::max(new_pos_.y(), rect.top() + 10),
    rect.bottom() - 10
                  ));
}

bool Node::advance()
{
  if (new_pos_ == pos())
    return false;

  setPos(new_pos_);
  return true;
}


QRectF Node::boundingRect() const { return shape_; }

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::lightGray);
  painter->drawEllipse(shape_);
}


QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
  switch (change) {
  case ItemPositionHasChanged:
    for (auto edge : edges_)
      edge->adjust();
    view_->item_moved();
    break;
  default: break;
  }

  return QGraphicsItem::itemChange(change, value);
}

} // namespace gui
