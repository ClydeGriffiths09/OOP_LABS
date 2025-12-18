#include <gtest/gtest.h>
#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"
#include "vector.hpp"
#include "exceptions.hpp"

using namespace figure;
using namespace vector;

// --- Тесты для Rectangle<double> ---
TEST(RectangleTest, ConstructorValidPoints) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    EXPECT_NO_THROW(Rectangle<double> r(p1, p2, p3, p4));
}

TEST(RectangleTest, ConstructorInvalidPoints) {
    Point<double> p1(0.0, 0.0), p2(0.0, 0.0), p3(2.0, 2.0), p4(0.0, 2.0);
    EXPECT_THROW(Rectangle<double> r(p1, p2, p3, p4), exceptions::InvalidPointsException);
}

TEST(RectangleTest, DefaultConstructor) {
    Rectangle<double> r;
    EXPECT_DOUBLE_EQ(r.Area(), 1.0);
}

TEST(RectangleTest, Center) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r(p1, p2, p3, p4);
    Point<double> center = r.Center();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RectangleTest, Area) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(r.Area(), 8.0);
}

TEST(RectangleTest, DoubleCast) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 8.0);
}

TEST(RectangleTest, Equality) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r1(p1, p2, p3, p4);
    Rectangle<double> r2(p1, p2, p3, p4);
    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 != r2);

    Point<double> p5(0.0, 0.0), p6(0.0, 3.0), p7(3.0, 3.0), p8(3.0, 0.0);
    Rectangle<double> r3(p5, p6, p7, p8);
    EXPECT_FALSE(r1 == r3);
}

TEST(RectangleTest, CopyConstructor) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r1(p1, p2, p3, p4);
    Rectangle<double> r2 = r1;
    EXPECT_DOUBLE_EQ(r2.Area(), 8.0);
    EXPECT_TRUE(r1 == r2);
}

TEST(RectangleTest, AssignmentOperator) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r1(p1, p2, p3, p4);
    Rectangle<double> r2;
    r2 = r1;
    EXPECT_DOUBLE_EQ(r2.Area(), 8.0);
    EXPECT_TRUE(r1 == r2);
}

// --- Тесты для Square<double> ---
TEST(SquareTest, ConstructorValidPoints) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(2.0, 2.0), p4(2.0, 0.0);
    EXPECT_NO_THROW(Square<double> s(p1, p2, p3, p4));
}

TEST(SquareTest, ConstructorInvalidPoints) {
    Point<double> p1(0.0, 0.0), p2(3.0, 0.0), p3(3.0, 3.0), p4(0.0, 2.0);
    EXPECT_THROW(Square<double> s(p1, p2, p3, p4), exceptions::InvalidPointsException);
}

TEST(SquareTest, Center) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(2.0, 2.0), p4(2.0, 0.0);
    Square<double> s(p1, p2, p3, p4);
    Point<double> center = s.Center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(SquareTest, Area) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(2.0, 2.0), p4(2.0, 0.0);
    Square<double> s(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(s.Area(), 4.0);
}

// --- Тесты для Triangle<double> ---
TEST(TriangleTest, ConstructorValidPoints) {
    Point<double> p1(0.0, 0.0), p2(4.0, 0.0), p3(0.0, 3.0);
    EXPECT_NO_THROW(Triangle<double> t(p1, p2, p3));
}

TEST(TriangleTest, ConstructorInvalidPoints) {
    Point<double> p1(0.0, 0.0), p2(0.0, 0.0), p3(2.0, 2.0);
    EXPECT_THROW(Triangle<double> t(p1, p2, p3), exceptions::InvalidPointsException);

    Point<double> p4(0.0, 0.0), p5(1.0, 1.0), p6(2.0, 2.0);
    EXPECT_THROW(Triangle<double> t(p4, p5, p6), exceptions::InvalidPointsException);
}

