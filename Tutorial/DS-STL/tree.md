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
