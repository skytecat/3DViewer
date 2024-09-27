#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("3D Viewer");
  w.setFixedSize(855, 663);
  w.show();
  return a.exec();
}
