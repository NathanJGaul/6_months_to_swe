#include <iostream>

// node structure
struct Node
{
  int data;
  Node *next;
  Node(int val) : data(val), next(nullptr) {}
};

// linked list class
class LinkedList
{
private:
  Node *head;

public:
  // constructor
  LinkedList() : head(nullptr) {}

  // add a new node at the front
  // O(1)
  void pushFront(int val)
  {
    Node *newNode = new Node(val);
    newNode->next = head;
    head = newNode;
  }

  // add a new node at the end
  // O(1)
  void pushBack(int val)
  {
    Node *newNode = new Node(val);
    if (head == nullptr)
    {
      head = newNode;
    }
    else
    {
      Node *temp = head;
      while (temp->next != nullptr)
      {
        temp = temp->next;
      }
      temp->next = newNode;
    }
  }

  // print the list
  // O(n)
  void printList()
  {
    Node *temp = head;
    while (temp != nullptr)
    {
      std::cout << temp->data << " -> ";
      temp = temp->next;
    }
    std::cout << "nullptr" << '\n';
  }

  // destructor
  // O(n)
  ~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
      Node* next = current->next;
      delete current;
      current = next;
    }
  }
};

int main()
{
  LinkedList myLL;

  for (size_t i = 0; i < 100; i++)
  {
    myLL.pushBack(i);
  }

  myLL.printList();
}