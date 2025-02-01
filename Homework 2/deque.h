#ifndef DEQUE_H_
#define DEQUE_H_

#include <cstddef>
#include <stdexcept>

template <typename T>
class Deque
{
public:
    //
    // @@@ The class's public API below should NOT be modified @@@
    //

    // Constructor
    Deque() : size(0), capacity(8)
    {
        deq_array = new T[8];
        front = 0;
        back = 7;
    }
    // Destructor
    ~Deque()
    {
        delete[] deq_array;
    };

    //
    // Capacity
    //

    // Return true if empty, false otherwise
    // Complexity: O(1)
    bool Empty() const noexcept
    {
        return size == 0;
    }

    // Return number of items in deque
    // Complexity: O(1)
    size_t Size() const noexcept
    {
        return size;
    }

    // Resize internal data structure to fit precisely the number of items and
    // free unused memory
    // Complexity: O(N)
    void ShrinkToFit()
    {
        T *new_arr = new T[size];
        for (size_t j = front; j < size; j++)
        {
            new_arr[j] = deq_array[(front + j) % capacity];
        }
        delete[] deq_array;
        deq_array = new_arr;
        capacity = size;
        front = 0;
        back = (size ==0 )? 0: size - 1;
    }

    //
    // Element access
    //

    // Return item at pos @pos
    // Complexity: O(1)
    T &operator[](size_t pos)
    {
        if (pos >= size)
            throw std::out_of_range("Index Out of Range");
        return deq_array[(front + pos) % capacity];
    }

    // Return item at front of deque
    // Complexity: O(1)
    T &Front()
    {
        return deq_array[front];
    }

    // Return item at back of deque
    // Complexity: O(1)
    T &Back()
    {
        return deq_array[back];
    }

    //
    // Modifiers
    //

    // Clear contents of deque (make it empty)
    // Complexity: O(1)
    void Clear(void) noexcept
    {
        delete[] deq_array;
        deq_array = new T[8];
        size = 0;
        capacity = 8;
        front = 0;
        back =7;
    }

    // Push item @value at front of deque
    // Complexity: O(1) amortized
    void PushFront(const T &value)
    {
        if (size == capacity)
            AddCapacity(); // Resize if full
        front = (front - 1 + capacity) % capacity;
        deq_array[front] = value;
        size++;
    }

    // Push item @value at back of deque
    // Complexity: O(1) amortized
    void PushBack(const T &value)
    {
        if (size == capacity)
            AddCapacity(); // Resize if full
        back = (back + 1) % capacity;
        deq_array[back] = value;
        size++;
    }

    // Remove item at front of deque
    // Complexity: O(1) amortized
    void PopFront()
    {
        if (size == 0)
            throw std::underflow_error("Deque is empty!");
        front = (front + 1) % capacity;
        size--;
        if (size==0)
        {
            front = 0;
            back =7;
        }
        
    }

    // Remove item at back of deque
    // Complexity: O(1) amortized
    void PopBack()
    {
        if (size == 0)
            throw std::underflow_error("Deque is empty!");
        back = (back - 1 + capacity) % capacity;
        size--;
        if (size==0)
        {
            front = 0;
            back =7;
        }
    }

private:
    //
    // @@@ The class's internal members below can be modified @@@
    //

    // Private member variables
    T *deq_array;
    size_t size;
    size_t front;
    size_t back;
    size_t capacity;

    // Private constants
    // ...To be completed (if any)...

    // Private methods
    void AddCapacity()
    {
        size_t new_capacity = capacity * 2;
        T *new_arr = new T[new_capacity];

        for (size_t j = 0; j < size; j++)
        {
            new_arr[j] = deq_array[(front + j) % capacity];
        }

        delete[] deq_array;
        deq_array = new_arr;
        capacity = new_capacity;
        front = 0;
        back = size - 1;
    }
};
#endif 
//
// Your implementation of the class should be located below
//

// ...To be completed..