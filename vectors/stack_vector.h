#ifndef STACK_VECTOR_H_
#define STACK_VECTOR_H_
#include <vector>
template <typename T>
class Stack
{
public:
    // Return number of items in stack
    size_t Size();
    // Return top of stack
    T &Top();
    // Remove top of stack
    void Pop();
    // Push item to top of stack
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
