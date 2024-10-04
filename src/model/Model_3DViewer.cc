#include "Model_3DViewer.h"

namespace s21 {

     //  -------------------------------Parser---------------------------- //

    int Model_3DViewer::ObjParser(std::string FileName) {
        int error = 0;
        std::ifstream ObjFile;
        ObjFile.open(FileName.c_str());
        if (ObjFile.is_open()) {
            std::string line;
            std::vector<std::string> numbers_vector;
            while (std::getline(ObjFile, line) && !error) {
                if (line[0] == 'v' && line[1] == ' ') {
                    numbers_vector = SplitStringBySpace(line);
                    VertexArray_.push_back(FromStringToDouble(numbers_vector, error));
                    SetMaxMin();
                    CountVertex_++;
                }
                else if (line[0] == 'f' && line[1] == ' ') {
                    numbers_vector = SplitStringBySpace(line);
                    std::vector<int> temp_face = FromStringToInt(numbers_vector, error);
                    FaceArray_.push_back(temp_face);
                    CountFace_++;
                }
            }
            ObjFile.close();
        }
        error = (((size_t)MaxFace) > (CountVertex_ - 1)) ? 1 : error;
        if (error) {
            ClearModel();
        }
        return error;
    }

    std::vector<std::string> Model_3DViewer::SplitStringBySpace(std::string line) {
        std::stringstream StreamOfLine(line);
        std::string number_str;
        std::vector<std::string> numbers_vector;
        while (StreamOfLine >> number_str) {
            numbers_vector.push_back(number_str);
        }
        return numbers_vector;
    }

    VertexCoordinates Model_3DViewer::FromStringToDouble(std::vector<std::string> numbers_vector, int& error) {
        VertexCoordinates Vertex;
        std::string::size_type sz = 0;
        try {
            Vertex.x = std::stod(numbers_vector[1], &sz);
            Vertex.y = std::stod(numbers_vector[2], &sz);
            Vertex.z = std::stod(numbers_vector[3], &sz);
            }
        catch (const std::invalid_argument& e) {
            error = 1;
        }
        catch (const std::out_of_range& e) {
            error = 1;
        }
        return Vertex;
    }

    std::vector<int> Model_3DViewer::FromStringToInt(std::vector<std::string> numbers_vector, int& error) {
        std::vector<int> parsed_int;
        std::vector<int> temp;
        std::string number_str;
        size_t e = 0;
        const char split_char = '/';
        for (size_t i = 1; i < numbers_vector.size(); i++) {
            std::stringstream StreamOfLine(numbers_vector[i]);
            while (!StreamOfLine.eof()) {
                getline(StreamOfLine, number_str, split_char);
                if (number_str != "") {
                    try {
                        int int_num = std::stoi(number_str, &e);
                        temp.push_back(int_num);
                    }
                    catch (const std::invalid_argument& e) {
                        error = 1;
                    }
                    catch (const std::out_of_range& e) {
                        error = 1;
                    }
               }
            }
            parsed_int.push_back(temp[0] - 1);
            MaxFace = ((temp[0] - 1) > MaxFace) ? (temp[0] - 1) : MaxFace;
            temp.clear();
        }
        return parsed_int;
    }

    void Model_3DViewer::SetMaxMin() {
        if (VertexArray_[CountVertex_].x > ExtremeValues.maxX_) {
            ExtremeValues.maxX_ = VertexArray_[CountVertex_].x;
        }
        else if (VertexArray_[CountVertex_].x < ExtremeValues.minX_) {
            ExtremeValues.minX_ = VertexArray_[CountVertex_].x;
        }
        if (VertexArray_[CountVertex_].y > ExtremeValues.maxY_) {
            ExtremeValues.maxY_ = VertexArray_[CountVertex_].y;
        }
        else if (VertexArray_[CountVertex_].y < ExtremeValues.minY_) {
            ExtremeValues.minY_ = VertexArray_[CountVertex_].y;
        }
        if (VertexArray_[CountVertex_].z > ExtremeValues.maxZ_) {
            ExtremeValues.maxZ_ = VertexArray_[CountVertex_].y;
        }
        else if (VertexArray_[CountVertex_].z < ExtremeValues.minZ_) {
            ExtremeValues.minZ_ = VertexArray_[CountVertex_].z;
        }
    }

    void Model_3DViewer::SetDefaultMaxMin() {
        ExtremeValues.minX_ = 100000000;
        ExtremeValues.maxX_ = -100000000;
        ExtremeValues.minY_ = 100000000;
        ExtremeValues.maxY_ = -100000000;
        ExtremeValues.minZ_ = 100000000;
        ExtremeValues.maxZ_ = -100000000;
    }

