#ifndef MODEL_3DVIEWER_H
#define MODEL_3DVIEWER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

namespace s21 {
    struct VertexCoordinates {
        double x = 0;
        double y = 0;
        double z = 0;
    };

    struct MaxMinValues
    {
        double minX_ = 100000000;
        double maxX_ = -100000000;
        double minY_ = 100000000;
        double maxY_ = -100000000;
        double minZ_ = 100000000;
        double maxZ_ = -100000000;
    };

    class Move {
        public:
        virtual ~Move() {}
        virtual void moveModel(double shift, std::vector<VertexCoordinates> &VertexArray, MaxMinValues &ExtremeValues) = 0;
    };

    class MoveX : public Move {
        public:
        void moveModel(double shift, std::vector<VertexCoordinates> &VertexArray, MaxMinValues &ExtremeValues);
    };

    class MoveY : public Move {
        public:
        void moveModel(double shift, std::vector<VertexCoordinates> &VertexArray, MaxMinValues &ExtremeValues);
    };

    class MoveZ : public Move {
        public:
        void moveModel(double shift, std::vector<VertexCoordinates> &VertexArray, MaxMinValues &ExtremeValues);
    };

    class ContextMove {
        protected:
        Move* Axis_;

        public:
        virtual ~ContextMove() {}
        virtual void useAxis(double shift) = 0;
        virtual void setAxis(Move* v) = 0;
    };
    

    class Model_3DViewer : public s21::ContextMove {
        private:
        std::vector<VertexCoordinates> VertexArray_;
        std::vector<std::vector<int>> FaceArray_;
        size_t CountVertex_ = 0;
        size_t CountFace_ = 0;
        MaxMinValues ExtremeValues;
        int MaxFace = 0;


        public:
        //  -------------------------------Parser---------------------------- //
        int ObjParser(std::string FileName);
        std::vector<std::string> SplitStringBySpace(std::string line);
        VertexCoordinates FromStringToDouble(std::vector<std::string> numbers_vector, int& error);
        std::vector<int> FromStringToInt(std::vector<std::string> numbers_vector, int& error);
        void SetMaxMin();
        void SetDefaultMaxMin();
        void ClearModel();
        
        //  ----------------------------Calculation-------------------------- //

        void SetScaleDefault();
        void SetScale(double scale);

        void RotationX(double angle);
        void RotationY(double angle);
        void RotationZ(double angle);

        void useAxis(double shift);
        void setAxis(Move* o);

        //  -----------------------------Accessors--------------------------- //
        size_t GetCountFace();
        size_t GetCountVertex();
        size_t GetCounrFaceLine(size_t numberLine);
        VertexCoordinates GetVertexFromFace(size_t row, size_t col);
        VertexCoordinates GetVertexFromFace(int index);
        //  -------------------------------Helper---------------------------- //
        void PrintVertexArray();
        void PrintFaceArray();
        void PrintVertexFromFace();

        friend class MoveX;
        friend class MoveY;
        friend class MoveZ;
    };

}

#endif