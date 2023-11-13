# Disjoint Set

## Set indentity
the identity of each set is simply the value of its first element.

![](/images/disjoint-set.png)

## Union
union operation on disjoint sets means to merge two sets into one set.

the "disjoint sets" data structure is also sometimes referred to as the "union-find" data structure, because of its primary methods, "union" and "find". However, there is another important thing to watch out for: In C and C++, the word `union` is reserved for a specific language feature, so you can't use "union" as a name for a variable or function. Instead you have to use a variant such as "set_union" and so on.

## Implementation-naive approach
when merging two sets, we must update the set indentity for each element in the second set to that of the first one. but we do not know what elements are in the same set. the naive approach is to check every element in the whole array and update them as needed.

## Implementation-Uptree

each element points to `-1` if it is not union-ed to something else yet. after union 3 to 0, you see that now 3 points to 0. it makes a tree like structure that all point upward. (need more reading)

![](/images/uptree.png)

to find the identity, you need to traverse up to the root. to union two sets, you only need to  update the second root to point to the first root. That's awesome. This amazing ability to update the union as quickly as possible in only changing one pointer.

![](/images/uptree2.png)

in this example the array will look like this (each element points to its parent, roots point to nowhere: -1):

| index    | 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   |
| -------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| identity | 4   | 8   | 5   | -1  | -1  | -1  | 3   | -1  | 4   | 5   |

## Uptree Performance

the running time of this UpTree is going to be `O(H)`, and the worst case, H is going to be equal to N (like a linkedlist). If our worst case `O(N)`, then we've done no better than our naive implementation. So uptree is good, but has very bad worst case performance.

## Smart Unions
we could have a single identity node as a root node, and every single child could be right underneath that root node. So, notice that this tree is extremely flat. There's only a height of one in this entire tree. this is ideal and we want to keep our trees as similar as possible to this.


### Union by height
Now when we union two things together by unioning by height, what we're able to do is put the shorter tree onto the taller tree.

we didn't actually increase the total height of the tree at all and this is fantastic. 

to do that, instead of representing the root node as negative one always, we can represent the root of our tree as the negative value of the height

to ensure that the height is always negative (to not confuse the zero case), we not just simply use the height, we use the height negative minus one (`-h-1`). So, a height tree of `0` is going to have the value of `-1`. The height of tree of `3` is going to have the value of `-4`. 

one downside about union by height, is the height of every single element in child tree is being increased by 1.

### Union by size

instead of storing the height at every single root identity node, we're going to store the size of elements in that set.

In unioning by size, we're able to build up this tree to be an absolutely great tree that's always going to ensure that the height of the tree increases it with as few nodes as possible every step of the way.

> it doesn't actually matter if we union by size or union by height. That both of these algorithms ensure that we have a tree that is `O(log n)` in height.

## Path Compression

the second little hack I'm going to do is not just hacking on the union to make the union smart, but to also make sure that find is an incredibly intelligent algorithm.

the idea here is by ensuring that whenever we have a path to the root, we're going to go through and make sure that every element that we took along that path now points directly to the root node itself. To make it closer and closer to this ideal perfect tree where we are a root node and a number of another nodes underneath it.

every time we do a fine algorithm, we are compressing the path to be smaller, and smaller, and smaller.

## Performane

the running time of a disjoint set is not `O(1)`, but still is one of the best running times we ever see in computer science. The running time of this algorithm is something called the iterated log (`log*`).

![](/images/iterated-log.png)

2^65,000 is an absolute gigantic number. The iterated log of that is 5. This is so, so, so close to constant time. 

a series of `m` find and union operations on a set of size `n` take `m * log*(n)` time. this is so small.

> we're going to consider that the amortize average running time of our algorithm for all practical purposes is `O(1)*` time. meaning that it is slighlty different but we assume it 1.

