#include "customgraphicsview.h"
#include "gui/graph/node.h"

#include <QWheelEvent>
#include <QGraphicsItem>

namespace gui {

CustomGraphicsView::CustomGraphicsView(QWidget* parent)
  : QGraphicsView(parent)
{
  setRenderHint(QPainter::Antialiasing);
}

void CustomGraphicsView::wheelEvent(QWheelEvent* event)
{
  if(event->angleDelta().y() > 0)
    scale(1.25, 1.25);
  else
    scale(0.8, 0.8);
}




} // namespace gui
