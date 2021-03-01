#include "customgraphicsview.h"

#include <QWheelEvent>

namespace gui {

CustomGraphicsView::CustomGraphicsView(QWidget* parent) : QGraphicsView(parent) { }

void CustomGraphicsView::wheelEvent(QWheelEvent* event)
{
  if(event->angleDelta().y() > 0)
    scale(1.25, 1.25);
  else
    scale(0.8, 0.8);
}




} // namespace gui
