# Simple Tree
![](/images/tree.png)

## Definitions

### Nodes
- Each element is a `node`
- nodes are always connected to other nodes
- `leaf` nodes have no outgoing edges
- nodes store data, and may be labeled

### Root
- The tree has 1 `root` node
- root has no incoming edges

### Edges
- each connection between two nodes is an `edge`
- edges are alwasy directed (and always directing away from root)
- edges do not store data, and have no labels; they are reffered by nodes they connect
- `height` is the number of **<u>edges</u>** in the longest path from root to a leaf

### Relation
- every node except root, has a `parent` node
- `children` of a node are the nodes having that node as parent
- a node can have 0 to infinite children
- an `ancestor` of a particular node is any node that lies on the path from that node to the root of the tree
- a `descendant` of a particular node is any node on the path from that node to a leaf
- `siblings` are the nodes with common parent
- `grandparant` parent of parent, and `grandchild` child of child

## Conditions
minimum conditions to be a tree:
1. must have a root
2. must have directed edges
3. must not have a cycle (an upward edge somewhere)

# Binary Tree
in a binary tree, every node has at most 2 children.

![](/images/binary-tree.png)

### Definitions
- every node has a `left` and `right` child
- the tree nodes' implementation is nearly identical to a doubly-linked list
- `height` is more important here
- a B-tree is `full` if and only if every node has 0 or 2 children
- a B-tree is `perfect` if and only if every interior(not root and not a leaf) has 2 children, and all leaves are at the same level. a perfect B-tree:

![](/images/perfect-btree.png)

- a B-tree is `complete` if and only if the tree is perfect up until the last level (neglecting the last level, you have a perfect tree), and all leaf nodes in the last level are pushed to the left (they are at the most left place they can be). a complete B-tree:

![](/images/complete-btree.png)

- a full B-tree is not necessarily complete; a complete B-tree is not neccesarily full!

# Tree Traversal
visiting every node in the tree exactly once.

> Doing a traversal requires that every single node is visited. On the other hand, a search allows us to discover a particular node throughout the tree. So when we discover a node in the tree, we may not visit every single node.

## Pre-order traversal
here we visit every node in this order: `node -> left child -> right child`

```cpp
void BinaryTree::PreOrder(TreeNode* current)
{
    if(current != NULL)
    {
        visit(current);
        PreOrder(current->left);
        PreOrder(current->right);
    }
}
```

## In-order traversal
here we visit every node in this order: `left child -> node -> right child`

this traversal is identical to orders in algebraic math equations 

```cpp
void BinaryTree::InOrder(TreeNode* current)
{
    if(current != NULL)
    {
        InOrder(current->left);
        visit(current);
        InOrder(current->right);
    }
}
```

## Post-order traversal
here we visit every node in this order: `left child -> right child -> node`

```cpp
void BinaryTree::PostOrder(TreeNode* current)
{
    if(current != NULL)
    {
        PostOrder(current->left);
        PostOrder(current->right);
        visit(current);
    }
}
```

## Level-order traversal
read every single level, one level at a time.

![](/images/level-order-traversal.png)

# Binary Search Tree (BST)
BST is an ordered B-tree capable of being used as a search structure.

![](/images/BST.png)

a B-tree is a BST if and only if for every node:

1. nodes in the left subtree are less than itself
2. nodes in the right subtree are greater than itself

we can implement a dictionary with BST. the dictionary ADT has these functionalities:

## BST Operations

- find: given a key, find the data associated with it
- insert: add new key/value
- remove
- empty: if the dict is empty


### find
worst-cast is visiting the longest path from root to a leaf (tree's height) -> much better than arrays and lists

```cpp
template <typename K, typename D>
const D & Dictionary<K, D>::find(const K & key)
{
    TreeNode *& node = _find(key, head_);
    if (node == nullptr) {throw std::runtime_error("key not found");}
    return node->data;
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode *& Dictionary<K, D>::_find(const K & key, TreeNode *& cur) const
{
    if      (cur == nullptr)    {return cur;}
    else if (key == cur->key)   {return cur;}
    else if (key < cur->key)    {return _find(key, cur->left);}
    else                        {return _find(key, cur->right);}
}
```
### insert
it is very trivial. you just need to find the location where you should add it.

```cpp
template <typename K, typename D>
void Dictionary<K, D>::insert(const K & key, const D & data)
{
    TreeNode *& node = _find(key, head_);
    node = new TreeNode(key, data);
}
```
```cpp
insert(17);
```
![](/images/insert-BST.png)

### remove

this operation is tricky. possible cases in order of difficulty are:

- removing a leaf: just wipe it
- removing a node with one child: just update its parent, like a linked list
- removing a node with two childs
- removing the root node

when removing the root (and also for case 3), the best choice to become the new root is the IOP (in-order predecessor) which is the previous node in an in-order traversal. 

We can also develop a clever way of finding the IOP. The IOP is always going to be the right-most node in the left sub-tree.

We first swap the root with IOP, and then remove the new previous root (is now case 1 or 2) and the BST is still correct.

```cpp
template <typename K, typename D>
const D & Dictionary<K, D>::remove(const K & key) 
{
    TreeNode *& node = _find(key, head_);
    return _remove(node);
}

template <typename K, typename D>
const D & Dictionary<K, D>::_remove(TreeNode *& node) 
{
    // Zero child remove:
    if (node->left == nullptr && node->right == nullptr) 
    {
        const D & data = node->data;
        delete(node);
        node = nullptr;
        return data;
    }

    // One-child (left) remove
    else if (node->left != nullptr && node->right == nullptr) 
    {
        const D & data = node->data;
        TreeNode *temp = node;
        node = node->left;
        delete(temp);
        return data;
    }

    // One-child (right) remove
    else if (node->left == nullptr && node->right != nullptr) 
    {
        const D & data = node->data;
        TreeNode *temp = node;
        node = node->right;
        delete(temp);
        return data;
    }

    // Two-child remove:
    else 
    {
        // Find the IOP
        TreeNode *& iop = _iop( node->left );
        // Swap the node to remove and the IOP
        _swap( node, iop );
        // Remove the new IOP node that was swapped
        return _remove( node );
    }
}

```

![](/images/iop.jpg)

## BST Runtime Analysis
For a given number `n` data elements, there are `n!` ways to put that data into a BST (for first element there are `n` options, for adding next element there are `n-1` options, ...)

The best case in BST is a fully balanced BST (data is equally put into left and right), and in worst case it is like a linked list.

all operations in BST are the same as `find`, because after finding the element the operation takes constant time.

|        | BST (avg case) | BST (worst case) | sorted array | sorted list |
| ------ | -------------- | ---------------- | ------------ | ----------- |
| find   | O(log(n))      | O(n)             | O(log(n))    | O(n)        |
| insert | O(log(n))      | O(n)             | O(n)         | O(n)        |
| remove | O(log(n))      | O(n)             | O(n)         | O(n)        |

the only algorithm that runs in log n time for both find, insert, and remove is this average case binary search tree. We can't do that with an array. We can't do that with a sorted list. 

## Balanced BST

### Height Balance Factor
it is the difference in height between the left subtree and the right subtree. Ideally we want to keep that balance factor small. 

### Definition
a balanced binary search tree is going to be a binary search tree where every single node in this tree has a balance factor with a magnitude of either 0 or 1. that means the balance factor can either be -1, 0 or 1.



