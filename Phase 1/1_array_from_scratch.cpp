#include <iostream>
#include <stdexcept> // for exception handling

template <typename T>
class MyArray
{
private:
  T *data;     // pointer to the array's memory
  size_t size; // number of elements

public:
  // constructor
  MyArray(size_t size) : size(size)
  {
    data = new T[size]; // allocate memory for the array
  }

  // descructor (memory management)
  ~MyArray()
  {
    delete[] data; // release allocated memory back to the system
  }

  // get element at index
  T &at(size_t index)
  {
    if (index >= size)
    {
      throw std::out_of_range("Index out of bounds");
    }
    return data[index];
  }

  // get array size
  size_t getSize() const
  {
    return size;
  }
};

int main()
{
  MyArray<int> myArray(5); // create a new int array of size 5

  // set values
  for (size_t i = 0; i < myArray.getSize(); ++i)
  {
    myArray.at(i) = i * 10;
  }

  // get values
  for (size_t i = 0; i < myArray.getSize(); ++i)
  {
    std::cout << "Element at index " << i << ": " << myArray.at(i) << '\n';
  }

  try
  {
    myArray.at(10); // this will throw an error
  }
  catch (const std::out_of_range &e)
  {
    std::cerr << "Error: " << e.what() << '\n';
  }

  return 0;
}