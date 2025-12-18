#include <gtest/gtest.h>
#include "eleven.h"

TEST(ElevenTest, DefaultConstructor) {
    eleven::Eleven e;
    eleven::Eleven expected("0");
    EXPECT_TRUE(e.Equal(expected));
}

TEST(ElevenTest, SizeConstructor) {
    eleven::Eleven e1(3, 5);
    eleven::Eleven expected1({5, 5, 5});
    EXPECT_TRUE(e1.Equal(expected1));
}

TEST(ElevenTest, StringConstructor) {
    eleven::Eleven e1("123");
    eleven::Eleven expected1("123");
    EXPECT_TRUE(e1.Equal(expected1));
    
    EXPECT_THROW(eleven::Eleven e2("12G3"), exceptions::ElevenException);
}

TEST(ElevenTest, CopyConstructor) {
    eleven::Eleven e1("A98");
    eleven::Eleven e2(e1);
    EXPECT_TRUE(e1.Equal(e2));
}

TEST(ElevenTest, AddMethod) {
    eleven::Eleven e1("123");
    eleven::Eleven e2("456");
    eleven::Eleven result = eleven::Eleven::Add(e1, e2);
    eleven::Eleven expected("579");
    EXPECT_TRUE(result.Equal(expected));
}

TEST(ElevenTest, SubMethod) {
    eleven::Eleven e1("6A");
    eleven::Eleven e2("37");
    eleven::Eleven result = eleven::Eleven::Sub(e1, e2);
    eleven::Eleven expected("33");
    EXPECT_TRUE(result.Equal(expected));
    
    EXPECT_THROW(eleven::Eleven::Sub(eleven::Eleven("50"), eleven::Eleven("100")), exceptions::ElevenException);
}

TEST(ElevenTest, ComparisonMethods) {
    eleven::Eleven e1("100");
    eleven::Eleven e2("A0");
    eleven::Eleven e3("100");
    
    EXPECT_TRUE(e1.GreaterThan(e2));
    EXPECT_TRUE(e2.LessThan(e1));
    EXPECT_TRUE(e1.Equal(e3));
}

TEST(ElevenTest, CopyMethod) {
    eleven::Eleven e1("A98");
    eleven::Eleven e2;
    e2.Copy(e1);
    EXPECT_TRUE(e1.Equal(e2));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}