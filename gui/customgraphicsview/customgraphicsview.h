#pragma once

#include <QGraphicsView>

namespace gui {

class CustomGraphicsView : public QGraphicsView
{
public:
  explicit CustomGraphicsView(QWidget* parent = nullptr);

protected:
  void wheelEvent(QWheelEvent* event) override;
};

} // namespace gui
