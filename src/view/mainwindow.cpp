#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_controller = new Controller();
  m_glView = new glView(m_controller);
  ui->verticalLayout->addWidget(m_glView);
}

MainWindow::~MainWindow() {
  if (ui) {
    delete ui;
  }
  if (m_controller) {
    delete m_controller;
  }
}

void MainWindow::showError() {
  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Critical);
  msgBox.setWindowTitle("Ошибка");
  msgBox.setText("Файл поврежден!");
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.exec();
}

void MainWindow::on_pushButton_OpenFile_clicked() {
  QString filePath;
  filePath = QFileDialog::getOpenFileName(this, "Выбрать файл", "../../../../",
                                          "OBJ File (*.obj)");
  QFileInfo fileInfo(filePath);
  QString fileName = fileInfo.fileName();
  ui->labelFileName->setText("File name: " + fileName);
  m_controller->ClearModel();
  if (m_controller->ObjParser(filePath.toUtf8().constData())) {
    showError();
  } else {
    QString numFace = QString::number(m_controller->GetCountFace());
    ui->labelFaceCount->setText("Face Count: " + numFace);
    QString numVert = QString::number(m_controller->GetCountVertex());
    ui->labelVertexCount->setText("Vertex Count: " + numVert);
  }
}

void MainWindow::on_ShiftX_sliderMoved(int position) {
  s21::MoveX moveX_;
  static int prev_positionX = 0;
  m_controller->setAxis(&moveX_);
  m_controller->useAxis((double)(position - prev_positionX) / 250);
  m_glView->update();
  prev_positionX = position;
}

void MainWindow::on_ShiftY_sliderMoved(int position) {
  s21::MoveY moveY_;
  static int prev_positionY = 0;
  m_controller->setAxis(&moveY_);
  m_controller->useAxis((double)(position - prev_positionY) / 250);
  m_glView->update();
  prev_positionY = position;
}

void MainWindow::on_ShiftZ_sliderMoved(int position) {
  s21::MoveZ moveZ_;
  static int prev_positionZ = 0;
  m_controller->setAxis(&moveZ_);
  m_controller->useAxis((double)(position - prev_positionZ) / 250);
  m_glView->update();
  prev_positionZ = position;
}

void MainWindow::on_Scale_sliderMoved(int scale) {
  static double prev_scale = 1;
  double d_scale = scale;
  d_scale /= 20;
  m_controller->SetScale(d_scale / prev_scale);
  m_glView->update();
  prev_scale = d_scale;
}

void MainWindow::on_RotationX_sliderMoved(int angle) {
  static double prev_angle = 0;
  double deltaAngle = (angle - prev_angle) * M_PI / 180.0;
  m_controller->RotationX(deltaAngle);
  m_glView->update();
  prev_angle = angle;
}

void MainWindow::on_RotationY_sliderMoved(int angle) {
  static double prev_angle = 0;
  double deltaAngle = (angle - prev_angle) * M_PI / 180.0;
  m_controller->RotationY(deltaAngle);
  m_glView->update();
  prev_angle = angle;
}

void MainWindow::on_RotationZ_sliderMoved(int angle) {
  static double prev_angle = 0;
  double deltaAngle = (angle - prev_angle) * M_PI / 180.0;
  m_controller->RotationZ(deltaAngle);
  m_glView->update();
  prev_angle = angle;
}
