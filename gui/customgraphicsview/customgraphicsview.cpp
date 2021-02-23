#include "customgraphicsview.h"

#include <QWheelEvent>
#include <QGraphicsItem>

#include "gui/graph/node.h"

namespace gui {

CustomGraphicsView::CustomGraphicsView(QWidget* parent)
  : QGraphicsView(parent)
{
  setRenderHint(QPainter::Antialiasing);
}

void CustomGraphicsView::wheelEvent(QWheelEvent* event)
{
  if(event->delta() > 0)
    scale(1.25, 1.25);
  else
    scale(0.8, 0.8);
}



} // namespace gui
