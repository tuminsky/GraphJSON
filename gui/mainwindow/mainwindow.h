#pragma once

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QSvgRenderer>

#include "util/graph/graph.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  Ui::MainWindow ui_;
  QGraphicsScene scene_;
  QSvgRenderer render_;

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() = default;

private slots:
  void open_clicked();

private:
  void show_graph(const util::graph_t& graph);
};