TEST(TriangleTest, Center) {
    Point<double> p1(0.0, 0.0), p2(4.0, 0.0), p3(0.0, 3.0);
    Triangle<double> t(p1, p2, p3);
    Point<double> center = t.Center();
    EXPECT_DOUBLE_EQ(center.x, 4.0 / 3.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(TriangleTest, Area) {
    Point<double> p1(0.0, 0.0), p2(4.0, 0.0), p3(0.0, 3.0);
    Triangle<double> t(p1, p2, p3);
    EXPECT_DOUBLE_EQ(t.Area(), 6.0);
}

TEST(TriangleTest, Equality) {
    Point<double> p1(0.0, 0.0), p2(4.0, 0.0), p3(0.0, 3.0);
    Triangle<double> t1(p1, p2, p3);
    Triangle<double> t2(p1, p2, p3);
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 != t2);

    Point<double> p4(1.0, 1.0), p5(6.0, 1.0), p6(1.0, 4.0);
    Triangle<double> t3(p4, p5, p6);
    EXPECT_FALSE(t1 == t3);
}

// --- Тесты для Vector с разными типами фигур ---
TEST(VectorTest, FigureDoubleVector) {
    using FigPtr = std::shared_ptr<Figure<double>>;
    Vector<FigPtr> v;

    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    auto rect = std::make_shared<Rectangle<double>>(p1, p2, p3, p4);
    v.PushBack(rect);

    Point<double> p5(0.0, 0.0), p6(2.0, 0.0), p7(2.0, 2.0), p8(0.0, 2.0);
    auto sq = std::make_shared<Square<double>>(p5, p6, p7, p8);
    v.PushBack(sq);

    Point<double> p9(0.0, 0.0), p10(4.0, 0.0), p11(0.0, 3.0);
    auto tri = std::make_shared<Triangle<double>>(p9, p10, p11);
    v.PushBack(tri);

    EXPECT_EQ(v.Size(), 3);

    EXPECT_DOUBLE_EQ(v.TotalAreas<double>(), 8.0 + 4.0 + 6.0);

    for (size_t i = 0; i < v.Size(); ++i) {
        auto fig = v[i];
        EXPECT_DOUBLE_EQ(fig->Area(), static_cast<double>(*fig));
    }

    v.Erase(0);
    EXPECT_EQ(v.Size(), 2);
}

TEST(VectorTest, RectangleDoubleVector) {
    using RectPtr = std::shared_ptr<Rectangle<double>>;
    Vector<RectPtr> v;

    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    auto r1 = std::make_shared<Rectangle<double>>(p1, p2, p3, p4);
    v.PushBack(r1);

    Point<double> p5(1.0, 1.0), p6(1.0, 3.0), p7(5.0, 3.0), p8(5.0, 1.0);
    auto r2 = std::make_shared<Rectangle<double>>(p5, p6, p7, p8);
    v.PushBack(r2);

    EXPECT_EQ(v.Size(), 2);
    EXPECT_DOUBLE_EQ(v[0]->Area(), 8.0);
    EXPECT_DOUBLE_EQ(v[1]->Area(), 8.0);

    EXPECT_DOUBLE_EQ(v.TotalAreas<double>(), 16.0);

    v.PopBack();
    EXPECT_EQ(v.Size(), 1);
}

TEST(VectorTest, SquareDoubleVector) {
    using SqPtr = std::shared_ptr<Square<double>>;
    Vector<SqPtr> v;

    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(2.0, 2.0), p4(2.0, 0.0);
    auto s1 = std::make_shared<Square<double>>(p1, p2, p3, p4);
    v.PushBack(s1);

    Point<double> p5(1.0, 1.0), p6(1.0, 3.0), p7(3.0, 3.0), p8(3.0, 1.0);
    auto s2 = std::make_shared<Square<double>>(p5, p6, p7, p8);
    v.PushBack(s2);

    EXPECT_EQ(v.Size(), 2);
    EXPECT_DOUBLE_EQ(v[0]->Area(), 4.0);
    EXPECT_DOUBLE_EQ(v[1]->Area(), 4.0);

    EXPECT_DOUBLE_EQ(v.TotalAreas<double>(), 8.0);
}

TEST(VectorTest, TriangleDoubleVector) {
    using TriPtr = std::shared_ptr<Triangle<double>>;
    Vector<TriPtr> v;

    Point<double> p1(0.0, 0.0), p2(4.0, 0.0), p3(0.0, 3.0);
    auto t1 = std::make_shared<Triangle<double>>(p1, p2, p3);
    v.PushBack(t1);

    Point<double> p4(1.0, 1.0), p5(5.0, 1.0), p6(1.0, 4.0);
    auto t2 = std::make_shared<Triangle<double>>(p4, p5, p6);
    v.PushBack(t2);

    EXPECT_EQ(v.Size(), 2);
    EXPECT_DOUBLE_EQ(v[0]->Area(), 6.0);
    EXPECT_DOUBLE_EQ(v[1]->Area(), 6.0);

    EXPECT_DOUBLE_EQ(v.TotalAreas<double>(), 12.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}