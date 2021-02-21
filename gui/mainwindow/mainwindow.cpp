#include "mainwindow.h"

#include "gui/graph/node.h"
#include "gui/graph/edge.h"

#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui_()
  , scene_(new QGraphicsScene(this))
{
  ui_.setupUi(this);
  ui_.graphicsView->setScene(scene_);
  ui_.graphicsView->setRenderHint(QPainter::Antialiasing);

  auto node1 = new gui::Node({0, 0, 100, 100}, "node1");
  auto node2 = new gui::Node({150, 0, 100, 100}, "node2");
  auto node3 = new gui::Node({-150, 150, 100, 100}, "node3");

  auto edge = new gui::Edge(node1, node2);
  auto edge2 = new gui::Edge(node1, node3);

  scene_->addItem(node1);
  scene_->addItem(node2);
  scene_->addItem(node3);
  scene_->addItem(edge);
  scene_->addItem(edge2);
}

