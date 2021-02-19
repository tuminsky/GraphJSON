#pragma once

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <memory>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow ui_;
  std::unique_ptr<QGraphicsScene> scene_;
};
