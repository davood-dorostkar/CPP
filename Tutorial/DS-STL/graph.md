# Graph

## Vocabulary

**Graph** G is a collection of vertices and edges. Here inside the graph G, we have three sub graphs G1, G2 and G3.

G1 itself is a **connected** graph, because every node inside of G1 can be connected through the various edges.

I'll use the term **Node** and **Vertex** interchangeably.

the term **Edge** means the connection between two nodes or vertices.

**n** is equal to the number of vertices in the graph. 
**m** is equal to the number of vertices in the graph. 

**incident edge** is an edge that is directly connected to that node.

The **degree** of the node is the count of incident edges that it has.

**Adjacent vertices** is every single vertex that are connected to the node with an incident edge.

A **path** is a sequence of vertices through our graph.

A **cycle** is a path that starts and ends at the same node. 

A **simple graph** Is a graph that has no **self loops** and no **multi edges**. 

**Subgraph** is a subset of a graph that contain all of the vertices and all of the edges in that particular subset. it might be also referred as **components**

![](/images/graph.png)

## Simple math

### min number of edges

- not connected graph: $0$
- connected: $(n-1)$

### max number of edges

- simple graph: $\frac{n(n-1)}{2}$ ; hint: divided by to because A->B is equal to B->A (in undirected graphs)
- connected: $\infty$

### sum of all degrees

- $\sum_v 2m$

## Graph ADT
to implement a graph we need some data and functions in it:

### Data stored in graph

- vertices
- edges
- some data structure maintaining the structure between vertices and edges

### Functions

**Setters:**

- `insertVertex(K key)`
- `insertEdge(Vertex v1, Vertex v2, K key)`
- `removeVertex(vertex v)`
- `removeEdge(Vertex v1, Vertex v2)`

**Getters:**

- `incidentEdges(Vertex v)`
- `areAdjacent(Vertex v1, Vertex v2)`
- `origin(Edge e)` if graph is directional
- `destination(Edge e)` if graph is directional

### Edge list implimentation

we're simply going to have a list of vertices and a list of edges maintained in a vector or a hash table like data structure.

![](/images/edge-list-graph.png)

Here, the inserted removal runs in constant time, but you actually find things about the property of the graph and how connected they are. It's going to run in orders of the entirety number of edges in the graph. So, this can become very, very large in very large graphs and may not be a desirable outcome.

### Adjacency matrix implementation

**simple matrix**

it only shows if there is an edge or not


![](/images/adjacency-matrix.png)

**more smart matrix**

while we represent everything with zeros and ones, I think we can do better than that in our adjacency matrix. 

So instead of having a one here, we're going to have a pointer that points directly to my edge list which contains u which is the edge between u and v.

![](/images/smart-adj-matrix.png)

we can see that these operations are going to become much much faster than some of the operations beforehand because we can find out what all the incident edges are far faster than we could have by just going through the entire edge list.

we're able to optimize whether or not we can check if two vertices are adjacent or not, and we can do that check in `O(1)` time. This is an amazing result if the algorithm we care about is going to care about whether or not two nodes are connected. The cost of this is an additional runtime when we insert a vertex and remove a vertex so we see that we have our first trade-off between the different algorithms that we have.

### Adjacency list implementation

we have pointers that come off of a linked list inside from our set of vertices that link back to the edge list, and the edge links list then links back to the linked list element inside of my adjacency list. So we have pointers that are going both between my list of nodes as well as my list of edges.

![](/images/adj-list-graph.png)

This is a crazy mess of pointers, complicated to think about an implement. But see how great the running times are.

### Performance

| in terms of O()   | edge list | adj matrix | adj list             |
| ----------------- | --------- | ---------- | -------------------- |
| space             | $n+m$ ✅   | $n^2$      | $n+m$  ✅             |
| insertVertex(v)   | 1 ✅       | $n$        | 1 ✅                  |
| removeVertex(v)   | $m$       | $n$        | $deg(v)$ ✅           |
| insertEdge(v,w,k) | 1         | 1          | 1                    |
| removeEdge(v,w)   | 1         | 1          | 1                    |
| incidentEdges(v)  | $m$       | $n$        | $deg(v)$ ✅           |
| areAdjacent(v,w)  | $m$       | 1 ✅        | $min(deg(v),deg(w))$ |

we see the adjacency matrix is best if we care about the areAdjacent operation. But on the other hand, if we care about inserting and removing vectors as well as checking out the list of all of the incident edges, we can see the ideal running time is for an adjacency list or in some cases, just as great for an edge list. 

## C++ Implementation

### std::unordered_set

A set contains value copies of objects, and it contains no duplicates; inserting
the same item twice has no effect. In C++, the `std::unordered_set` is used for this purpose. Unlike the `unordered_map` type, the keys for an unordered set do not have associated values. We only care whether a given key has been
inserted or not.

```cpp
std::unordered_set<int> favoriteNumbers;

favoriteNumbers.insert(7);
favoriteNumbers.insert(42);
favoriteNumbers.insert(42); // no effect

favoriteNumbers.size(); // size of set
favoriteNumbers.empty(); // is the set empty?
favoriteNumbers.count(42); // does 42 exist?
favoriteNumbers.erase(42); // remove item
```

### Other options for a set

hashed containers that STL offers may not be optimal in some cases. 
- There does also exist an ordered type `std::set` which is based on a binary tree implementation instead of hashing, and consequently uses the `<` and `==` operators to arrange items instead of `std::hash` and `==`.
- It is also possible to use any of the other ordered STL containers such as `std::vector` as a general purpose ordered set (as long as you maintain them in a sorted order).
- there are some utility functions in `<algorithm>` that can let you compute set union and intersection efficiently.

> In your real-world projects, you would want to profile the performance of several options and see what works best. 