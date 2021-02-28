#include "mainwindow.h"
#include "gui/graph/node.h"
#include "gui/graph/edge.h"
#include "util/keysmanager/keysmanager.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui_()
  , scene_(new QGraphicsScene(this))
{
  ui_.setupUi(this);
  ui_.graphicsView->setScene(scene_);

  auto node1 = new gui::Node(QStringList{"node1"});
  auto node2 = new gui::Node(QStringList{"node2"});
  node2->setPos(0, 150);
  auto edge = new gui::Edge(node1, node2);

  scene_->addItem(node1);
  scene_->addItem(node2);
  scene_->addItem(edge);
}
