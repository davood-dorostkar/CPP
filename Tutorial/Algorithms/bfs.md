# Graph traversal

Just like a tree, a traversal is going to visit every single node exactly once. but there are differences:

tree:

- ordered
- obvious start
- notion of completeness

graph:

- not ordered
- no obvious start
- no notion of completeness

> graph is going to be possibly looping around a whole bunch. We're going to have to maintain some data structure to ensure that we're not stepping on a node for a second time.

## BFS

we're going to visit all over adjacent nodes before we visit any of their adjacent nodes. So, if we do that, we're going to use the same data structure we used in trees. We're going to maintain a queue, and this queue is going to help us organize our traversal through a graph. 

regardless of how you order the incident nodes of a node, All of the incident nodes are visited before any of their incident nodes are visited. This property is going to hold for all implementations of a breadth-first search traversal.

## DFS

In a depth-first traversal, we want to go very, very deep very quickly. In a BFS, we used the queue structure to maintain our data structure. Here, we're going to maintain our data structure using a stack structure. 

![](/images/dfs.png)

we want to mark the K edge as a `back edge`, it gets us somewhere further back in our process. So just like a cross edge inside of a BFS, a back edge is going to be an edge that's not a discovery edge in a DFS. So I'm going to label it with dots just as I did with the cross edges.

> sSo notice we did this entire algorithm without ever thinking about a queue or stack data structure. We have an implicit stack going on based on the calling stack in our recursive algorithm. 

we have two different forms of doing a BFS and DFS traversal. Those two different forms of traversal are going to both run in `O(n+m)` time. Because we have to visit every single node exactly once and we have to visit every single edge exactly once. So there's no way we can do faster `O(n+m)` time, so both the BFS and DFS traversal are optimal traversal running optimal running times for a graph.