    void Model_3DViewer::ClearModel() {
        VertexArray_.clear();
        for (auto& row : FaceArray_) {
            row.clear();
        }
        FaceArray_.clear();
        CountVertex_ = 0;
        CountFace_ = 0; 
        MaxFace = 0;
        SetDefaultMaxMin();
    }

    //  -----------------------------Accessors--------------------------- //

    size_t Model_3DViewer::GetCountFace() {
        return CountFace_;
    }

    size_t Model_3DViewer::GetCountVertex() {
        return CountVertex_;
    }

    size_t Model_3DViewer::GetCounrFaceLine(size_t numberLine) {
        return FaceArray_[numberLine].size();
    }

    VertexCoordinates Model_3DViewer::GetVertexFromFace(size_t row, size_t col) {
        return VertexArray_[FaceArray_[row][col]];
    }

    VertexCoordinates Model_3DViewer::GetVertexFromFace(int index) {
        return VertexArray_[index];
    }

    //  ----------------------------Calculation-------------------------- //

    void Model_3DViewer::SetScaleDefault() {
        double diff = 0;
        double diffArray[] = {ExtremeValues.maxX_ - ExtremeValues.minX_, ExtremeValues.maxY_ - ExtremeValues.minY_, ExtremeValues.maxZ_ - ExtremeValues.minZ_};
        for (int i = 0; i < 3; i++) {
            if (abs(diffArray[i]) > diff) {
                diff  = abs(diffArray[i]);
            }
        }
        if (diff > 1) {
            SetScale((double)0.8 / diff);
        }
    }

    void Model_3DViewer::SetScale(double scale) {
        for (size_t i = 0; i < VertexArray_.size(); i++) {
            VertexArray_[i].x *= scale;
            VertexArray_[i].y *= scale;
            VertexArray_[i].z *= scale;
        }
        ExtremeValues.maxX_ *= scale;
        ExtremeValues.minX_ *= scale;
        ExtremeValues.maxY_ *= scale;
        ExtremeValues.minY_ *= scale;
        ExtremeValues.maxZ_ *= scale;
        ExtremeValues.minZ_ *= scale;
    }

    void Model_3DViewer::RotationX(double angle) {
        for (size_t i = 0; i < VertexArray_.size(); i++) {
            double tempY = VertexArray_[i].y;
            double tempZ = VertexArray_[i].z;
            VertexArray_[i].y = tempY * cos(angle) - tempZ * sin(angle);
            VertexArray_[i].z = tempY * sin(angle) + tempZ * cos(angle);
        }
    }
    
    void Model_3DViewer::RotationY(double angle) {
        for (size_t i = 0; i < VertexArray_.size(); i++) {
            double tempX = VertexArray_[i].x;
            double tempZ = VertexArray_[i].z;
            VertexArray_[i].x = tempX * cos(angle) - tempZ * sin(angle);
            VertexArray_[i].z = tempX * sin(angle) + tempZ * cos(angle);
        }
    }
    
    void Model_3DViewer::RotationZ(double angle) {
        for (size_t i = 0; i < VertexArray_.size(); i++) {
            double tempX = VertexArray_[i].x;
            double tempY = VertexArray_[i].y;
            VertexArray_[i].x = tempX * cos(angle) - tempY * sin(angle);
            VertexArray_[i].y = tempX * sin(angle) + tempY * cos(angle);
        }
    }

    void Model_3DViewer::useAxis(double shift) {
        Axis_->moveModel(shift, VertexArray_, ExtremeValues);
    }

    void Model_3DViewer::setAxis(Move* o) {
        Axis_ = o;
    }

    void MoveX::moveModel(double shift, std::vector<VertexCoordinates> &VertexArray, MaxMinValues &ExtremeValues) {
        for (size_t i = 0; i < VertexArray.size(); i++) {
            VertexArray[i].x += shift;
        }
        ExtremeValues.maxX_ += shift;
        ExtremeValues.minX_ += shift;
    }

    void MoveY::moveModel(double shift, std::vector<VertexCoordinates> &VertexArray, MaxMinValues &ExtremeValues) {
        for (size_t i = 0; i < VertexArray.size(); i++) {
            VertexArray[i].y += shift;
        }
        ExtremeValues.maxY_ += shift;
        ExtremeValues.minY_ += shift;
    }

    void MoveZ::moveModel(double shift, std::vector<VertexCoordinates> &VertexArray, MaxMinValues &ExtremeValues) {
        for (size_t i = 0; i < VertexArray.size(); i++) {
            VertexArray[i].z += shift;
        }
        ExtremeValues.maxZ_ += shift;
        ExtremeValues.minZ_ += shift;
    }
}
