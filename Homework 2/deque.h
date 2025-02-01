#ifndef DEQUE_H_
#define DEQUE_H_

#include <cstddef>

template<typename T>
class Deque {
 public:
  //
  // @@@ The class's public API below should NOT be modified @@@
  //

  // Constructor
  Deque(){
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
  bool Empty() const noexcept{
    return size == 0;
  }

  // Return number of items in deque
  // Complexity: O(1)
  size_t Size() const noexcept{
    return size;
  }

  // Resize internal data structure to fit precisely the number of items and
  // free unused memory
  // Complexity: O(N)
  void ShrinkToFit(){
    T* new_arr = new T[size];
    for (size_t j = 0 , i = front; i != back; i++, j++)
    {
        if (i == capacity)
        {
            i=0;
        }
        new_arr[j]=deq_array[i];
    }
    delete[] deq_array;
    deq_array=new_arr;
    capacity=size;
    front = 0;
    back = size-1;
    delete[] new_arr;
  }


  //
  // Element access
  //

  // Return item at pos @pos
  // Complexity: O(1)
  T& operator[](size_t pos){
    return deq_array[(front < back)?];
  }

  // Return item at front of deque
  // Complexity: O(1)
  T& Front(){
    return deq_array[front];
  }

  // Return item at back of deque
  // Complexity: O(1)
  T& Back(){
    return deq_array[back];
  }


  //
  // Modifiers
  //

  // Clear contents of deque (make it empty)
  // Complexity: O(1)
  void Clear(void) noexcept{
    delete[] deq_array;
    deq_array = new T[8];
    size=0;
    capacity=8;
  }

  // Push item @value at front of deque
  // Complexity: O(1) amortized
  void PushFront(const T &value){

  }

  // Push item @value at back of deque
  // Complexity: O(1) amortized
  void PushBack(const T &value)(
    
  )

  // Remove item at front of deque
  // Complexity: O(1) amortized
  void PopFront(){
    deq_array[front] == nullptr;
    if (front == size-1) front -=size;
    front++;
    
  }

  // Remove item at back of deque
  // Complexity: O(1) amortized
  void PopBack(){
    deq_array[back]==nullptr;
    if (back==0) back += size;
    back--;
  }

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  // Private member variables
  T* deq_array;
  size_t size;
  size_t front;
  size_t back;
  size_t capacity;

  // Private constants
  // ...To be completed (if any)...

  // Private methods
  void AddCapacity(){
    T* new_arr = new T[capacity+8];
    for (size_t j = 0 , i = front; i != back; i++, j++)
    {
        if (i == capacity)i=0;
        new_arr[j]=deq_array[i];
    }
    capacity=capacity+8;
    delete[] deq_array;
    deq_array=new_arr;
    front = 0 ;
    back = size-1;
    }
} ;
#endif DEQUE_H_
//
// Your implementation of the class should be located below
//

// ...To be completed..