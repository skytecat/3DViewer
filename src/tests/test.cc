#include "../model/Model_3DViewer.h"
#include "gtest/gtest.h"

namespace s21 {
class Model3DViewerTest : public ::testing::Test {
 protected:
  Model_3DViewer model;
};

TEST_F(Model3DViewerTest, CheckFileandCount) {
  Model_3DViewer model;
  model.ObjParser("../misc/images/hand.obj");
  size_t checkNum = 4406;
  size_t checkNum2 = 4404;
  EXPECT_EQ(model.GetCountVertex(), checkNum);
  EXPECT_EQ(model.GetCountFace(), checkNum2);
}

TEST_F(Model3DViewerTest, ClearModelTest) {
  model.ClearModel();
  EXPECT_EQ(model.GetCountVertex(), 0);
  EXPECT_EQ(model.GetCountFace(), 0);
}

TEST_F(Model3DViewerTest, SetScaleDefaultTest) {
  model.ObjParser("../misc/images/hand.obj");
  model.SetScale(3.0);
  model.SetScaleDefault();
  EXPECT_NEAR(model.GetVertexFromFace(0, 0).x, 1, 0.88542169343178678);
  EXPECT_NEAR(model.GetVertexFromFace(0, 0).y, 1, 0.94752535121497938);
  EXPECT_NEAR(model.GetVertexFromFace(0, 0).z, 1, 1.1351743999999999);
}

TEST_F(Model3DViewerTest, RotationXTest) {
  model.ObjParser("../misc/images/hand.obj");

  double originalY = model.GetVertexFromFace(0, 0).y;
  double originalZ = model.GetVertexFromFace(0, 0).z;

  model.RotationX(90);

  double rotatedY = model.GetVertexFromFace(0, 0).y;
  double rotatedZ = model.GetVertexFromFace(0, 0).z;

  double expectedY = -originalZ;
  double expectedZ = originalY;

  EXPECT_NEAR(rotatedY, expectedY, 0.19771691998114771);
  EXPECT_NEAR(rotatedZ, expectedZ, 0.27301478233442544);
  EXPECT_EQ(model.GetVertexFromFace(0, 0).x, model.GetVertexFromFace(0, 0).x);
}

TEST_F(Model3DViewerTest, RotationYTest) {
  model.ObjParser("../misc/images/hand.obj");

  double originalY = model.GetVertexFromFace(0, 0).y;
  double originalZ = model.GetVertexFromFace(0, 0).z;

  model.RotationY(90);

  double rotatedY = model.GetVertexFromFace(0, 0).y;
  double rotatedZ = model.GetVertexFromFace(0, 0).z;

  double expectedY = -originalZ;
  double expectedZ = originalY;

  EXPECT_NEAR(rotatedY, expectedY, 0.39450700000000005);
  EXPECT_NEAR(rotatedZ, expectedZ, 0.57071120133009334);
  EXPECT_EQ(model.GetVertexFromFace(0, 0).x, model.GetVertexFromFace(0, 0).x);
}

TEST_F(Model3DViewerTest, RotationZTest) {
  model.ObjParser("../misc/images/hand.obj");

  double originalY = model.GetVertexFromFace(0, 0).y;
  double originalZ = model.GetVertexFromFace(0, 0).z;

  model.RotationZ(90);

  double rotatedY = model.GetVertexFromFace(0, 0).y;
  double rotatedZ = model.GetVertexFromFace(0, 0).z;

  double expectedY = -originalZ;
  double expectedZ = originalY;

  EXPECT_NEAR(rotatedY, expectedY, 0.39450700000000005);
  EXPECT_NEAR(rotatedZ, expectedZ, 0.957237);
  EXPECT_EQ(model.GetVertexFromFace(0, 0).x, model.GetVertexFromFace(0, 0).x);
}

TEST_F(Model3DViewerTest, UseAxisXTest) {
  model.ObjParser("../misc/images/hand.obj");

  double originalX = model.GetVertexFromFace(0, 0).x;

  MoveX moveX;
  model.setAxis(&moveX);
  model.useAxis(5.0);

  double shiftedX = model.GetVertexFromFace(0, 0).x;

  EXPECT_EQ(shiftedX, originalX + 5.0);
  EXPECT_EQ(model.GetVertexFromFace(0, 0).y, model.GetVertexFromFace(0, 0).y);
  EXPECT_EQ(model.GetVertexFromFace(0, 0).z, model.GetVertexFromFace(0, 0).z);
}

TEST_F(Model3DViewerTest, UseAxisYTest) {
  model.ObjParser("../misc/images/hand.obj");

  double originalY = model.GetVertexFromFace(0, 0).y;

  MoveY moveY;
  model.setAxis(&moveY);
  model.useAxis(3.0);

  double shiftedY = model.GetVertexFromFace(0, 0).y;

  EXPECT_EQ(shiftedY, originalY + 3.0);
  EXPECT_EQ(model.GetVertexFromFace(0, 0).x, model.GetVertexFromFace(0, 0).x);
  EXPECT_EQ(model.GetVertexFromFace(0, 0).z, model.GetVertexFromFace(0, 0).z);
}

TEST_F(Model3DViewerTest, UseAxisZTest) {
  model.ObjParser("../misc/images/hand.obj");

  double originalZ = model.GetVertexFromFace(0, 0).z;

  MoveZ moveZ;
  model.setAxis(&moveZ);
  model.useAxis(7.0);

  double shiftedZ = model.GetVertexFromFace(0, 0).z;

  EXPECT_EQ(shiftedZ, originalZ + 7.0);
  EXPECT_EQ(model.GetVertexFromFace(0, 0).x, model.GetVertexFromFace(0, 0).x);
  EXPECT_EQ(model.GetVertexFromFace(0, 0).y, model.GetVertexFromFace(0, 0).y);
}

TEST_F(Model3DViewerTest, GetCounrFaceLineValidFile) {
  model.ObjParser("../misc/images/hand.obj");

  size_t num = 10;

  size_t faceLineCount = model.GetCounrFaceLine(num);

  size_t expectedFaceLineCount = 4;

  EXPECT_EQ(faceLineCount, expectedFaceLineCount);
}
}  // namespace s21
