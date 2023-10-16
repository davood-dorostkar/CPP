## AVL Trees

### Height Balance Factor (b)
it is the difference in height between the left subtree and the right subtree. Ideally we want to keep that balance factor small. 

```
b = H_rightSubTree - H_leftSubTree
```

- if the left/right child of a node is `nullptr`, then the height of that node's left/right subtree is `-1`. This is for consistency, as a leaf node by itself is a subtree of height `0`. so a `non-existent` subtree has a height of `-1`.
- The term `deeper/deepest` refer to the nodes that are closer to leafs.

### Balanced BST
a balanced binary search tree is a binary search tree where every single node in this tree has a balance factor with a magnitude of either 0 or 1. that means the balance factor can either be -1, 0 or 1.


## Balancing Algorithm

### Mountain case
it is balanced already. it is a node that has both the left and the right child.

![](/images/stick-mountain.png)

### Stick case
it is a node that has two children in the same direction and no children in the other direction.

![](/images/stick.png)

By transforming sticks into mountains, we make sure that our binary tree stays as balanced as possible.
To do that, we pick the middle node on the stick, here this V, raise it up. 

![](/images/left-rotation.png)


### Elbow case
This is a hybrid between both a stick as well as a mountain. What we need to do is actually fix the elbow to make it a stick. We do that by doing a rotation about the bend of the elbow. we do a transformation by moving this yellow node up, then transform this elbow into a stick. Once we have a stick, we know exactly what to do.

![](/images/elbow-bst.png)

we first transform this elbow into a stick, and once we transform the elbow into a stick, we raise up the center node of the stick and make it into a mountain.

![](/images/right-left-rotation.png)

### Summary

- if both of the signs match, we say we only do a single rotation, this transforms a stick into a mountain
- When the signs differ, we know we have an elbow. we need to do a double rotation. This unbends the elbow and then does the simple transformation to transform a stick into a mountain.
- if the next node in the imbalance direction is positive, we start with left rotation, otherwise start with right rotation

|                     | b of lowest node of imbalance | b of the node in the imbalance direction |
| ------------------- | ----------------------------- | ---------------------------------------- |
| Left Rotation       | 2                             | 1                                        |
| Right Rotation      | -2                            | -1                                       |
| Right-Left Rotation | 2                             | -1                                       |
| Left-Right Rotation | -2                            | 1                                        |

# AVL Trees
Balanced binary search trees are kept in balance through tree rotations when we do an insert and remove. We call these trees AVL trees named after two computer scientists, Adelson-Velsky and Landis. An AVL Tree is just like a Binary Search Tree. an AVL Tree is a implementation of a balanced binary search tree.

We only do two things differently in an AVL Tree. 
1. we do some extra work on insert and remove to ensure that we keep the trees in balance. 
2. for the balance factors to be computed easily, we store the height of every single node in the tree.

### Insert

1. insert node at proper place
2. check for imbalance
3. rotate, if necessary
4. update heights

now we have this extra helper function called ensureBalance in our AVL tree:
```cpp
template <typename K, typename D>
void AVL<K, D>::_ensureBalance(TreeNode *& cur) 
{
    int balance = height(cur->right) - height(cur->left);

    if ( balance == -2 ) 
    {
        int l_balance = height(cur->left->right) - height(cur->left->left);
        if ( l_balance == -1 ) { _rotateRight( cur ); }
        else { _rotateLeftRight( cur ); }
    } 
    else if ( balance == 2 ) 
    {
        int r_balance = height(cur->right->right) - height(cur->right->left);
        if( r_balance == 1 ) { _rotateLeft( cur ); }
        else { _rotateRightLeft( cur ); }
    }
    _updateHeight(cur);
}
```
```cpp
template <typename K, typename D>
void AVL<K, D>::_updateHeight(TreeNode *& cur) 
{
    cur->height = 1 + max(height(cur->left), height(cur->right));
}
```
```cpp
template <typename K, typename D>
void AVL<K, D>::_rotateLeft(TreeNode *& cur) 
{
    TreeNode *x = cur;
    TreeNode *y = cur->right;
    x->right = y->left;
    y->left = x;
    cur = y;
    _updateHeight(x);
    _updateHeight(y);
}
```

### Remove

```cpp
template <typename K, typename D>
const D & AVL<K, D>::_iopRemove(TreeNode *& node, TreeNode *& iop) 
{
    if (iop->right != nullptr) 
    {
        // IoP not found, keep going deeper:
        const D & d = _iopRemove(node, iop->right);
        if (iop) { _ensureBalance(iop); }
        return d;
    } 
    else 
    {
        // Found IoP, swap the location:
        _swap( node, iop );
        std::swap( node, iop );
        // Remove the swapped node (at iop's position):
        return _remove(iop);
    }
}
```