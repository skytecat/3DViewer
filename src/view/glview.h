#ifndef GLVIEW_H
#define GLVIEW_H
#define GL_SILENCE_DEPRECATION

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>

#include "../Controller/controller.h"

class glView : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  explicit glView(Controller *controller, QWidget *parent = nullptr);
  ~glView();
  void initializeGL() override;
  void paintGL() override;

 private:
  Controller *m_controller;
};

#endif  // GLVIEW_H
