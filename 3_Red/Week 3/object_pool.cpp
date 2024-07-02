#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:

    //если есть хотя бы один освобождённый объект, то его надо перенести в множество выделенных и вернуть указатель на него в качестве результата функции
    //если же освобождённых объектов нет, то создаётся новый объект, помещается в множество выделенных, и указатель на него возвращается в качестве результата функции
    T* Allocate() {
        T* object = TryAllocate();
        return object != nullptr ? object : GetNewObject();
    }

    T* TryAllocate() {
        if (deallocated.size() == 0) {
            return nullptr;
        } else {
            T* object = deallocated.front();
            deallocated.pop();
            allocated.insert(object);
            return object;
        }
    }

    T* GetNewObject() {
        T* object = new T;
        allocated.insert(object);
        return object;
    }

    void Deallocate(T* object) {
        if (allocated.find(object) == end(allocated)) {
            throw invalid_argument("");
        } else {
            deallocated.push(object);
            allocated.erase(object);
        }
    }

    ~ObjectPool() {
        for (T* object: allocated) {
            delete object;
        }
        while (!deallocated.empty()) {
            T* object = deallocated.front();
            deallocated.pop();
            delete object;
        }
    }

private:
    // Добавьте сюда поля
    set<T*> allocated;
    queue<T*> deallocated;

};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
