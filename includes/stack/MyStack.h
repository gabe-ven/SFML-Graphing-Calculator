#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Stack
{
public:
    class Iterator
    {
    public:
        friend class Stack;                // give access to list to access _ptr
        Iterator() { _ptr = NULL; }        // default ctor
        Iterator(node<T> *p) { _ptr = p; } // Point Iterator to where
                                           //   p is pointing to
        operator bool()
        {
            return _ptr != NULL;
        }

        T &operator*()
        {
            assert(_ptr);
            return _ptr->_item;
        }

        T *operator->()
        {
            return &_ptr->_item;
        }

        bool is_null()
        {
            return _ptr == NULL;
        }

        friend bool operator!=(const Iterator &left, const Iterator &right)
        {
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator &left, const Iterator &right)
        {
            return left._ptr == right._ptr;
        }

        Iterator &operator++()
        {
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator &it, int unused)
        {
            Iterator hold(it);
            ++it;
            return hold;
        }

    private:
        node<T> *_ptr; // pointer being encapsulated
    };

    Stack();
    Stack(const Stack<T> &copyMe);
    ~Stack();
    Stack<T> &operator=(const Stack<T> &RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template <typename TT>
    friend ostream &operator<<(ostream &outs,
                               const Stack<TT> &printMe);

    Iterator begin() const; // Iterator to the head node
    Iterator end() const;   // Iterator to NULL
    int size() const { return _size; }

private:
    node<T> *_top;
    int _size;
};

template <typename T>
Stack<T>::Stack()
{
    _top = nullptr;
    _size = 0;
}
template <typename T>
Stack<T>::Stack(const Stack<T> &copyMe)
{
    _top = _copy_list(copyMe._top);
    _size = copyMe._size;
}

template <typename T>
Stack<T>::~Stack()
{
    _clear_list(_top);
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &RHS)
{
    if (this == &RHS)
    {
        return *this;
    }

    _clear_list(_top);
    _size = RHS._size;
    _top = _copy_list(RHS._top);
    return *this;
}

template <typename T>
T Stack<T>::top()
{
    return _top->_item;
}

template <typename T>
bool Stack<T>::empty()
{
    return _size == 0;
}

template <typename T>
void Stack<T>::push(T item)
{
    _insert_head(_top, item);
    _size++;
}

template <typename T>
T Stack<T>::pop()
{
    assert(!empty());
    T item = _delete_node(_top, _top);
    _size--;
    return item;
}

template <typename TT>
ostream &operator<<(ostream &outs, const Stack<TT> &printMe)
{
    outs << "Stack:Head->";
    _print_list(printMe._top);
    return outs;
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::begin() const
{
    return Iterator(_top);
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const
{
    return Iterator(NULL);
}

#endif