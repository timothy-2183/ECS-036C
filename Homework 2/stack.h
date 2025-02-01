#ifndef STACK_VECTOR_H_
#define STACK_VECTOR_H_
#include <vector>
#include <iostream>
template <typename T>
class Stack
{
public:
    size_t Size();
    T &Top();
    void Pop();
    void Push(const T &item);

private:
    std::vector<T> items;
};
template <typename T>
size_t Stack<T>::Size()
{
    return items.size();
}
template <typename T>
T &Stack<T>::Top()
{
    if (!items.size())
        throw std::underflow_error("Empty stack!");
    return items.back();
}
template <typename T>
void Stack<T>::Pop()
{
    if (!items.size())
        throw std::underflow_error("Empty stack!");
    items.pop_back();
}
template <typename T>
void Stack<T>::Push(const T &item)
{
    items.push_back(item);
}
#endif // STACK_VECTOR_H_
