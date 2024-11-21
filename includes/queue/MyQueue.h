#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator
    {
    public:
        friend class Queue;                // give access to list to access _ptr
        Iterator() { _ptr = NULL; }        // default ctor
        Iterator(node<T> *p) { _ptr = p; } // Point Iterator to where
                                           //...                        //  p is pointing to

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

    Queue();

    Queue(const Queue<T> &copyMe);
    ~Queue();
    Queue &operator=(const Queue<T> &RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const; // Iterator to the head node
    Iterator end() const;   // Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template <typename TT>
    friend ostream &operator<<(ostream &outs, const Queue<TT> &printMe);

private:
    node<T> *_front;
    node<T> *_rear;
    int _size;
};

template <typename T>
Queue<T>::Queue()
{
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &copyMe)
{
    _front = _copy_list(copyMe._front);
    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
}

template <typename T>
Queue<T>::~Queue()
{
    _clear_list(_front);
}

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &RHS)
{
    if (this == &RHS)
    {
        return *this;
    }

    _clear_list(_front);
    _size = RHS._size;
    _front = _copy_list(RHS._front);
    _rear = _copy_list(_front, RHS._front);
    return *this;
}

template <typename T>
bool Queue<T>::empty()
{
    return _size == 0;
}

template <typename T>
T Queue<T>::front()
{
    assert(_front != nullptr);
    return _front->_item;
}

template <typename T>
T Queue<T>::back()
{
    assert(_rear != nullptr);
    return _rear->_item;
}

template <typename T>
void Queue<T>::push(T item)
{
    if (_front == nullptr)
    {
        _insert_head(_front, item);
        _rear = _front;
    }
    else
    {
        _rear = _insert_after(_front, _rear, item);
    }
    _size++;
}

template <typename T>
T Queue<T>::pop()
{
    assert(!empty());
    T item = _delete_node(_front, _front);
    _size--;
    return item;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return Iterator(_front);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    return Iterator(NULL);
}

template <typename T>
void Queue<T>::print_pointers()
{
    _print_list(_front);
}

template <typename TT>
ostream &operator<<(ostream &outs, const Queue<TT> &printMe)
{
    outs << "Queue:Head->";
    _print_list(printMe._front);
    return outs;
}

#endif
