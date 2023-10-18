# Heap

In this data structure, we don't want to maintain a total ordering, we don't want a sorted piece of data because we know that sorted data takes a really long time to maintain.

![](/images/heap.png)

A Priority Queue is where every single value can have a priority, and we can remove based on the value that has the highest or lowest priority. 

## Definition
- Either we have a tree that has no nodes
- or we have a tree that has both a right and a left child such that both the left and the right child nodes are larger than the root node(in min-heap).

## Properties

- The only property about the heap that matters is everything that's a descendant from a node has to be larger (in a min-heap) or smaller (in a max-heap) than the node itself.
- what we'll do is we'll always ensure a heap is a [complete](/Tutorial/DS-STL/tree.md) tree.

## Resulting Representation
- When we have this tree, we represent this tree in memory as an array.
-  inside of our array, we can always navigate to our parent not by having a parent pointer, but we know our parent is equal to our index divided by two (here we start indexes from 1).
-  we can always go to our parent and child quickly, and we know that these operations all have simple mathematical formulas that allow us to compute them extremely quickly.

```
parent = i/2
LChild = i*2
RChiled = i*2 + 1
```

![](/images/heap-navigation.png)

## Operations

### insert

```cpp
template <class T>
void Heap<T>::_insert(const T & key) 
{
    if ( size_ == capacity_ ) { _growArray(); }
    item_[++size] = key;
    _heapifyUp(size);
}
```
Whenever we grow the array, we're doubling in size, so we know that this is an amortized O of one operation
```cpp
template <class T>
void Heap<T>::_heapifyUp( int index ) 
{
    if ( index > 1 ) // check whether it is the root
    {
        if ( item_[index] < item_[ parent(index) ] ) 
        {
            // if the new item is less than its parent, swap them recursively upward
            std::swap( item_[index], item_[ parent(index) ] );
            _heapifyUp( parent(index) );
        }
    }
}
```
### removeMin

- we use a clever approach of actually just swapping the very last element on our tree with root, to ensure that we don't mess up the tree structure itself. we haven't ruin our tree structure, we've just ruined the order.
- then we heapify down by comparing the root with the least of its children

![](/images/heap-removemin.png)
```cpp
template <class T>
void Heap<T>::_removeMin() 
{
    // Swap with the last value
    T minValue = item_[1];
    item_[1] = item_[size_];
    size--;
    // Restore the heap property
    heapifyDown();
    // Return the minimum value
    return minValue;
}
```
```cpp
template <class T>
void Heap<T>::_heapifyDown(int index) 
{
    if ( !_isLeaf(index) ) 
    {
        T minChildIndex = _minChild(index);
        if ( item_[index] > item_[minChildIndex] ) 
        {
            std::swap( item_[index], item_[minChildIndex] );
            _heapifyDown( minChildIndex );
        }
    }
}
```

### Build heap
for turning an existing data structure (array or tree) we have 3 options:

1. sort it 
2. heapify up

```cpp
template <class T>
void Heap<T>::buildHeap() 
{
    for (unsigned i = 2; i <= size_; i++) {
        heapifyUp(i);
    }
}
```
3. heapify down (this method is most efficient)
```cpp
template <class T>
void Heap<T>::buildHeap() 
{
    for (unsigned i = parent(size); i > 0; i--) {
        heapifyDown(i);
    }
}
```
- we're able to perform a series of just N over 2 heapifyDown operations to ensure it is heap.
-  the key reason that we're actually care about heaps, Is the fact that, given any sort of data structure, any array representation, we can build a heap notation of that in just `O(n)` time. Far shorter than sorting the array, far shorter than inserting into a binary tree.

## Runtime Analysis
1. we can do an insert and remove operation by just doing simple tree operations. we know that these are `log(n)` operations because we have a complete tree. 
2. we can build a heap in `O(n)` time. 

### Heap Sort
there are 3 steps:
1. Build a heap - `O(n)`
2. n calls of removeMin - `log(n)`
3. swap elements to order list (may not be necessary)

- worst case runtime is `n * log(n)`
- using this zeroth index that we leave completely empty, you can do a heap sort without using any additional space than the space you have in this array