#include "glview.h"

glView::glView(Controller *controller, QWidget *parent)
    : QOpenGLWidget(parent), m_controller(controller) {}

glView::~glView() {
  //    delete m_controller;
}

void glView::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glOrtho(-1, 1, -1, 1, -1, 1);
}

void glView::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0f, 0.0f, 0.0f);
  for (size_t i = 0; i < m_controller->GetCountFace(); i++) {
    glBegin(GL_LINE_LOOP);
    for (size_t j = 0; j < m_controller->GetCounrFaceLine(j); j++) {
      s21::VertexCoordinates tempVertex = m_controller->GetVertexFromFace(i, j);

      glVertex3d(tempVertex.x, tempVertex.y, tempVertex.z);
    }
    glEnd();
  }
}
