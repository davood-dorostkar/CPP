# B-Tree

## Motivation

The goal of a B-Tree is to create a data structure that's going to perform extremely well in both main memory, as well as in on disk. Specifically we want to make as few disk seeks as possible. And in fact, I decided the term disk seeks, but This might be on the cloud somewhere, or this might be anywhere else. 

## Definition

A B-Tree is constructed by having a node that contains a number of keys (rather than just one). Each of these keys are going to have a pointer to another tree node inside of it.

![](/images/b-tree.png)

## Order
The order of a B-Tree refers to the size of the nodes, note the fact that the keys are in sorted order. The order of a B-Tree is the maximum number of keys that a given node can have, plus one. So for example, here's an example of a B-Tree of order 9. having 8 keys in this node. The goal of every single B-Tree is to minimize the number of network packets, disk seeks, or whatever operation we have to get at the data, so we want to minimize the seeks to reach our data.

A b-tree of order m is specifically a tree that contains nodes of order m. Each node can contain no more than m-1 keys. 

## B-Tree Insertion
- All keys within a node are in sorted order.
(Note: These are two different meanings for the word "order".)
- Each node contains no more than m-1 keys.
- Each internal node can have at most m children,
so a B-tree of order m is like an m-way tree.

## Properties
1. All keys within a node are in sorted order.
2. Each node contains no more than m-1 keys.
3. Each internal node has exactly one more child than key
(at most m children, so a B-tree of order m is like an m-way tree).
- A root node can be a leaf or have [2, m] children.
- Each non-root, internal node has [ceil(m/2), m] children.
4. All leaves are on the same level

[A visualization for better understanding B-Tree](https://www.cs.usfca.edu/~galles/visualization/BTree.html)

## Search
```cpp
bool Btree::_exists(BTreeNode & node, const K & key) 
{
    unsigned i;
    for ( i = 0; i < node.keys_ct_ && key < node.keys_[i]; i++) 
    { 
        if ( i < node.keys_ct_ && key == node.keys_[i] ) 
        {
            return true;
        }
    }

    if ( node.isLeaf() ) 
    {
        return false;
    } 
    else 
    {
        BTreeNode nextChild = node._fetchChild(i);
        return _exists(nextChild, key);
    }
    
}
```

## Analysis

- The height of the B_Tree determines maximum number of seeks possible in search data.
- and the height of the structure is log<sub>m</sub>(n).
- Therefore The number of seeks is no more than log<sub>m</sub>(n).
- B-Trees perform better than other trees in terms of `seek`; not to be confused with `Big-O` performance (it is not better).

## Fun facts
-  many BTrees are going to run in order of a thousand or more. So, if we consider a BTree of order of `1,001`, we see that that tree is going to take a number and break it up by however many commas are in that number. So, if you have `1,000,000,000,000` pieces of data, you've got `4` different commas in that number, which means you're only going to have to do `4` seeks to look through all three trillion pieces of data. This is absolutely amazing given how much data you can store and in this small amount of disk seeks you need to do. In comparison, if you had that much data in an AVL tree, you'd have to do over `30` seeks.
- So, a BTree is an optimized algorithm to optimize around the idea of doing as minimal disk seeks as possible when all of our data is can't fit in main memory. It's a little bit of a hybrid between a classical tree and a pure disk algorithm. So, we have the best of both worlds by combining two different algorithms.