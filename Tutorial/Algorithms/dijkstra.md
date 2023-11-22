# Dijkstra's Algorithms

This algorithm is very similar to Prim's Algorithm, but it's completely different. In the sense that, instead of finding the minimum spanning tree, Djikstra's Algorithm is going to find us the shortest path on a graph. 

the only difference now is as we update the weight. So if the weight is lower than positive infinity, we're going to update it only if, not just the edge weight is lower. But the entire distance from the root node or the starting point to the new point.

![](/images/dijkstra.png)

We know the precise path to every single node from A using Dijkstra's Algorithm. Because of this, we call Dijkstra's Algorithm a `single source shortest path` or an SSSP algorithm. Dijkstra's Algorithm takes a single source, in this case, our single source was a node A. And from node A, it finds the shortest path to every single other node in our connected graph. This means we know the distance from A to B, A to C, A to D, A to E. Dijkstra's Algorithm only finds us a single source shortest path. So we have to give it a source node and it was always going to start from that source node. It does not know the path from D to E unless we make B the source node. 

## Implementation

```cpp
DijkstraSSSP(G, s):
    foreach (Vertex v : G):
        d[v] = +inf // each node's weight
        p[v] = NULL // each node's parent
    d[s] = 0

    PriorityQueue Q // min distance, defined by d[v]
    Q.buildHeap(G.vertices())
    Graph T // "labeled set"

    repeat n times:
        Vertex u = Q.removeMin()
        T.add(u)
        foreach (Vertex v : neighbors of u not in T):
            if cost(u, v) + d[u] < d[v]:
                d[v] = cost(u, v) + d[u]
                p[v] = u
```