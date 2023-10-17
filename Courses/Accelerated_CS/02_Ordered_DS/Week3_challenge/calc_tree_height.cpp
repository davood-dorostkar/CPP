#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

class Node
{
public:
    int height; // to be set by computeHeight()
    Node *left, *right;
    Node()
    {
        height = -1;
        left = right = nullptr;
    }
    ~Node()
    {
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
    }
};

void computeHeight(Node *n)
{

    int leftHeight = -1;
    int rightHeight = -1;
    if (n->left == nullptr && n->right == nullptr)
    {
        n->height = 0;
        return;
    }
    if (n->left != nullptr)
    {
        computeHeight(n->left);
        leftHeight = n->left->height;
    }
    if (n->right != nullptr)
    {
        computeHeight(n->right);
        rightHeight = n->right->height;
    }
    n->height = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

void printTree(const Node *n)
{
    if (!n)
        return;
    std::cout << n->height << "(";
    printTree(n->left);
    std::cout << ")(";
    printTree(n->right);
    std::cout << ")";
}

int main()
{
    Node *n = new Node();
    n->left = new Node();
    n->right = new Node();
    n->right->left = new Node();
    n->right->right = new Node();
    n->right->right->right = new Node();

    computeHeight(n);

    printTree(n);
    std::cout << std::endl
              << std::endl;
    delete n;
    n = nullptr;
    return 0;
}
