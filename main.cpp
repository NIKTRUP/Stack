#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Type>
class Stack {
public:
    void Push(const Type& element) {
        elements_.push_back(element);
    }
    void Pop() {
        elements_.pop_back();
    }
    const Type& Peek() const {
        return elements_.back();
    }
    Type& Peek() {
        return elements_.back();
    }
    void Print() const {
        PrintRange(elements_.begin(), elements_.end());
    }
    uint64_t Size() const {
        return elements_.size();
    }
    bool IsEmpty() const {
        return elements_.empty();
    }

private:
    vector<Type> elements_;
};

// используем струкруту из элемента
// и минимума в стеке до дна стека до текущего элемента включительно
template <typename Type>
struct PairWithMin {
    Type element;
    Type minimum;
};

template <typename Type>
ostream& operator<<(ostream& out, const PairWithMin<Type>& pair_to_print) {
    out << pair_to_print.element;
    return out;
}

template <typename Type>
class StackMin {
public:
    void Push(const Type& new_element) {
        PairWithMin<Type> new_pair = {new_element, new_element};
        if (!elements_.IsEmpty() && new_pair.minimum > elements_.Peek().minimum) {
            new_pair.minimum = elements_.Peek().minimum;
        }
        elements_.Push(new_pair);
    }
    void Pop() {
        elements_.Pop();
    }
    const Type& Peek() const {
        return elements_.Peek().element;
    }
    Type& Peek() {
        return elements_.Peek().element;
    }
    void Print() const {
        elements_.Print();
    }
    uint64_t Size() const {
        return elements_.size();
    }
    bool IsEmpty() const {
        return elements_.IsEmpty();
    }
    const Type& PeekMin() const {
        return elements_.Peek().minimum;
    }
    Type& PeekMin() {
        return elements_.Peek().minimum;
    }

private:
    Stack<PairWithMin<Type>> elements_;
};

template <typename Type>
class SortedStack {
public:
    void Push(const Type& element) {
        if (elements_.IsEmpty()) {
            elements_.Push(element);
            return;
        }
        Type last_elem = elements_.Peek();
        if (element > last_elem) {
            elements_.Pop();
            Push(element);
            elements_.Push(last_elem);
        } else {
            elements_.Push(element);
        }
    }
    void Pop() {
        elements_.Pop();
    }
    const Type& Peek() const {
    return elements_.Peek();
    }
    Type& Peek() {
    return elements_.Peek();
    }
    void Print() const {
    elements_.Print();
    }
    uint64_t Size() const {
    return elements_.Size();
    }
    bool IsEmpty() const {
    return elements_.IsEmpty();
    }
private:
    Stack<Type> elements_;
};

int main() {
    {
        Stack<int> stack;
        for (uint32_t i = 0; i < 10; ++i) {
            stack.Push(i);
            stack.Print();
        }
        while (!stack.IsEmpty()) {
            stack.Pop();
            stack.Print();
        }
    }


    {
    StackMin<int> stack;
       vector<int> values(5);
       iota(values.begin(), values.end(), 1);
       random_shuffle(values.begin(), values.end());
       for (int i = 0; i < 5; ++i) {
           stack.Push(values[i]);
       }
       while (!stack.IsEmpty()) {
           stack.Print();
           cout << "Минимум = "s << stack.PeekMin() << endl;
           stack.Pop();
       }
    }

    std::cout << std::endl;

    {
        SortedStack<int> stack;
        vector<int> values(5);
        iota(values.begin(), values.end(), 1);
        random_shuffle(values.begin(), values.end());
        for (int i = 0; i < 5; ++i) {
            cout << "Вставляемый элемент = "s << values[i] << endl;
            stack.Push(values[i]);
            stack.Print();
        }
    }

    return 0;
}
