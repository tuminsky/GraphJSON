#include "edge.h"

#include "node.h"

namespace gui {

Edge::Edge(Node* from, Node* to)
  : from_(from)
  , to_(to)
{ }

QRectF Edge::boundingRect() const
{
  if (!from_ || !to_)
    return {};

}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}


} // namespace gui
