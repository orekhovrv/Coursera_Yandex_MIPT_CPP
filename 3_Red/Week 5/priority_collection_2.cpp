#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
//#include <memory>
#include <set>
#include <utility>
#include <map>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    /* тип, используемый для идентификаторов */
    using Id = int;

    // Добавить объект с нулевым приоритетом с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        priority_ids.insert(pair(new_priority, new_id));
        elements[new_id] = pair(move(object), new_priority);
        return new_id++;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(
            ObjInputIt range_begin,
            ObjInputIt range_end,
            IdOutputIt ids_begin
    ) {
        while(range_begin != range_end) {
            *ids_begin++ = Add(move(*range_begin++));
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        return elements.find(id) != elements.end();
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const{
        return elements[id].first;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id){
        priority_ids.erase(pair(elements[id].second++, id));
        priority_ids.insert(pair(elements[id].second, id));
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const{
        return elements[prev(priority_ids.end())->second];
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax(){
        const auto max_priority_iterator = prev(priority_ids.end());
        pair<T, int>& result = elements[max_priority_iterator->second];
        priority_ids.erase(max_priority_iterator);
        return move(result);
    }

private:
    int new_id = 0;
    const int new_priority = 0;

    using PriorityId = pair<int, Id>;
    using ElementPriority = pair<T, int>;

    set<PriorityId> priority_ids;
    map<Id, ElementPriority> elements;
};



class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
