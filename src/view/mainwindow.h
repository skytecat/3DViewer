#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define OPEN_FILE 1
#define CLEAR 2

#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QVBoxLayout>

#include "glview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void showError();

 private slots:
  void on_pushButton_OpenFile_clicked();

  void on_ShiftX_sliderMoved(int position);

  void on_ShiftY_sliderMoved(int position);

  void on_ShiftZ_sliderMoved(int position);

  void on_Scale_sliderMoved(int position);

  void on_RotationX_sliderMoved(int position);

  void on_RotationY_sliderMoved(int position);

  void on_RotationZ_sliderMoved(int position);

 private:
  Ui::MainWindow *ui;
  Controller *m_controller;
  glView *m_glView;
};
#endif  // MAINWINDOW_H
