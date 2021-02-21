#include "edge.h"

#include <QPainter>

#include <cmath>
#include "node.h"

constexpr double pi() { return std::atan(1) * 4; }

namespace gui {

Edge::Edge(Node* from, Node* to)
  : from_(from), to_(to), arrow_size_(10.0)
{
  if (from_)
    from_->add_edge(this);
  if (to_)
    to_->add_edge(this);

  adjust();
}

void Edge::adjust()
{
  if (!from_ || !to_)
    return;

  const auto source_br = from_->boundingRect();
  const auto dest_br = to_->boundingRect();

  // set start and end points
  const QLineF line(
    source_br.center(), // start
    dest_br.center()    // end
  );

  // get radius
  const auto source_radius = source_br.width() / 2;
  const auto dest_radius = dest_br.width() / 2;

  // calculate offset points from center of nodes
  const QPointF source_offset(
    line.dx() * source_radius / line.length(), // xpos
    line.dy() * source_radius / line.length()  // ypos
  );

  const QPointF dest_offset(
    line.dx() * dest_radius / line.length(), // xpos
    line.dy() * dest_radius / line.length()  // ypos
  );

  prepareGeometryChange();

  from_point_ = line.p1() + source_offset;
  to_point_ = line.p2() - dest_offset;
}

QRectF Edge::boundingRect() const
{
  if (!from_ || !to_)
    return {};

  const QSizeF size(
    to_point_.x() - from_point_.x(),
    to_point_.y() - from_point_.y()
  );

  return {from_point_, size};
}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  if (!from_ || !to_)
    return;

  const QLineF line(from_point_, to_point_);

  if (qFuzzyCompare(line.length(), 0.))
    return;

  painter->setPen(QPen{Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
  painter->drawLine(line);

  // draw the arrow
  auto angle = std::acos(line.dx() / line.length());

  if (line.dy() >= 0)
    angle = 2 * pi() - angle;

  const auto arrow_p1 = to_point_ + QPointF{
    std::sin(angle - pi() / 3) * arrow_size_,
    std::cos(angle - pi() / 3) * arrow_size_,
  };
  const auto arrow_p2 = to_point_ + QPointF{
    std::sin(angle - pi() + pi() / 3) * arrow_size_,
    std::cos(angle - pi() + pi() / 3) * arrow_size_,
  };

  QPolygonF arrow_points;
  arrow_points << line.p2() << arrow_p1 << arrow_p2;

  painter->setBrush(Qt::black);
  painter->drawPolygon(arrow_points);
}



} // namespace gui
