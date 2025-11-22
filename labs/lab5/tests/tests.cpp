#include <gtest/gtest.h>
#include <memory_resource>
#include <thread>
#include <future>
#include <algorithm>
#include <string>

#include "vector.hpp"
#include "memory_resource.hpp"

struct Person {
    std::string name;
    int age;

    Person() = default;
    Person(const std::string& n, int a) : name(n), age(a) {}

    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "{name: \"" << p.name << "\", age: " << p.age << "}";
        return os;
    }
};

class VectorTest : public testing::Test {
protected:
    void SetUp() override {
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);
        vec.PushBack(4);
        vec.PushBack(5);
        ASSERT_EQ(vec.Size(), sz);
    }

    DynamicMemoryResource resource;
    Vector<int> vec{&resource};
    const size_t sz = 5;
};

TEST(MemoryResourceTest, VectorDefaultConstructor) {
    DynamicMemoryResource resource;
    Vector<int> vec(&resource);
    ASSERT_TRUE(vec.IsEmpty()) << "Default vector isn't empty!";
    ASSERT_EQ(vec.Size(), 0);
    ASSERT_EQ(vec.Capacity(), 0);
}

TEST(MemoryResourceTest, VectorPushBackSimple) {
    DynamicMemoryResource resource;
    Vector<int> vec(&resource);
    vec.PushBack(42);
    ASSERT_EQ(vec.Size(), 1);
    ASSERT_EQ(vec.Front(), 42);
    ASSERT_EQ(vec.Back(), 42);
}

TEST(MemoryResourceTest, VectorPopBackSimple) {
    DynamicMemoryResource resource;
    Vector<int> vec(&resource);
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PopBack();

    ASSERT_EQ(vec.Size(), 1);
    ASSERT_EQ(vec.Back(), 1);
}

TEST(MemoryResourceTest, VectorConstructorSizeDefaultValues) {
    DynamicMemoryResource resource;
    Vector<std::string> vec(5, &resource);
    ASSERT_EQ(vec.Size(), 5);
    for (size_t i = 0; i < vec.Size(); ++i) {
        ASSERT_TRUE(vec[i].empty());
    }
}

TEST(MemoryResourceTest, VectorConstructorWithInitList) {
    DynamicMemoryResource resource;
    Vector<int> vec({1, 2, 3, 4, 5}, &resource);
    ASSERT_EQ(vec.Size(), 5);
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}

TEST(MemoryResourceTest, VectorConstructorWithSizeAndValue) {
    DynamicMemoryResource resource;
    Vector<int> vec(5, 42, &resource);
    ASSERT_EQ(vec.Size(), 5);
    for (size_t i = 0; i < vec.Size(); ++i) {
        ASSERT_EQ(vec[i], 42);
    }
}

TEST_F(VectorTest, CopyConstructor) {
    Vector<int> copy = vec;
    ASSERT_NE(&vec, &copy) << "Copy constructor must do copy!";
    ASSERT_EQ(vec.Size(), copy.Size());
    for (size_t i = 0; i < vec.Size(); ++i) {
        ASSERT_EQ(vec[i], copy[i]);
    }
}

TEST_F(VectorTest, SelfAssignment) {
    std::thread thread([&](){
        vec = vec;
    });
    auto future = std::async(std::launch::async, &std::thread::join, &thread);
    ASSERT_LT(
        future.wait_for(std::chrono::seconds(1)),
        std::future_status::timeout
    ) << "There is infinity loop!";
}

TEST_F(VectorTest, IteratorRange) {
    ASSERT_EQ(std::distance(vec.Begin(), vec.End()), sz) << 
                  "Distance between begin and end iterators isn't equal size";
    
    int expected = 1;
    for (auto it = vec.Begin(); it != vec.End(); ++it) {
        ASSERT_EQ(*it, expected++);
    }
}

TEST_F(VectorTest, IteratorPostIncrement) {
    int expected = 1;
    for (auto it = vec.Begin(); it != vec.End(); it++) {
        ASSERT_EQ(*it, expected++);
    }
}

TEST_F(VectorTest, IteratorDereference) {
    auto it = vec.Begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
}

TEST_F(VectorTest, IteratorArrowOperator) {
    DynamicMemoryResource resource;
    Vector<Person> persons(&resource);
    persons.PushBack(Person("Alice", 30));
    
    auto it = persons.Begin();
    ASSERT_EQ(it->name, "Alice");
    ASSERT_EQ(it->age, 30);
}

TEST_F(VectorTest, FindFirst) {
    auto it = vec.Begin();
    ASSERT_EQ(it, vec.Find(1));
}

TEST_F(VectorTest, FindLast) {
    auto it = vec.Begin();
    std::advance(it, 4);
    ASSERT_EQ(it, vec.Find(5));
}

TEST_F(VectorTest, FindFail) {
    auto it = vec.End();
    ASSERT_EQ(it, vec.Find(999));
}

TEST_F(VectorTest, FindAll) {
    for (int i = 1; i <= 5; ++i) {
        auto it = vec.Find(i);
        ASSERT_NE(it, vec.End());
        ASSERT_EQ(*it, i);
    }
}

