#include "mainwindow.h"

#include "gui/graph/node.h"
#include "gui/graph/edge.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

#include <cmath>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui_()
  , scene_(new QGraphicsScene(this))
{
  ui_.setupUi(this);
  ui_.graphicsView->setScene(scene_);

  connect(ui_.aOpen, &QAction::triggered,
          this, &MainWindow::open_clicked);

  auto node1 = new gui::Node(0, 0, {"node1"});
  auto node2 = new gui::Node(0, 200, {"node2"});
  auto edge = new gui::Edge(node1, node2);

  scene_->addItem(node1);
  scene_->addItem(node2);
  scene_->addItem(edge);
}

void MainWindow::open_clicked()
{
  const auto path = QFileDialog::getOpenFileName(this, "Open", "", "*.json");

  if (path.isEmpty())
    return;

  QFile file(path);

  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(this, "Critical", "Failed open file");
    return;
  }

  const auto json_doc = QJsonDocument::fromJson(file.readAll());

  if (json_doc.isNull()) {
    QMessageBox::critical(this, "Critical", "Incorrect json format");
    return;
  }

  iterate_json(json_doc.object());
}


void MainWindow::iterate_json(const QJsonObject& json_obj)
{


}

