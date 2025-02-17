#ifndef MULTISET_H_
#define MULTISET_H_

#include <cstddef>
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>

template <typename K>
class Multiset {
 public:
  //
  // Public API
  //

  // * Capacity
  // Returns number of items in multiset --O(1)
  size_t Size(){return size;}

  // Returns true if multiset is empty --O(1)
  bool Empty() {return (!root)}

  // * Modifiers
  // Inserts an item corresponding to @key in multiset --O(log N) on average
  void Insert(const K &key){
    if (root)
    {
      root->insert(key);
      size++;
    }
    else{
      root = std::unique_ptr<Node<K>>(new Node(key));
      size = 1;
    }
  }

  // Removes an item corresponding to @key from multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  void Remove(const K &key){
    if (root->getkey()==key)
    {
      
    }
    
  }

  // * Lookup
  // Return whether @key is found in multiset --O(log N) on average
  bool Contains(const K& key){
    if (root)
    {
      root.contains(key);
    }
    else{
      return false;
    }
  }

  // Returns number of items matching @key in multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  size_t Count(const K& key){
    if (root)
    {
      
    }
    else{
      throw std::runtime_error("Multiset is empty");
    }
  }

  // Return greatest key less than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no floor exists for key
  const K& Floor(const K &key){
    if (root)
    {
      if (root->contains(key))
      {
        return key;
      }
      else if(key < root->min()){
        throw std::runtime_error("All numbers in the multiset is greater than the Floor.")
      }
      else{
        return root->floor(key);
      }
    }
    else{
      throw std::runtime_error("Multiset is empty");
    }
  }

  // Return least key greater than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no ceil exists for key
  const K& Ceil(const K &key){
    if (root)
    {
      if (root->contains(key))
      {
        return key;
      }
      else if(key > root->max()){
        throw std::runtime_error("All numbers in the multiset is lesser than the ceil");
      }
      else{
        return root->ceil(key);
      }
    }
    else{
      throw std::runtime_error("Multiset is empty");
    }
  }
  

  // Return max key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K& Max(){
    if(root){
      root->min
    }
    else {
      throw std::runtime_error("Multiset is empty");
    }
  }

  // Return min key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K& Min(){
    if(root){
      return root->min();
    }
    else {
     throw std::runtime_error("Multiset is empty");
    }
  }
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

template <typename K>
class Node{
  public:
  const &K max(){
    if (this->right)
    {
      return right->max();
    }
    else{
      return key;
    }
  }
  const &K min(){
    if (this->left)
    {
      return left->min();
    }
    else{
      return key;
    }
  }
  void insert (const K &in){
    if (key==in)
    {
      count++;
      return;
    }
    if (key > in && left) {
      left->insert(in);
    }
    else if (key > in){
      left = std::unique_ptr<Node>(new Node(search));
      return;
    }
    if (key < in && right) {
      right->insert(in);
    }
    else if(key < in){
      right = std::unique_ptr<Node>(new Node(search));
      return;
    }
  }
  const &K ceil(const &K search){
    if (key > search)
    {
      if (right)
      {
        return min();
      }
      else{
        return key;
      }
    }
    else{
      return right->ceil(search);
    }
  }
  const &K floor(const &K search){
    if (key < search)
    {
      if (left)
      {
        return min();
      }
      else{
        return key;
      }
    }
    else{
      return right->ceil(search);
    }
  }
  

  bool contains(const K& search){
    if (key == search) return true;
    if (key > search && left) return left->contains(search);
    if (key < search && right) return right->contains(search);
    return false;
  }
  const &K getkey{return key;}

  // constructor that immedeately adds the key to reduce the amount of insertion later on.
  Node(const K& new_key):key(new_key):left(nullptr):right(nullptr):count(1){}
  private:
  K key;
  std::unique_ptr<Node<K>> left;
  std::unique_ptr<Node<K>> right; 
  size_t count;
};

//
// Your implementation of the class should be located below
//

// ...To be completed...

#endif  // MULTISET_H_
