#include <gtest/gtest.h>
#include "rectangle.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "vector.h"
#include "exceptions.h"

using namespace figure;
using namespace vector;

TEST(RectangleTest, ConstructorValidPoints) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    EXPECT_NO_THROW(Rectangle r(p1, p2, p3, p4));
}

TEST(RectangleTest, ConstructorInvalidPoints) {
    Point p1(0, 0), p2(0, 0), p3(2, 2), p4(0, 2);
    EXPECT_THROW(Rectangle r(p1, p2, p3, p4), exceptions::InvalidPointsException);
}

TEST(RectangleTest, Center) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r(p1, p2, p3, p4);
    Point center = r.Center();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RectangleTest, Area) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(r.Area(), 8.0);
}

TEST(RectangleTest, DoubleCast) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 8.0);
}

TEST(RectangleTest, Equality) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r1(p1, p2, p3, p4);
    Rectangle r2(p1, p2, p3, p4);
    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 != r2);

    Point p5(0, 0), p6(3, 0), p7(3, 3), p8(0, 3);
    Rectangle r3(p5, p6, p7, p8);
    EXPECT_FALSE(r1 == r3);
}

TEST(RectangleTest, CopyConstructor) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r1(p1, p2, p3, p4);
    Rectangle r2 = r1;
    EXPECT_DOUBLE_EQ(r2.Area(), 8.0);
    EXPECT_TRUE(r1 == r2);
}

TEST(RectangleTest, AssignmentOperator) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r1(p1, p2, p3, p4);
    Rectangle r2;
    r2 = r1;
    EXPECT_DOUBLE_EQ(r2.Area(), 8.0);
    EXPECT_TRUE(r1 == r2);
}

TEST(RhombusTest, ConstructorValidPoints) {
    Point p1(0, 0), p2(2, 3), p3(4, 0), p4(2, -3);
    EXPECT_NO_THROW(Rhombus r(p1, p2, p3, p4));
}

TEST(RhombusTest, ConstructorInvalidPoints) {
    Point p1(0, 0), p2(0, 0), p3(2, 2), p4(0, 2);
    EXPECT_THROW(Rhombus r(p1, p2, p3, p4), exceptions::InvalidPointsException);
}

TEST(RhombusTest, ConstructorNotRhombus) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    EXPECT_THROW(Rhombus r(p1, p2, p3, p4), exceptions::InvalidPointsException);
}

TEST(RhombusTest, Center) {
    Point p1(0, 0), p2(2, 3), p3(4, 0), p4(2, -3);
    Rhombus r(p1, p2, p3, p4);
    Point center = r.Center();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 0.0);
}

TEST(RhombusTest, Area) {
    Point p1(0, 0), p2(3, 4), p3(6, 0), p4(3, -4);
    Rhombus r(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(r.Area(), 24.0);
}

TEST(RhombusTest, AreaSquareRhombus) {
    Point p1(0, 0), p2(2, 2), p3(4, 0), p4(2, -2);
    Rhombus r(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(r.Area(), 8.0);
}

TEST(RhombusTest, DoubleCast) {
    Point p1(0, 0), p2(3, 4), p3(6, 0), p4(3, -4);
    Rhombus r(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 24.0);
}

TEST(RhombusTest, Equality) {
    Point p1(0, 0), p2(2, 3), p3(4, 0), p4(2, -3);
    Rhombus r1(p1, p2, p3, p4);
    Rhombus r2(p1, p2, p3, p4);
    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 != r2);

    Point p5(1, 0), p6(3, 2), p7(5, 0), p8(3, -2);
    Rhombus r3(p5, p6, p7, p8);
    EXPECT_FALSE(r1 == r3);
}

TEST(RhombusTest, CopyConstructor) {
    Point p1(0, 0), p2(2, 3), p3(4, 0), p4(2, -3);
    Rhombus r1(p1, p2, p3, p4);
    Rhombus r2 = r1;
    EXPECT_TRUE(r1 == r2);
}

TEST(RhombusTest, AssignmentOperator) {
    Point p1(0, 0), p2(2, 3), p3(4, 0), p4(2, -3);
    Rhombus r1(p1, p2, p3, p4);
    Rhombus r2;
    r2 = r1;
    EXPECT_TRUE(r1 == r2);
}

TEST(RhombusTest, PerpendicularDiagonals) {
    Point p1(0, 0), p2(2, 3), p3(4, 0), p4(2, -3);
    Rhombus r(p1, p2, p3, p4);
    EXPECT_NO_THROW(Rhombus r(p1, p2, p3, p4));
}

TEST(TrapezoidTest, GeomCenter) {
    Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
    Trapezoid t(p1, p2, p3, p4);
    Point center = t.Center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 0.5);
}

