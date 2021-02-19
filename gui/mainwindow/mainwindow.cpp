#include "mainwindow.h"

#include "gui/graph/node.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui_()
  , scene_(std::make_unique<QGraphicsScene>())
{
  ui_.setupUi(this);
  ui_.graphicsView->setScene(scene_.get());

  scene_->addItem(new gui::Node({0, 0, 100, 100}, "test"));
}

MainWindow::~MainWindow() { }

