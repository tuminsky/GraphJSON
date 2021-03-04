#pragma once

#include <QObject>

#include "graph/graph.h"

namespace util {

class Controller : public QObject
{
  Q_OBJECT

  QString svg_;

  Q_PROPERTY(QString svg READ svg NOTIFY svgChanged)

public:
  Q_INVOKABLE void json_to_graph(const QString& json_file);

  QString svg() const { return svg_; }

signals:
  void failedOpen();
  void jsonFailed();
  void svgChanged();

private:
  void graph_to_svg(const graph_t& graph);
};


} // namespace util
