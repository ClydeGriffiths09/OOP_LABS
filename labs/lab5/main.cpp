#include <iostream>

#include "memory_resource.hpp"
#include "vector.hpp"

int main() {
    DynamicMemoryResource my_resource;
    Vector<int> vec(&my_resource);
    vec.PushBack(42);
    vec.PushBack(100);
    vec.PushBack(31);
    vec.PushBack(42);
    vec.PushBack(100);
    vec.PushBack(31);
    vec.PushBack(42);
    vec.PushBack(100);
    vec.PushBack(31);
    vec.PushBack(42);
    vec.PushBack(100);
    vec.PushBack(31);
}