#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QGraphicsSvgItem>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui_()
{
  ui_.setupUi(this);
  ui_.graphicsView->setScene(&scene_);

  connect(ui_.aOpen, &QAction::triggered,
          this, &MainWindow::open_clicked);
}

void MainWindow::open_clicked()
{
  const auto path = QFileDialog::getOpenFileName(this, "Open", "", "*.json");

  if (path.isEmpty())
    return;

  QFile file(path);
  if (!file.open(QFile::ReadOnly)) {
    QMessageBox::critical(this, "Critical", "Failed open file: " + path);
    return;
  }


  const auto json_doc = QJsonDocument::fromJson(file.readAll());
  if (json_doc.isNull()) {
    QMessageBox::critical(this, "Critical", "Incorrect format json");
    return;
  }

  const auto graph = util::json_to_graph(json_doc.object());

  show_graph(graph);
}

void MainWindow::show_graph(const util::graph_t& graph)
{
  using namespace util;

  std::ostringstream os;
  os << graph;

  std::ofstream fout;
  fout.open("D:\\Programming\\Qt\\Projects\\dev_os_homework_2\\qwe.txt");
  fout << graph;

  const auto str = os.str();

  QProcess graphviz;
  graphviz.setProcessChannelMode(QProcess::MergedChannels);
  graphviz.start("dot", {"-Tsvg"});
  graphviz.write(str.data(), static_cast<int>(str.size()));

  QByteArray data;
  while (graphviz.waitForReadyRead(100)) {
    data.append(graphviz.readAll());
  }

  render_.load(data);
  auto svg = new QGraphicsSvgItem();
  svg->setSharedRenderer(&render_);

  scene_.clear();
  scene_.addItem(svg);
}
