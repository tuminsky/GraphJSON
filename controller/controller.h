#pragma once

#include <QObject>
#include <QProcess>

#include <memory>

#include "graph/graph.h"

namespace util {

class Controller : public QObject
{
  Q_OBJECT

  QString svg_;

  Q_PROPERTY(QString svg READ svg NOTIFY svgChanged)

public:
  Q_INVOKABLE void json_to_graph(const QString& path);

  QString svg() const { return svg_; }

signals:
  void failedOpen();
  void jsonFailed();
  void svgChanged();
  void graphvizFailed();

private:
  void graph_to_svg(const graph_t& graph);
};


} // namespace util
