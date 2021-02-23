#pragma once

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <memory>

class MainWindow : public QMainWindow
{
  Q_OBJECT

  Ui::MainWindow ui_;
  QGraphicsScene* scene_;

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() = default;

};
