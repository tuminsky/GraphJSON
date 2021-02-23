#pragma once

#include <QGraphicsView>

namespace gui {

class CustomGraphicsView : public QGraphicsView
{
  int timer_id_;

public:
  explicit CustomGraphicsView(QWidget* parent = nullptr);

  void item_moved();

protected:
  void wheelEvent(QWheelEvent* event) override;
  void timerEvent(QTimerEvent* event) override;
};

} // namespace gui
