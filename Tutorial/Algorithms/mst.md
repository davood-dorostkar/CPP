# Minimum Spanning Trees

We want to find the tree that can be placed over graph that connects every single vertex in the graph, using the minimal total number of edges, or the minimal weight of all of the edges among the graph.

- **input**: some undirected graph G with usually edge weights
- **output**: a graph $G^\prime$ that is 
  1. a spanning tree of the graph
  2. It needs to be a tree so it needs to not have a cycle because it needs to visit every node exactly once
  3. It has a minimal total weight across all of the possible spanning trees

This is going to be a really important application whenever we want to see what is the connectivity of any given system, and how can we easily minimally travel between two different locations.

## Kruskal's

### Algorithm
1. we have a list that can be maintained as a [minimum heap](/Tutorial/DS-STL/heap.md) that is always going to allow us to return on the minimum edge in the entire graph.
2. we're also going to have every single vertex as initially its own [disjoint set](/Tutorial/DS-STL/disjointSet.md).
3. we're going to always remove the minimum element from the heap, and then check if that element, if the two vertices that are part of the element are already in the same set. If they are we do nothing. If they're not the same set, we union those sets together.

![](/images/kruskal.png)

now we have one single spanning tree where from any single node on the spanning tree, we can visit every single other node on this graph. This is an amazing property and Kruskal's algorithm guarantees that not only is this a spanning tree, but this is one of the smallest possible spanning trees for this entire graph. You cannot create another spanning tree that has a smaller value than this particular spanning tree right here. This result is a fantastic result that allows us to know that this is going to be a minimal path that can take in our system to move around, as long as we care only about the path that spans every single node.

### Implementation (pseudocode)

```cpp
KruskalMST(G):
    DisjointSets forest
    foreach (Vertex v : G):
        forest.makeSet(v)

    PriorityQueue Q // min edge weight
    foreach (Edge e : G):
        Q.insert(e)

    Graph T = (V, {})

    while |T.edges()| < n-1:
        Edge (u, v) = Q.removeMin()
        if forest.find(u) != forest.find(v):
            T.addEdge(u, v)
            forest.union( forest.find(u),
            forest.find(v) )
    return T
```
### Performance

| Priority Queue: | Heap     | Sorted Array |
| --------------- | -------- | ------------ |
| Building        | $m$      | $m log(m)$   |
| Each RemoveMin  | $log(m)$ | 1            |

| Priority Queue:    | Heap            | Sorted Array   |
| ------------------ | --------------- | -------------- |
| Total Running Time | $m + m  log(m)$ | $m log(m) + m$ |

> So notice that the running time is going to be `m log(m)` in both cases.

> here we completely ignored the running time to create a disjoint set of N items which is going to be N. So we could say plus N here, but notice that N is always going to be smaller than the number of edges.

## Prim's

we're going to utilize a fact about a graph which is that if you have two distinct components `U` and `V`, the minimum edge that connects U and V must be part of some minimum spanning tree. 

If we find the edge `e` that splits up partition, we know that this edge `e` has to be part of a minimum spanning tree.

![](/images/partition-property.png)

### Algorithm

1. we start with just a single node and we looked at partition that separates that node in the labeled set from every other node. 
2. We find the minimum edge that bridges that partition, add it to our labeled set, and look at the next partition and find the minimum node that spans that partition. 

This whole process ends up creating a spanning tree that is a minimum spanning tree of the graph.

![](/images/prim.png)

### Implementation (pseudocode)

```cpp
PrimMST(G, s):
    Input:  G, Graph
            s, vertex in G, starting vertex

    Output: T, a minimum spanning tree (MST) of G
    
    foreach (Vertex v : G):
        d[v] = +inf
        p[v] = NULL
    d[s] = 0

    PriorityQueue Q // min distance, defined by d[v]
    Q.buildHeap(G.vertices())
    Graph T // "labeled set"

    repeat n times:
        Vertex m = Q.removeMin()
        T.add(m)
        foreach (Vertex v : neighbors of m not in T):
            if cost(v, m) < d[v]:
                d[v] = cost(v, m)
                p[v] = m
    return T
```
### Performance

|                  | Heap                | Unsorted Array |
| ---------------- | ------------------- | -------------- |
| Adjacency Matrix | $n^2 + mlog(n)$     | $n^2$          |
| Adjacency List   | $nlog(n) + mlog(n)$ | $n^2$          |


#### Sparsity

- Sparse graph: $m \sim n$ (the number of edges and nodes are about the same)
- Dense graph: $m \sim n^2$ (every node is connected to nearly every other node)

You can see that if we use a heap plus an adjacency list, we have just a nearly similar run time, as we did with Kruskal's algorithm.

In fact if we consider a sparse graph, this is going to be `m log(n) + m log(n)` which means that the total running time is the exact same thing as Kruskal's algorithm.

If we have a dense graph, it becomes `n^2 log(n)`, which is greater than `n log(n)`.

> The time it takes to build our minimum spanning tree, is going to always be proportional to the number of edges in the graph times the log of the number of edges in the graph, no matter what algorithm we use. In a dense graph you're going to find that that run time is going to be M log M in both cases.