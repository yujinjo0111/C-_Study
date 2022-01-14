#include <algorithm>
#include <iostream>
using namespace std;


template <class T>
class Stack
{
private:
    T* stack;
    int top, capacity;
    
public:
    Stack(int stackCapacity = 10);
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& item);
    void Pop();
};

// 1차원 배열의 크기를 늘리는 함수
template <class T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize) 
{
    if (newSize < 0) throw "New length must be >= 0";
    T* temp = new T[newSize]; 
    int number = min(oldSize, newSize); 
    copy(a, a + number, temp); 
    delete[] a; 
    a = temp;
}

// stackCapacity 만큼의 크기를 할당하는 생성자
template <class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity)
{
    if (capacity < 1) throw "Stack capacity must be > 0";
    stack = new T[capacity];
    top = -1;
}

// 스택이 비어있는지 확인하는 함수
template <class T>
inline bool Stack<T>::IsEmpty() const { return top == -1; }

// 스택의 가장 위 원소를 가져오는 함수
template <class T>
inline T& Stack<T>::Top() const
{
    if (IsEmpty()) throw "Stack is empty";
    return stack[top];
}

// 스택의 가장 위에 원소를 추가하는 함수
template <class T>
void Stack<T>::Push(const T& x)
{
    if (top == capacity - 1)
    {
        ChangeSize1D(stack, capacity, 2 * capacity);
        capacity *= 2;
    }
    stack[++top] = x;
}

// 스택의 가장 위 원소를 제거하는 함수
template <class T>
void Stack<T>::Pop()
{
    if (IsEmpty()) throw "Stack is empty. Cannot delete";
    stack[top--].~T();
}

