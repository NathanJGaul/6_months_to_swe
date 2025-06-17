#include <iostream>
#include <stdexcept>

/*
  aQueue Implementation using linked list

  A queue is a linear data structure that follows the FIFO (First In, First Out) principle.
  Elements are added at the rear and removed from the front.

  This implementation uses a singly linked list with pointers to both fron an rear for efficient operations at both ends.
*/
template <typename T>
class Queue
{
private:
  // Node structure for linked list implementation
  struct Node
  {
    T data;     // Data stored in the node
    Node *next; // Pointer to the next node

    // Constructor for easy node creation
    Node(const T &value) : data(value), next(nullptr) {}
  };

  Node *frontPtr;   // Popinter to the front of the queue
  Node *rearPtr;    // Pointer to the rear of the queu
  size_t queueSize; // Current number of elements in the queue

public:
  /**
   * Constructor
   * Time complexity: O(1)
   * Space complexity: O(1)
   */
  Queue() : frontPtr(nullptr), rearPtr(nullptr), queueSize(0) {}

  /**
   * Destructor
   * Time complexity: O(n)
   * Space complexity: O(1)
   */
  ~Queue()
  {
    clear();
  }

  /**
   * Enqueue - Add element to the rear of the queue
   * @param value: The value to be added to the queue
   *
   * Time complexity: O(1)
   * Space complexity: O(1)
   */
  void enqueue(const T &value)
  {
    Node *newNode = new Node(value);

    // If queue is empty, both fron and rear point to the new node
    if (isEmpty())
    {
      frontPtr = rearPtr = newNode;
    }
    else
    {
      // Add new node after current rear and update rear pointer
      rearPtr->next = newNode;
      rearPtr = newNode;
    }

    queueSize++;
  }

  T dequeue()
  {
    if (isEmpty())
    {
      throw std::runtime_error("Cannot dequeue from empty queue");
    }

    Node *nodeToDelete = frontPtr;
    T frontValue = frontPtr->data;

    frontPtr = frontPtr->next;

    // If queue becomes empty after dequeue, reset rear pointer
    if (frontPtr = nullptr)
    {
      rearPtr = nullptr;
    }

    delete nodeToDelete;
    queueSize--;

    return frontValue;
  }

  bool isEmpty() const
  {
    return frontPtr == nullptr;
  }

  void clear()
  {
    while (!isEmpty())
    {
      dequeue();
    }
  }

  int size()
  {
    return queueSize;
  }
};

int main()
{
  Queue<int> myQueue;

  for (int i = 0; i < 10; i++)
  {
    myQueue.enqueue(i * 10);
    std::cout << "Size: " << myQueue.size() << std::endl;
  }

  myQueue.clear();

  std::cout << "Size: " << myQueue.size() << std::endl;
}