TEST_F(VectorTest, OperatorBrackets) {
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}

TEST_F(VectorTest, AtValidIndex) {
    ASSERT_EQ(vec.At(0), 1);
    ASSERT_EQ(vec.At(2), 3);
    ASSERT_EQ(vec.At(4), 5);
}

TEST_F(VectorTest, AtInvalidIndex) {
    EXPECT_THROW({
        vec.At(10);
    }, exceptions::InvalidIndex);
}

TEST_F(VectorTest, FrontAndBack) {
    ASSERT_EQ(vec.Front(), 1);
    ASSERT_EQ(vec.Back(), 5);
}

TEST(MemoryResourceTest, VectorFrontBackEmpty) {
    DynamicMemoryResource resource;
    Vector<int> vec(&resource);
    EXPECT_THROW({
        vec.Front();
    }, exceptions::VectorIsNull);
    EXPECT_THROW({
        vec.Back();
    }, exceptions::VectorIsNull);
}

TEST_F(VectorTest, Clear) {
    vec.Clear();
    ASSERT_TRUE(vec.IsEmpty());
    ASSERT_EQ(vec.Size(), 0);
}

TEST_F(VectorTest, ResizeIncrease) {
    vec.Resize(10);
    ASSERT_EQ(vec.Size(), 10);
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
    
}

TEST_F(VectorTest, ResizeDecrease) {
    vec.Resize(2);
    ASSERT_EQ(vec.Size(), 2);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);
}

TEST_F(VectorTest, ResizeWithValue) {
    vec.Resize(10, 42);
    ASSERT_EQ(vec.Size(), 10);
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
    for (int i = 5; i < 10; ++i) {
        ASSERT_EQ(vec[i], 42);
    }
}

TEST_F(VectorTest, Reserve) {
    size_t old_capacity = vec.Capacity();
    vec.Reserve(old_capacity + 10);
    ASSERT_GE(vec.Capacity(), old_capacity + 10);
    ASSERT_EQ(vec.Size(), sz); 
    
    
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}

TEST(MemoryResourceTest, VectorWithComplexType) {
    DynamicMemoryResource resource;
    Vector<Person> vec(&resource);

    vec.PushBack(Person("Alice", 30));
    vec.PushBack(Person("Bob", 25));

    ASSERT_EQ(vec.Size(), 2);
    EXPECT_EQ(vec[0].name, "Alice");
    EXPECT_EQ(vec[0].age, 30);
    EXPECT_EQ(vec[1].name, "Bob");
    EXPECT_EQ(vec[1].age, 25);
}

TEST(MemoryResourceTest, VectorCopyWithComplexType) {
    DynamicMemoryResource resource;
    Vector<Person> original(&resource);
    original.PushBack(Person("Alice", 30));
    original.PushBack(Person("Bob", 25));

    Vector<Person> copy(original);

    ASSERT_EQ(copy.Size(), 2);
    EXPECT_EQ(copy[0].name, "Alice");
    EXPECT_EQ(copy[0].age, 30);
    EXPECT_EQ(copy[1].name, "Bob");
    EXPECT_EQ(copy[1].age, 25);
}

TEST(MemoryResourceTest, VectorFindWithPerson) {
    DynamicMemoryResource resource;
    Vector<Person> vec(&resource);
    vec.PushBack(Person("Alice", 30));
    vec.PushBack(Person("Bob", 25));

    auto it = vec.Find(Person("Alice", 30));
    EXPECT_NE(it, vec.End());
    EXPECT_EQ(it->name, "Alice");
    EXPECT_EQ(it->age, 30);

    auto not_found = vec.Find(Person("Charlie", 40));
    EXPECT_EQ(not_found, vec.End());
}

TEST(MemoryResourceTest, VectorMoveConstructor) {
    DynamicMemoryResource resource;
    Vector<int> original(&resource);
    original.PushBack(1);
    original.PushBack(2);
    original.PushBack(3);
    
    size_t original_size = original.Size();
    int original_front = original.Front();
    
    Vector<int> moved = std::move(original);
    
    ASSERT_EQ(moved.Size(), original_size);
    ASSERT_EQ(moved.Front(), original_front);
    ASSERT_TRUE(original.IsEmpty());
    ASSERT_EQ(original.Size(), 0);
}

TEST(MemoryResourceTest, VectorMoveAssignment) {
    DynamicMemoryResource resource;
    Vector<int> original(&resource);
    original.PushBack(1);
    original.PushBack(2);
    original.PushBack(3);
    
    Vector<int> target(&resource);
    target.PushBack(10);
    target.PushBack(20);
    
    size_t original_size = original.Size();
    int original_front = original.Front();
    
    target = std::move(original);
    
    ASSERT_EQ(target.Size(), original_size);
    ASSERT_EQ(target.Front(), original_front);
    ASSERT_TRUE(original.IsEmpty());
    ASSERT_EQ(original.Size(), 0);
}

TEST(MemoryResourceTest, VectorMoveSelfAssignment) {
    DynamicMemoryResource resource;
    Vector<int> vec(&resource);
    vec.PushBack(1);
    vec.PushBack(2);
    
    size_t original_size = vec.Size();
    int original_front = vec.Front();
    
    vec = std::move(vec);
    
    ASSERT_EQ(vec.Size(), original_size);
    ASSERT_EQ(vec.Front(), original_front);
}

