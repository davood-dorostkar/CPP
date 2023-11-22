# Dijkstra's Algorithms

This algorithm is very similar to Prim's Algorithm, but it's completely different. In the sense that, instead of finding the minimum spanning tree, Djikstra's Algorithm is going to find us the shortest path on a graph. 

the only difference now is as we update the weight. So if the weight is lower than positive infinity, we're going to update it only if, not just the edge weight is lower. But the entire distance from the root node or the starting point to the new point.

> Notice that these edges are directed edges, that they have a source node, and a destination, so every edge has an arrow.

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

## Edge Cases

### a single heavy-weight path vs multiple light-weight paths

Dijkstra's algorithm is able to overcome the fact that there may be multiple different nodes that have to be taken.

![](/images/sssp-case1.png)
![](/images/sssp-case2.png)

### a single optimal heavy-weight path vs multiple light-weight paths

we find that even under the presence of a long path, Dijkstra's still finds the shortest path.

![](/images/sssp-case3.png)
![](/images/sssp-case4.png)

### negative edges 

Dijkstra's algorithm is not able to find the shortest path. In fact, the shortest path to see involves looping around to get back to see an infinite number of times because every time we loop around, our path gets five units shorter. the shortest path keeps looping around and Dijkstra's algorithm is unable to account for this. 

![](/images/sssp-case5.png)
![](/images/sssp-case6.png)

Any time you have a `negative weight cycle`, there does not exist a shortest path. So, we absolutely cannot run `any` shortest path algorithm with the existence of a negative weight cycle. 

> Dijkstra's algorithm does not work under any graph that has any negative weights. So, not even a negative weight cycle, not even in negative weight that's not part of a cycle because Dijkstra algorithm assumes that everything going out from the source is monotonically **increasing**. So, one of the biggest weaknesses is that Dijkstra's algorithm fails, as soon as you bring in a negative weight edge.

### negative edge cycles

There's going to be more advanced algorithms that help us solve problems on graphs that look at negative weight edges. Though as soon as we have a negative weight cycle, there will never be a shortest path, because mathematically that shortest path is infinite.

### undirected graphs

![](/images/sssp-case7.png)

we see that Dijkstra's algorithm has no problem.

> Dijkstra's algorithm works really great on any graph no matter what the structure is, so long as every single edge weight is positive.

## Performance

the running time is going to be very similar to prim's algorithm. the difference is as we find an edge that smaller, we're going to update the weight of that edge. So, here we see that the updated cost of the edge, only happens when we decrease. Using a special type of heap, called the `Fibonacci heap`, we're able to optimize the Dijkstra's algorithm running time to an amazing runtime. So, the total running time here, is going to be order of `m + n log(n)`, times the log of the number of nodes in this graph. This running time is the absolute best running time, that you can get in any shortest path algorithm.

it's a little bit more than a traversal. That extra `log(n)` to the end, allows us to find the shortest path, while just traversing over all of the edges and nodes.

## Landmark Path Problem

instead of running Dijkstra algorithm which takes an extra `n log(n)`, We can just run a minimum spanning tree algorithm like a breadth-first search.

![](/images/landmark.png)

### Add Constaint: middle point

Here, I don't want to just go from A to G, I want to go to A to G via landmark L.

![](/images/landmark-middle.png)

using two applications of a breadth-first search (A-L and L-G) we can see the minimum spanning tree that it creates is going to go ahead and find a fantastic solution to this problem.

#### Going further: In total running time, what is the absolute fastest time that we can find this entire path?

because we have a bidirectional graph where all of the weights of all the edges are equal and we're creating spanning trees. We know the path from L to A is also the shortest path from A to L. So as long as you find that L to A shortest path we know that that can be used for A to L. So by running BFS just once starting with L, we get a spanning tree that shows us the shortest path.