#include <QApplication>
#include <QQmlApplicationEngine>

#include "controller/controller.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  qmlRegisterType<util::Controller>("util.controller", 1, 0, "Controller");

  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:/mainwindow.qml"));

  return app.exec();
}
