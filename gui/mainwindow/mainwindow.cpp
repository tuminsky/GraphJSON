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

  auto node1 = new gui::Node(0, 0, {"node1"});
  auto node2 = new gui::Node(0, 200, {"node2"});
  auto edge = new gui::Edge(node1, node2);

  scene_->addItem(node1);
  scene_->addItem(node2);
  scene_->addItem(edge);
}


