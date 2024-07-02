#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T>
SimpleVector<T>::SimpleVector() : begin_(nullptr), end_(nullptr), memory_end_(nullptr) {};

template<typename T>
SimpleVector<T>::SimpleVector(size_t size) {
    begin_ = new T[size];
    end_ = begin_;
    memory_end_ = begin_ + size;
}

template<typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] begin_;
}

template<typename T>
void SimpleVector<T>::PushBack(const T &value) {
    if (Size() == Capacity()) {
        AddMemory();
        PushBack(value);
    } else {
        begin_[Size()] = value;
        end_++;
    }
}

template<typename T>
void SimpleVector<T>::AddMemory() {
    T* new_begin = new T[Capacity() * 2];
    copy(begin_, end_, new_begin);
    end_ = new_begin + Size();
    memory_end_ = new_begin + Capacity();
    begin_ = new_begin;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const {
    return memory_end_ - begin_;
}

template<typename T>
size_t SimpleVector<T>::Size() const {
    return memory_end_ - end_;
}

template<typename T>
T *SimpleVector<T>::end() {
    return end_;
}

template<typename T>
T *SimpleVector<T>::begin() {
    return begin_;
}

template<typename T>
T &SimpleVector<T>::operator[](size_t index) {
    return begin_[index];
}




void TestConstruction() {
    SimpleVector<int> empty;
    ASSERT_EQUAL(empty.Size(), 0u);
    ASSERT_EQUAL(empty.Capacity(), 0u);
    ASSERT(empty.begin() == empty.end());

    SimpleVector<string> five_strings(5);
    ASSERT_EQUAL(five_strings.Size(), 5u);
    ASSERT(five_strings.Size() <= five_strings.Capacity());
    for (auto& item : five_strings) {
        ASSERT(item.empty());
    }
    five_strings[2] = "Hello";
    ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
    SimpleVector<int> v;
    for (int i = 10; i >= 1; --i) {
        v.PushBack(i);
        ASSERT(v.Size() <= v.Capacity());
    }
    sort(begin(v), end(v));

    const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQUAL(v.Size(), expected.size());
    ASSERT(equal(begin(v), end(v), begin(expected)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestConstruction);
    RUN_TEST(tr, TestPushBack);
    return 0;
}
