#include <iostream>
using namespace std;

// Define the structure of the node
struct Node
{
    int key;
    Node *left;
    Node *right;
};

// Function to create a new node
Node *createNode(int key)
{
    Node *newNode = new Node();
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node
Node *insertNode(Node *root, int key)
{
    if (root == NULL)
        return createNode(key);
    if (key < root->key)
        root->left = insertNode(root->left, key);
    else if (key > root->key)
        root->right = insertNode(root->right, key);
    return root;
}

// Function to print the tree in order
void printInOrder(Node *root)
{
    if (root == NULL)
        return;
    printInOrder(root->left);
    cout << root->key << " ";
    printInOrder(root->right);
}

Node *makeTree()
{
    Node *root = NULL;
    root = insertNode(root, 10);
    insertNode(root, 5);
    insertNode(root, 20);
    insertNode(root, 3);
    insertNode(root, 8);
    insertNode(root, 15);
    insertNode(root, 25);
    return root;
}

int findMin(Node *tree)
{
    if (tree == NULL)
        return false;
    if (tree->left == NULL)
        return tree->key;
    findMin(tree->left);
}

int findMax(Node *tree)
{
    if (tree == NULL)
        return false;
    if (tree->right == NULL)
        return tree->key;
    findMax(tree->right);
}

bool contains(Node *tree, int value)
{
    if (tree == NULL)
        return false;
    if (tree->key == value)
        return true;
    if (contains(tree->left, value))
        return true;
    if (contains(tree->right, value))
        return true;
    return false;
}

// Main function
int main()
{
    Node *tree = makeTree();
    cout << "In order traversal: ";
    printInOrder(tree);
    cout << endl;
    cout << "Min: " << findMin(tree) << endl;
    cout << "Max: " << findMax(tree) << endl;
    cout << "Does tree have " << 21 << " ? : " << contains(tree, 21) << endl;
    return 0;
}