TEST(TrapezoidTest, Area) {
    Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
    Trapezoid t(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(t.Area(), 1.5);
}

TEST(TrapezoidTest, DoubleCast) {
    Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
    Trapezoid t(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(static_cast<double>(t), 1.5);
}

TEST(TrapezoidTest, Equality) {
    Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
    Trapezoid t1(p1, p2, p3, p4);
    Trapezoid t2(p1, p2, p3, p4);
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 != t2);

    Point p5(0, 0), p6(3, 0), p7(2, 1), p8(1, 1);
    Trapezoid t3(p5, p6, p7, p8);
    EXPECT_FALSE(t1 == t3);
}

TEST(TrapezoidTest, CopyConstructor) {
    Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
    Trapezoid t1(p1, p2, p3, p4);
    Trapezoid t2 = t1;
    EXPECT_DOUBLE_EQ(t2.Area(), 1.5);
    EXPECT_TRUE(t1 == t2);
}

TEST(TrapezoidTest, AssignmentOperator) {
    Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
    Trapezoid t1(p1, p2, p3, p4);
    Trapezoid t2;
    t2 = t1;
    EXPECT_DOUBLE_EQ(t2.Area(), 1.5);
    EXPECT_TRUE(t1 == t2);
}

TEST(RhombusTest, GeomCenter) {
    Point p1(0, 0), p2(1, 1), p3(0, 2), p4(-1, 1);
    Rhombus r(p1, p2, p3, p4);
    Point center = r.Center();
    EXPECT_DOUBLE_EQ(center.x, 0.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(VectorTest, PushBackAndSize) {
    Vector v;
    Point p1(0, 0), p2(2, 0), p3(1.5, 1), p4(0.5, 1);
    Trapezoid* t = new Trapezoid(p1, p2, p3, p4);
    v.PushBack(t);
    EXPECT_EQ(v.Size(), 1);
    delete t;
}

TEST(PolymorphismTest, VirtualMethods) {
    Point tp1(0, 0), tp2(2, 0), tp3(1.5, 1), tp4(0.5, 1);
    Trapezoid* t = new Trapezoid(tp1, tp2, tp3, tp4);

    Point rp1(0, 0), rp2(1, 1), rp3(2, 0), rp4(1, -1);
    Rhombus* r = new Rhombus(rp1, rp2, rp3, rp4);

    Point rect_p1(0, 0), rect_p2(0, 3), rect_p3(2, 3), rect_p4(2, 0);
    Rectangle* rect = new Rectangle(rect_p1, rect_p2, rect_p3, rect_p4);

    Figure* f1 = t;
    EXPECT_DOUBLE_EQ(f1->Area(), 1.5);
    Point c1 = f1->Center();
    EXPECT_DOUBLE_EQ(c1.x, 1.0);
    EXPECT_DOUBLE_EQ(c1.y, 0.5);
    EXPECT_DOUBLE_EQ(static_cast<double>(*f1), 1.5);

    Figure* f2 = r;
    EXPECT_DOUBLE_EQ(f2->Area(), 2.0);
    Point c2 = f2->Center();
    EXPECT_DOUBLE_EQ(c2.x, 1.0);
    EXPECT_DOUBLE_EQ(c2.y, 0.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(*f2), 2.0);

    Figure* f3 = rect;
    EXPECT_DOUBLE_EQ(f3->Area(), 6.0);
    Point c3 = f3->Center();
    EXPECT_DOUBLE_EQ(c3.x, 1.0);
    EXPECT_DOUBLE_EQ(c3.y, 1.5);
    EXPECT_DOUBLE_EQ(static_cast<double>(*f3), 6.0);

    EXPECT_NE(f1->Area(), f2->Area());
    EXPECT_NE(f2->Area(), f3->Area());

    delete t;
    delete r;
    delete rect;
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}