#include "controller.h"

Controller::Controller()
{

}

Controller::~Controller()
{

}

int Controller::ObjParser(std::string FileName)
{
    int error = m_Model.ObjParser(FileName);
    m_Model.SetScaleDefault();
    return error;
}

void Controller::ClearModel()
{
    m_Model.ClearModel();
}

void Controller::SetScaleDefault()
{
    m_Model.SetScaleDefault();
}

size_t Controller::GetCountFace()
{
    return m_Model.GetCountFace();
}

size_t Controller::GetCountVertex()
{
    return m_Model.GetCountVertex();
}

size_t Controller::GetCounrFaceLine(size_t numberLine)
{
    return m_Model.GetCounrFaceLine(numberLine);
}

s21::VertexCoordinates Controller::GetVertexFromFace(size_t row, size_t col)
{
    return m_Model.GetVertexFromFace(row, col);
}

void Controller::useAxis(double shift)
{
    m_Model.useAxis(shift);
}

void Controller::setAxis(s21::Move *o)
{
    m_Model.setAxis(o);
}

void Controller::SetScale(double scale)
{
    m_Model.SetScale(scale);
}

void Controller::RotationX(double angle)
{
    m_Model.RotationX(angle);
}

void Controller::RotationY(double angle)
{
    m_Model.RotationY(angle);
}

void Controller::RotationZ(double angle)
{
    m_Model.RotationZ(angle);
}
