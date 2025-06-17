#include <iostream>
#include <stdexcept>

template <typename T>
class Stack
{
private:
  T *data;
  int top;
  int capacity;

public:
  // constructor
  Stack(int capacity = 10) : capacity(capacity), top(-1)
  {
    data = new T[capacity];
  }

  // destructor
  ~Stack()
  {
    delete[] data;
  }

  // copy constructor
  Stack(const Stack &other) : capacity(other.capacity), top(other.top)
  {
    data = new T[capacity];
    for (int i = 0; i <= top; ++i)
    {
      data[i] = other.data[i];
    }
  }

  // copy assignment operator
  Stack &operator=(const Stack &other)
  {
    if (this != &other)
    {
      delete[] data;
      capacity = other.capacity;
      top = other.top;
      data = new T[capacity];
      for (int i = 0; i <= top; ++i)
      {
        data[i] = other.data[i];
      }
    }
    return *this;
  }

  // move constructor
  Stack(Stack &&other) noexcept : data(other.data), top(other.top), capacity(other.capacity)
  {
    other.data = nullptr;
    other.top = -1;
    other.capacity = 0;
  }

  // move assignment operator
  Stack &operator=(Stack &&other) noexcept
  {
    if (this != &other)
    {
      delete[] data;
      data = other.data;
      top = other.top;
      capacity = other.capacity;

      other.data = nullptr;
      other.top = -1;
      other.capacity = 0;
    }
    return *this;
  }

  // push operation
  void push(const T &value)
  {
    if (top == capacity - 1)
    {
      resize();
    }
    data[++top] = value;
  }

  // pop operation
  T pop()
  {
    if (isEmpty())
    {
      throw std::out_of_range("Stack is empty");
    }
    return data[top--];
  }

  // top operation
  T peek() const
  {
    if (isEmpty())
    {
      throw std::out_of_range("Stack is empty");
    }
    return data[top];
  }

  // isEmpty operation
  bool isEmpty() const
  {
    return top == -1;
  }

  // size operation
  int size() const
  {
    return top + 1;
  }

private:
  // helper function to resize the stack
  void resize()
  {
    capacity *= 2;
    T *newData = new T[capacity];
    for (int i = 0; i <= top; ++i)
    {
      newData[i] = data[i];
    }
    delete[] data;
    data = newData;
  }
};

int main()
{
  Stack<int> intStack(3);

  std::cout << "Stack is empty: " << (intStack.isEmpty() ? "true" : "false") << std::endl;

  std::cout << "\nPushing elements: 10, 20, 30, 40" << std::endl;
  intStack.push(10);
  intStack.push(20);
  intStack.push(30);
  intStack.push(40);

  std::cout << "Stack size: " << intStack.size() << std::endl;
  std::cout << "Top element: " << intStack.peek() << std::endl;

  std::cout << "\nPopping elements:" << std::endl;
  while (!intStack.isEmpty())
  {
    std::cout << "Popped: " << intStack.pop() << std::endl;
  }

  std::cout << "\nStack is empty: " << (intStack.isEmpty() ? "true" : "false") << std::endl;

  try
  {
    intStack.pop();
  }
  catch (const std::out_of_range &e)
  {
    std::cout << "Error: " << e.what() << std::endl;
  }

  return 0;
}