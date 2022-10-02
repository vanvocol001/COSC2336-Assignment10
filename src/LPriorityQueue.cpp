/** @file LPriorityQueue.cpp
 * @brief Concrete linked list based implementation of Priority Queue ADT.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Queues
 * @date   June 1, 2021
 *
 * Implement the Queue abstraction but maintain the queue as a
 * priority queue.  This is a linked list based implementation.  We
 * inherit from the LQueue class and override the
 * enqueue() method to insert new values into the queue
 * based on their priority.  For this class we assume that
 * operator<() is defined for the type T being managed, and that
 * it returns true when the lhs T value is higher priority than the
 * rhs T value.
 */
#include "LPriorityQueue.hpp"
#include "Job.hpp"
#include "QueueException.hpp"
using namespace std;

// define macros to make it easier to access the base class protected
// members without all of the cruft
#define size LQueue<T>::size
#define frontNode LQueue<T>::frontNode
#define backNode LQueue<T>::backNode

/**
 * 
 * @brief Enqueue with a sort on linked list
 * 
 * Enqueue a new value and sort the queue so that 
 * its values are alligned in descending order. This 
 * implementation will work with a queue created using 
 * the linked list method as opposed to being created
 * with an array format.
 * 
 *  @param newItem The value to be added to the queue.
 * Initially starts at backIndex but will be compared and swapped
 * with the values "in front" of it within the queue until it's 
 * placed in the proper location.
 * 
 */
template<class T>
void LPriorityQueue<T>::enqueue(const T& newItem)
{
  
  // dynamically allocate a new Node to hold the value
  Node<T>* newNode = new Node<T>;
  newNode->value = newItem;
  newNode->next = nullptr;

  // if queue is currently empty, this node becomes the front and back
  if (this->isEmpty())
  {
    frontNode = newNode;
  }
  // otherwise at least one node, so just make this the new back node
  else
  {
    backNode->next = newNode;
  }

  // this new node is always the new back node
  backNode = newNode;

  // queue has now grown by 1 item, don't forget to update size member
  // variable
  this->size += 1;

  Node<T>* tempNode1 = frontNode;
  Node<T>* tempNode2 = frontNode;
  for (int index1 = 0; index1 < this->size; index1++)
  {
    for (int index2 = 0; index2 < this->size - 1; index2++)
    {
      if (tempNode1-> value > tempNode2->value)
      {
        T temp = tempNode1 ->value;
        tempNode1->value = tempNode2->value;
        tempNode2->value = temp;
      }
      tempNode2 = tempNode2->next;
    }
    tempNode2 = frontNode;
    tempNode1 = frontNode->next;
    for (int index3 = 0; index3 < index1; index3++)
    {
      tempNode1 = tempNode1->next;
    }
  }
}






/**
 * @brief Cause specific instance compilations
 *
 * This is a bit of a kludge, but we can use normal make dependencies
 * and separate compilation by declaring template class Queue<needed_type>
 * here of any types we are going to be instantianting with the
 * template.
 *
 * https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 * https://isocpp.org/wiki/faq/templates#separate-template-class-defn-from-decl
 */
template class LPriorityQueue<int>;
template class LPriorityQueue<string>;
template class LPriorityQueue<Job>;

/*
  Node<T>* temp1 = frontNode;
  Node<T>* temp2 = frontNode;
  for (int i = 0; i < this->size; i++)
  {
    for (int j = 0; j < this->size - 1; j++)
    {
      if (temp1-> value > temp2->value)
      {
        T temp = temp1 ->value;
        temp1->value = temp2->value;
        temp2->value = temp;
      }
      temp2 = temp2->next;
    }
    temp2 = frontNode;
    temp1 = frontNode->next;
    for (int k = 0; k < i; k++)
    {
      temp1 = temp1->next;
    }
  }*/