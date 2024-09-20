#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/Model_3DViewer.h"

class Controller
{
public:
    Controller();
    ~Controller();
    int execute(int command);

    int ObjParser(std::string FileName);
    void ClearModel();

    void SetScaleDefault();
    size_t GetCountFace();
    size_t GetCountVertex();
    size_t GetCounrFaceLine(size_t numberLine);
    s21::VertexCoordinates GetVertexFromFace(size_t row, size_t col);

    void useAxis(double shift);
    void setAxis(s21::Move* o);
    void RotationX(double angle);
    void RotationY(double angle);
    void RotationZ(double angle);


    void SetScale(double scale);

private:
    s21::Model_3DViewer m_Model;
};

#endif // CONTROLLER_H
