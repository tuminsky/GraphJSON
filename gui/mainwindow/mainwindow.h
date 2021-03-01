#pragma once

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace gui { class Node; }

class MainWindow : public QMainWindow
{
  Q_OBJECT

  Ui::MainWindow ui_;
  QGraphicsScene* scene_;

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() = default;

private slots:
  void open_clicked();

private:
  void json_to_node(const QJsonObject& obj, gui::Node* parent = nullptr);
  QPointF calculate_valid_pos(const QPointF& hint, double new_node_radius);
};
