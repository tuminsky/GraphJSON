#include "customgraphicsview.h"
#include "gui/graph/node.h"

#include <QWheelEvent>
#include <QGraphicsItem>

namespace gui {

CustomGraphicsView::CustomGraphicsView(QWidget* parent)
  : QGraphicsView(parent)
  , timer_id_(0)
{
  setRenderHint(QPainter::Antialiasing);
}


void CustomGraphicsView::item_moved()
{
  if (timer_id_ != 0)
    timer_id_ = startTimer(100);
}


void CustomGraphicsView::wheelEvent(QWheelEvent* event)
{
  if(event->delta() > 0)
    scale(1.25, 1.25);
  else
    scale(0.8, 0.8);
}


void CustomGraphicsView::timerEvent(QTimerEvent* /*event*/)
{
  std::vector<Node*> nodes;

  for (auto item : scene()->items()) {
    if (auto node = qgraphicsitem_cast<Node*>(item))
      nodes.push_back(node);
  }

  for (auto node : nodes)
    node->calculateForces();

  bool items_moved = false;

  for (auto node : nodes) {
    if (node->advance())
      items_moved = true;
  }

  if (!items_moved) {
    killTimer(timer_id_);
    timer_id_ = 0;
  }
}



} // namespace gui
