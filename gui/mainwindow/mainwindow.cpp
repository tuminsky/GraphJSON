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

  scene_->clear();
  json_to_node(json_doc.object());
}

void MainWindow::json_to_node(const QJsonObject& obj, gui::Node* parent)
{
  util::KeysManager km(obj);

  QStringList text;
  for (const auto& key : km.keys_not_array_or_object()) {
    const auto value = obj.value(key);
    auto line = key + ": ";

    if (value.isBool())        line += value.toBool();
    else if (value.isString()) line += value.toString();
    else if (value.isDouble()) line += QString::number(value.toDouble());

    text << line;
  }

  auto node = new gui::Node(text);
  scene_->addItem(node);

  QPointF pos(0.0, 0.0);

  if (parent) {
    pos = parent->mapToScene(0.0, 0.0);
    const auto new_node_radius = node->boundingRect().width() / 2.0;
    pos.ry() += parent->boundingRect().width() / 2.0 + new_node_radius + 50.0;
    pos = calculate_valid_pos(pos, new_node_radius);
  }

  node->setPos(pos);
  scene_->addItem(new gui::Edge(parent, node));

  for (const auto& child_key : km.keys_is_array_or_object()) {
    const auto child = obj.value(child_key);

    if (child.isArray()) {
      for (const auto item : child.toArray())
        json_to_node(item.toObject(), node);
    } else { // isObject
      json_to_node(child.toObject(), node);
    }
  }
}

QPointF MainWindow::calculate_valid_pos(const QPointF& hint, double new_node_radius)
{
  const auto central_node = scene_->itemAt(hint, {});

  if (!central_node)
    return hint;

  const auto central_node_radius = central_node->boundingRect().width() / 2.0;

  const QPointF left_point {
    central_node->mapToScene(0.0, 0.0).x() - central_node_radius - new_node_radius - 50.0,
    hint.y()
  };

  const auto left_item = scene_->itemAt(left_point, {});

  if (!left_item)
    return left_point;

  return calculate_valid_pos(left_point, new_node_radius);
}
