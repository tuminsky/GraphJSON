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
}
