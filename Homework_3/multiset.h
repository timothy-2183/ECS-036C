#ifndef MULTISET_H_
#define MULTISET_H_

#include <cstddef>
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>

template <typename K>
class Multiset;

template <typename K>
class Node
{
public:
  std::pair<K, size_t> find(const K &search)
  {
    if (search == key)
      return std::pair<K, size_t>{key, count};
    if (search > key && right)
      return right->find(search);
    if (search < key && left)
      return left->find(search);
    return std::pair<K, size_t>{NULL, NULL};
  }
  std::unique_ptr<Node<K>> remove(const K &search)
  {
    if (search < key)
    {
      if (left)
      {
        left = left->remove(search);
      }
    }
    else if (search > key)
    {
      if (right)
      {
        right = right->remove(search);
      }
    }
    else
    {
      if (count > 1)
      {
        count--;
        return std::unique_ptr<Node<K>>(this);;
      }
      if (!left)
        return std::move(right);
      if (!right)
        return std::move(left);

      key = right->min();
      count = right->find(right->min()).second;
      right = right->remove(key);
    }
    return std::unique_ptr<Node<K>>(this);
  }

  const K &max()
  {
    if (this->right)
    {
      return right->max();
    }
    else
    {
      return key;
    }
  }
  const K &min()
  {
    if (this->left)
    {
      return left->min();
    }
    else
    {
      return key;
    }
  }
  void insert(const K &in)
  {
    if (key == in)
    {
      count++;
      return;
    }
    if (key > in && left)
    {
      left->insert(in);
    }
    else if (key > in)
    {
      left = std::unique_ptr<Node>(new Node(in));
      return;
    }
    if (key < in && right)
    {
      right->insert(in);
    }
    else if (key < in)
    {
      right = std::unique_ptr<Node>(new Node(in));
      return;
    }
  }
  const K &ceil(const K &search)
  {
    if (key > search)
    {
      if (right)
      {
        return min();
      }
      else
      {
        return key;
      }
    }
    else
    {
      return right->ceil(search);
    }
  }
  const K &floor(const K &search)
  {
    if (key < search)
    {
      if (left)
      {
        return min();
      }
      else
      {
        return key;
      }
    }
    else
    {
      return right->ceil(search);
    }
  }

  bool contains(const K &search)
  {
    if (key == search)
      return true;
    if (key > search && left)
      return left->contains(search);
    if (key < search && right)
      return right->contains(search);
    return false;
  }

  // constructor that immedeately adds the key to reduce the amount of insertion later on.
  Node(const K &new_key) : key(new_key), left(nullptr), right(nullptr), count(1) {};

private:
  K key;
  std::unique_ptr<Node<K>> left;
  std::unique_ptr<Node<K>> right;
  size_t count;
};

template <typename K>
class Multiset
{
public:
  //
  // Public API
  //

  // * Capacity
  // Returns number of items in multiset --O(1)
  size_t Size() { return size; }

  // Returns true if multiset is empty --O(1)
  bool Empty() { return !root; }

  // * Modifiers
  // Inserts an item corresponding to @key in multiset --O(log N) on average
  void Insert(const K &key)
  {
    if (root)
    {
      root->insert(key);
      size++;
    }
    else
    {
      root = std::unique_ptr<Node<K>>(new Node<K>(key));
      size = 1;
    }
  }

  // Removes an item corresponding to @key from multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  void Remove(const K &key)
  {
    if (!root)
      throw std::runtime_error("Key not found");
    root = root->remove(key);
    size--;
  }

  // * Lookup
  // Return whether @key is found in multiset --O(log N) on average
  bool Contains(const K &key)
  {
    if (!root)
      return false;
    return root->contains(key);
  }

  // Returns number of items matching @key in multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  size_t Count(const K &key)
  {
    if (!root)
      throw std::runtime_error("Key not found");
    if (root->contains(key))
    {
      std::pair<K, size_t> my_pair = root->find(key);
      return my_pair.second;
    }
    else
    {
      throw std::runtime_error("Key does not exist");
    }
  }

  // Return greatest key less than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no floor exists for key
  const K &Floor(const K &key)
  {
    if (!root)
      throw std::runtime_error("Multiset is empty");
    if (root->contains(key))
    {
      return key;
    }
    else if (key < root->min())
    {
      throw std::runtime_error("All numbers in the multiset is greater than the Floor.");
    }
    else
    {
      return root->floor(key);
    }
  }

  // Return least key greater than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no ceil exists for key
  const K &Ceil(const K &key)
  {
    if (!root)
      throw std::runtime_error("Multiset is empty");
    if (root->contains(key))
    {
      return key;
    }
    else if (key > root->max())
    {
      throw std::runtime_error("All numbers in the multiset is lesser than the ceil");
    }
    else
    {
      return root->ceil(key);
    }
  }

  // Return max key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K &Max()
  {
    if (!root)
      throw std::runtime_error("Multiset is empty");
    return root->max();
  }

  // Return min key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K &Min()
  {
    if (!root)
      throw std::runtime_error("Multiset is empty");
    return root->min();
  }
  Multiset() : size(0), root(nullptr) {};

private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  // Private member variables
  // ...To be completed...

  // Private constants
  // ...To be completed (if any)...

  size_t size;
  std::unique_ptr<Node<K>> root;

  // Private methods
  // ...To be completed (if any)...
};

//
// Your implementation of the class should be located below
//

// ...To be completed...

#endif // MULTISET_H_
