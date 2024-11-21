#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "../node/node.h"
using namespace std;

// Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE> *head);

// recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head);

// return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_search_list(node<ITEM_TYPE> *head,
                              ITEM_TYPE key);

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_head(node<ITEM_TYPE> *&head,
                              ITEM_TYPE insert_this);

// insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_after(node<ITEM_TYPE> *&head,
                               node<ITEM_TYPE> *after_this,
                               ITEM_TYPE insert_this);

// insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_before(node<ITEM_TYPE> *&head,
                                node<ITEM_TYPE> *before_this,
                                ITEM_TYPE insert_this);

// ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_previous_node(node<ITEM_TYPE> *head,
                                node<ITEM_TYPE> *prev_to_this);

// delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE> *&head,
                       node<ITEM_TYPE> *delete_this);

// duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE> *head);

// duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

// delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE> *&head);

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE &_at(node<ITEM_TYPE> *head, int pos);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted(node<ITEM_TYPE> *&head, // insert
                                ITEM_TYPE item,
                                bool ascending = true);

// insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted_and_add(node<ITEM_TYPE> *&head,
                                        ITEM_TYPE item,
                                        bool ascending = true);
// node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_where_this_goes(node<ITEM_TYPE> *head,
                                  ITEM_TYPE item,
                                  bool ascending = true);

template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE> *head)
{
    node<ITEM_TYPE> *walker = head;
    while (walker != nullptr)
    {
        cout << *walker;        // print node item at that position
        walker = walker->_next; // move walker to next node
    }
    cout << "|||" << endl; // signify end, null
}

template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head)
{
    if (head == nullptr)
    {
        return;
    }

    _print_list_backwards(head->_next);
    cout << *head;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_search_list(node<ITEM_TYPE> *head, ITEM_TYPE key)
{
    node<ITEM_TYPE> *walker = head;
    while (walker != nullptr)
    {
        if (walker->_item == key) // match item with key
        {
            return walker; // return ptr to key
        }
        walker = walker->_next;
    }

    return nullptr;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this)
{

    node<ITEM_TYPE> *temp = new node<ITEM_TYPE>(insert_this); // create node with value insert_this

    temp->_next = head; // set next pointer of new node to current head

    head = temp; // update head to point to new node

    return temp; // return pointer to new node
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_after(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this)
{
    if (head == nullptr || after_this == nullptr) // if the list is empty
    {
        assert(after_this == nullptr);
        return _insert_head(head, insert_this); // add a head to the list
    }

    node<ITEM_TYPE> *temp = new node<ITEM_TYPE>(insert_this); // create node with value insert_this

    temp->_next = after_this->_next; // set next pointer of new node to next node of after_this

    after_this->_next = temp; // update after_this to new node

    return temp;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_before(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *before_this, ITEM_TYPE insert_this)
{
    if (head == nullptr || before_this == nullptr) // if the list is empty
    {
        assert(before_this == nullptr);
        return _insert_head(head, insert_this); // add a head to the list
    }

    if (head == before_this) // check if head and before_this are the same
    {
        return _insert_head(head, insert_this);
    }

    node<ITEM_TYPE> *prev = _previous_node(head, before_this); // grab the previous node to "before_this"

    assert(prev != nullptr);

    return _insert_after(head, prev, insert_this); // insert after this previous node, which is before "before_this"
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_previous_node(node<ITEM_TYPE> *head, node<ITEM_TYPE> *prev_to_this)
{

    if (head == nullptr || prev_to_this == nullptr)
    {
        return nullptr;
    }

    node<ITEM_TYPE> *prev = nullptr;

    while (head != nullptr)
    {
        if (head->_next == prev_to_this)
        {
            return head;
        }
        head = head->_next;
    }

    return nullptr;
}

template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *delete_this)
{
    if (head == nullptr || delete_this == nullptr) // check if both nodes are nullptr
    {
        assert(delete_this == nullptr);
        return ITEM_TYPE();
    }

    if (head == delete_this) // if the head is the node to be deleted
    {
        ITEM_TYPE item = head->_item; // get the item of head
        node<ITEM_TYPE> *temp = head; // point a temp node to the head
        head = head->_next;           // walk head to next node
        delete temp;                  // delete temp node
        temp = nullptr;
        return item; // return the item
    }

    node<ITEM_TYPE> *prev = _previous_node(head, delete_this); // get previous node to delete_this

    if (prev == nullptr)
    {
        return ITEM_TYPE();
    }

    ITEM_TYPE item = delete_this->_item; // get deleted item
    prev->_next = delete_this->_next;    // point next node of prev to next node of delete_this
    delete delete_this;                  // delete delete_this
    return item;                         // return deleted item
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE> *head)
{

    if (head == nullptr)
    {
        return nullptr;
    }

    node<ITEM_TYPE> *new_head = new node<ITEM_TYPE>(head->_item); // create new node taking head item
    node<ITEM_TYPE> *w1 = new_head;                               // create a walker that points to new node
    node<ITEM_TYPE> *w2 = head->_next;                            // create second walker that points to next node of head

    while (w2 != nullptr)
    {
        w1 = _insert_after(new_head, w1, w2->_item);
        w2 = w2->_next;
    }

    return new_head;
}

template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
    dest = _copy_list(src);

    if (dest == nullptr)
    {
        return nullptr;
    }

    node<T> *last_node = dest;

    while (last_node != nullptr)
    {
        last_node = last_node->_next;
    }

    return last_node;
}

template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE> *&head)
{
    while (head != nullptr)
    {
        node<ITEM_TYPE> *temp = head;
        head = head->_next;
        delete temp;
    }
}

template <typename ITEM_TYPE>
ITEM_TYPE &_at(node<ITEM_TYPE> *head, int pos)
{
    node<ITEM_TYPE> *walker = head;

    int i = 0;
    while (walker != nullptr)
    {
        if (i == pos)
        {
            return walker->_item;
        }
        walker = walker->_next;
        i++;
    }
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending)
{

    if (head == nullptr)
    {
        return _insert_head(head, item);
    }

    node<ITEM_TYPE> *position = _where_this_goes(head, item, ascending);

    if (position == nullptr)
    {
        return _insert_before(head, head, item);
    }

    return _insert_after(head, position, item);
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted_and_add(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending)
{
    if (head == nullptr)
    {
        return _insert_head(head, item);
    }

    node<ITEM_TYPE> *position = _where_this_goes(head, item, ascending);

    if (position == nullptr)
    {
        return _insert_before(head, head, item);
    }

    if (position->_item == item)
    {
        position->_item += item;
        return position;
    }

    return _insert_after(head, position, item);
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_where_this_goes(node<ITEM_TYPE> *head, ITEM_TYPE item, bool ascending)
{

    if (head == nullptr)
    {
        return nullptr;
    }

    node<ITEM_TYPE> *leader = head;      // leader after follower
    node<ITEM_TYPE> *follower = nullptr; // get a follower to point to node to return

    if ((ascending && item < head->_item) || (!ascending && item > head->_item))
    {
        return nullptr;
    }

    while (leader != nullptr)
    {
        if ((ascending && leader->_item > item) || (!ascending && leader->_item < item))
        {
            return follower; // return the node that the item goes after
        }

        follower = leader;
        leader = leader->_next;

        if (leader == nullptr)
        {
            break;
        }
    }

    return follower;
}

#endif