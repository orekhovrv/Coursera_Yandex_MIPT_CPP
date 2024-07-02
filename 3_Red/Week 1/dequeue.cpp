// Условие
//Напишите шаблонный класс Deque, содержащий следующий набор методов:
//конструктор по умолчанию;
//константный метод Empty, возвращающий true, если дек не содержит ни одного элемента;
//константный метод Size, возвращающий количество элементов в деке;
//T& operator[](size_t index) и const T& operator[](size_t index) const;
//константный и неконстантный метод At(size_t index), генерирующий стандартное исключение out_of_range, если индекс больше или равен количеству элементов в деке;
//константные и неконстантные версии методов Front и Back, возвращающих ссылки на первый и последний элемент дека соответственно;
//методы PushFront и PushBack.
//Неконстантные версии методов должны позволять изменять соответствующий элемент дека.
//Для реализации заведите внутри класса Deque два вектора: в один осуществляйте вставку в методе PushFront, а в другой — в методе PushBack.

//Замечание
//Заголовочный файл, который вы пришлёте на проверку, не должен подключать файлы <list>, <deque>, <set>, <map>.
// Если у вас будет подключен один из этих файлов, вы получите ошибку компиляции.


#include <cstddef>
#include <stdexcept>
#include <vector>

template< typename T>
class Deque {
public:
    Deque() = default;

    bool Empty() const {
        return head.empty() && tail.empty();
    }

    size_t Size() const {
        return head.size() + tail.size();
    }

    T& operator[](size_t index) {
        return index < head.size() ?
            head[head.size() - index - 1] :
            tail[index - head.size()];
    }

    const T& operator[](size_t index) const {
        return index < head.size() ?
               head[head.size() - index - 1] :
               tail[index - head.size()];
    }

    T& At(size_t index) {
        CheckIndex(index);
        return *this[index];
    }

    const T& At(size_t index) const {
        CheckIndex(index);
        return *this[index];
    }

    T& Front() {
        return !head.empty() ? head.back() : tail.front();
    }

    const T& Front() const {
        return !head.empty() ? head.back() : tail.front();
    }

    T& Back() {
        return !tail.empty() ? tail.back() : head.front();
    }

    const T& Back() const {
        return !tail.empty() ? tail.back() : head.front();
    }

    void PushFront(const T& element) {
        head.push_back(element);
    }

    void PushBack(const T& element) {
        tail.push_back(element);
    }

private:
    std::vector<T> head, tail;
    // head is reversed


    void CheckIndex(size_t index) const {
        if (index >= Size())
            throw std::out_of_range("Index is out of range");
    }
};