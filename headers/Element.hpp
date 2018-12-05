#ifndef ELEMENT_CLASS

#define ELEMENT_CLASS

#include "Avl_headers\AvlTree.hpp"

template <class T>
class Element {
  private:
    T value;
    int key;

  public:
    Element() {};

    Element(T value, int key)
    {
      this->value = value;
      this->key = key;
    };

    bool operator<(const Element& other)
    {
      return this->key < other.key;
    };

    bool operator>(const Element& other)
    {
      return this->key > other.key;
    };

    bool operator==(const Element& other)
    {
      return this->key == other.key;
    };

    bool operator!=(const Element& other)
    {
      return this->key != other.key;
    };

    bool operator=(const Element& other)
    {
      this->value = other.value;
      this->key = other.key;
    };

    T getValue() const
    {
      return this->value;
    };

    int getKey() const
    {
      return this->key;
    };
};

#endif