#include <iostream>
#include <random>
#include <queue>

template <typename T>
class BTree
{
private:
  struct Node
  {
    T val;
    Node *left;
    Node *right;

    // Constructor for easy node creation
    Node(const T &value) : val(value), left(nullptr), right(nullptr) {}
  };

  Node *root;

public:
  BTree() : root(nullptr) {}

  ~BTree()
  {
    destroyTree(root);
  }

  void insert(T value)
  {
    root = insertHelper(root, value);
  }

  // Simple in-order traversal (sorted output for BST)
  void printInOrder()
  {
    std::cout << "In-order: ";
    printInOrderHelper(root);
    std::cout << std::endl;
  }

  // Visual tree representation
  void printTree()
  {
    std::cout << "Tree structure:" << std::endl;
    printTreeHelper(root, "", true);
    std::cout << std::endl;
  }

  // Level-order traversal
  void printLevelOrder()
  {
    std::cout << "Level-order: ";
    printLevelOrderHelper();
    std::cout << std::endl;
  }

private:
  Node *insertHelper(Node *node, T value)
  {
    if (node == nullptr)
    {
      return new Node(value);
    }

    if (value < node->val)
    {
      node->left = insertHelper(node->left, value);
    }
    else if (value > node->val)
    {
      node->right = insertHelper(node->right, value);
    }

    return node;
  }

  void destroyTree(Node *node)
  {
    if (node != nullptr)
    {
      destroyTree(node->left);
      destroyTree(node->right);
      delete node;
    }
  }

  void printInOrderHelper(Node *node)
  {
    if (node != nullptr)
    {
      printInOrderHelper(node->left);
      std::cout << node->val << " ";
      printInOrderHelper(node->right);
    }
  }

  void printTreeHelper(Node *node, std::string prefix, bool isLast)
  {
    if (node != nullptr)
    {
      std::cout << prefix << (isLast ? "└── " : "├── ") << node->val << std::endl;

      if (node->left || node->right)
      {
        if (node->right)
        {
          printTreeHelper(node->right, prefix + (isLast ? "    " : "│   "), !node->left);
        }
        if (node->left)
        {
          printTreeHelper(node->left, prefix + (isLast ? "    " : "│   "), true);
        }
      }
    }
  }

  void printLevelOrderHelper()
  {
    if (!root)
      return;

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
      Node *current = q.front();
      q.pop();
      std::cout << current->val << " ";

      if (current->left)
        q.push(current->left);
      if (current->right)
        q.push(current->right);
    }
  }
};

int randomInt(int min, int max)
{
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(min, max);
  return dis(gen);
}

int main()
{
  BTree<int> myTree;

  for (int i = 0; i < 100; i++)
  {
    myTree.insert(randomInt(0, 100));
    myTree.printTree();
  }

  myTree.printInOrder();
}