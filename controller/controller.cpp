#include "controller.h"

#include <QJsonDocument>
#include <QFile>
#include <QProcess>
#include <QUrl>
#include <QDir>

namespace util {

void Controller::json_to_graph(const QString& path)
{
  const QUrl url(path);
  const QString json_file = url.isLocalFile()
      ? QDir::toNativeSeparators(url.toLocalFile())
      : path;


  QFile file(json_file);
  if (!file.open(QFile::ReadOnly)) {
    emit failedOpen();
    return;
  }

  const auto json_doc = QJsonDocument::fromJson(file.readAll());
  if (json_doc.isNull()) {
    emit jsonFailed();
    return;
  }

  graph_to_svg(util::json_to_graph(json_doc.object()));
}

void Controller::graph_to_svg(const graph_t& graph)
{
  std::ostringstream os;
  os << graph;

  const auto str = os.str();

  QProcess graphviz;
  graphviz.setProcessChannelMode(QProcess::MergedChannels);
  graphviz.start("dot", {"-Tsvg"});
  const auto started = graphviz.waitForStarted(5000/*msecs*/);

  if (!started) {
    emit graphvizFailed();
    return;
  }

  graphviz.write(str.data(), static_cast<int>(str.size()));

  svg_.clear();

  while (graphviz.waitForReadyRead(3000/*msecs*/))
    svg_.append(graphviz.readAll());

  graphviz.kill();
  
  emit svgChanged();
}

} // namespace util