TEST_F(VectorTest, MoveConstructorPreservesContent) {
    size_t original_size = vec.Size();
    int original_front = vec.Front();
    
    Vector<int> moved = std::move(vec);
    
    ASSERT_EQ(moved.Size(), original_size);
    ASSERT_EQ(moved.Front(), original_front);
    
    int expected_values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(moved[i], expected_values[i]);
    }
    
    ASSERT_TRUE(vec.IsEmpty());
}

TEST(MemoryResourceTest, VectorMoveWithComplexType) {
    DynamicMemoryResource resource;
    Vector<Person> original(&resource);
    original.PushBack(Person("Alice", 30));
    original.PushBack(Person("Bob", 25));
    
    Vector<Person> moved = std::move(original);
    
    ASSERT_EQ(moved.Size(), 2);
    EXPECT_EQ(moved[0].name, "Alice");
    EXPECT_EQ(moved[0].age, 30);
    EXPECT_EQ(moved[1].name, "Bob");
    EXPECT_EQ(moved[1].age, 25);
    
    ASSERT_TRUE(original.IsEmpty());
}

TEST(MemoryResourceTest, VectorMultiplePushBack) {
    DynamicMemoryResource resource;
    Vector<int> vec(&resource);
    
    const int COUNT = 1000;
    for (int i = 0; i < COUNT; ++i) {
        vec.PushBack(i);
    }
    
    ASSERT_EQ(vec.Size(), COUNT);
    for (int i = 0; i < COUNT; ++i) {
        ASSERT_EQ(vec[i], i);
    }
}

TEST(MemoryResourceTest, VectorGetResource) {
    DynamicMemoryResource resource;
    Vector<int> vec(&resource);
    
    auto* res = vec.GetResource();
    ASSERT_EQ(res, &resource);
}

TEST(MemoryResourceTest, VectorOutOfRangeExceptions) {
    DynamicMemoryResource resource;
    Vector<int> vec(&resource);
    
    EXPECT_THROW(vec.At(0), exceptions::InvalidIndex);
    EXPECT_THROW(vec.Front(), exceptions::VectorIsNull);
    EXPECT_THROW(vec.Back(), exceptions::VectorIsNull);
    
    vec.PushBack(1);
    vec.PushBack(2);
    
    EXPECT_NO_THROW(vec.At(0));
    EXPECT_NO_THROW(vec.At(1));
    
    EXPECT_THROW(vec.At(2), exceptions::InvalidIndex);
    EXPECT_THROW(vec.At(100), exceptions::InvalidIndex);
}

TEST(MemoryResourceTest, VectorWithString) {
    DynamicMemoryResource resource;
    Vector<std::string> vec(&resource);
    
    vec.PushBack("hello");
    vec.PushBack("world");
    vec.PushBack("test");
    
    ASSERT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec[0], "hello");
    EXPECT_EQ(vec[1], "world");
    EXPECT_EQ(vec[2], "test");
    
    auto it = vec.Find("world");
    EXPECT_NE(it, vec.End());
    EXPECT_EQ(*it, "world");
}

TEST(MemoryResourceTest, VectorWithDouble) {
    DynamicMemoryResource resource;
    Vector<double> vec(&resource);
    
    vec.PushBack(3.14);
    vec.PushBack(2.71);
    vec.PushBack(1.41);
    
    ASSERT_EQ(vec.Size(), 3);
    EXPECT_DOUBLE_EQ(vec[0], 3.14);
    EXPECT_DOUBLE_EQ(vec[1], 2.71);
    EXPECT_DOUBLE_EQ(vec[2], 1.41);
}

TEST(MemoryResourceTest, VectorEmptyAfterMove) {
    DynamicMemoryResource resource;
    Vector<int> original(&resource);
    original.PushBack(1);
    original.PushBack(2);
    
    Vector<int> moved = std::move(original);
    
    ASSERT_TRUE(original.IsEmpty());
    ASSERT_EQ(original.Size(), 0);
    ASSERT_EQ(original.Capacity(), 0);
    
    
    EXPECT_NO_THROW(original.PushBack(3));
    ASSERT_EQ(original.Size(), 1);
    ASSERT_EQ(original.Front(), 3);
}

TEST(MemoryResourceTest, VectorLargeReserve) {
    DynamicMemoryResource resource;
    Vector<int> vec(&resource);
    
    const size_t LARGE_SIZE = 10000;
    vec.Reserve(LARGE_SIZE);
    
    ASSERT_GE(vec.Capacity(), LARGE_SIZE);
    ASSERT_EQ(vec.Size(), 0); 
    
    
    for (size_t i = 0; i < LARGE_SIZE; ++i) {
        vec.PushBack(static_cast<int>(i));
    }
    
    ASSERT_EQ(vec.Size(), LARGE_SIZE);
    for (size_t i = 0; i < LARGE_SIZE; ++i) {
        ASSERT_EQ(vec[i], static_cast<int>(i));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}