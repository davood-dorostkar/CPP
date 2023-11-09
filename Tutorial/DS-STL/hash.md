# Hash

this algorithm's often computer science's favorite algorithm, because you're going to find the results of hashing, it's going to give us a fantastic run time for certain operations.

And our goal of a hash table is to be able to map every single key to the value that it contains in that dictionary, and do so as quickly and as efficiently as possible.

![](/images/hash.jpg)

## Hashing Components

1. **hash function**: that's going to map our input space into an array index. So if we have a string as our input, we need to map that string from the string input type down to some integer between 0 and n. 
2. **array**: that's going to store data
3. **collision handler**: a strategy that allows us to handle the collisions that occur when our hash function maps two different values to the same point in the array.

## Hash Function

examples of hash functions:

- Onto function

subtract letter `A` from the first letter.

problem:

1. different inputs get same output values.

![](/images/onto-function.jpg)

- petals around the rose

roll a number of dice for and give you a number of what that dice says. 

problems:

1. The only way we're going to count petals is for a three we count two or for a five we count four. So every single odd number is never going to be reached in our hash table. This hash table is not going to be perfectly filled.
2. we may have a lot of rolls that contain just a single five. So there may be a lot of different values that get mapped to the value four.

![](/images/petals-roses.png)

### Parts of a Hash function
1. transform an input into an integer. So I just need some generic functions that's going to turn whatever my input is into a numeric form. 
2. a compression to make sure that the hash function is within the bounds of the array. The compression can be easily done with a mod operator. So I can do that using `%N`.

### Characteristics of a good hash function
1. Computation time
   
   We want to ensure the time to compute a hash is going to be `O(1)`. it must be a very fast function.


2. Deterministic
   
   a hash function must be deterministic. if we hash a string once, and we hash the exact same string a second time, those two results must be exactly the same.


3. Satisfy the SUHA
   
   or simple uniform hashing assumption.  it means that given two values, so we're going to take the hash of some value a and the second hash function of b. When we hash these two functions, we need the probability of the hash of a to be equal to the hash of b, to be equal to one over the size of the array, if a does not equal b.

   `P(a)=P(b)=1/N | a!=b`

   it is obvious that the petals around the rose function does not satisfy this.

   ### Difficulties
   for small values of input, this is going to be extremely easy. but instead of just mapping to a small key space, we have to consider the fact that our circle maybe here or maybe way out here. In doing so, we have different parts of that key space when you consider all of these subspaces of the key space needs to be uniform. This is incredibly difficult to do.

   ![](/images/hash-keyspace.png)

## Collision Handling

### Separate Chaining
in this strategy we're going to dive into the array but you treat it more like a linked list. Every time we run into a collision, we'll simply add the element to the linked list.

You can imagine the very worst case of this algorithm would be quite bad. If we had a hash function that always kept returning to the same value, we have a linked list that grows in size equal to exactly the value of the number of data in our hash table. That means our algorithm is going to run in `O(n)` for searching. 

![](/images/separate-chaining.png)

**load factor**

The load factor of the table `alpha` is the number of elements inside of the table divided by the size of the table itself. So, little n divided by big N. This term determines how full the table is.

A load factor of two means on an average, every single node has two items in the linked list. as a load factor grows, the amount of time it takes to run this algorithm is also going to grow. 

### Probing
 In probe-based hashing, simply look at the next location inside of the array. By looking at the next location, we're just going to probe ahead until we find an empty slot. Once we find that empty slot, we can write the value right there. 

 ![](/images/probing.png)

 problems:

 1. when the array is near full, We hade to look at every single element in the array to find an empty place.
 2. we're going to find the runtime of this is going to be problematic.
 3. **primary cluster**; we have a number of elements that have been filling up right here in this space. It's getting pretty crowded, lots of things are hashing here. So now if we hash to anything in this point, it's always going to be probed until this point right here. So we have something called a primary cluster.

   ![](/images/primary-cluster.png)

   even with the uniform distribution that based on the laws of probability, we end up with a cluster that has a primary set of values all in a single block while the rest of the arrays is going to be fairly sparse. The remedy to this Is we want to make sure our probing isn't exactly linear.

### Double Hashing
So here, we have `h1` our first hash function, While `h2` will be our second hash function. So our second hash function, we want to be not 0 and less than the size of the array.

for example `h(k) = k%7` can be `h(k,i) = (h_1(k) + i*k_2(k)) % 7`

this approach of randomizing how much we step in each time is going to avoid the idea of a primary cluster.

### Performance
> the big idea you should take from this is no matter what strategy we use, as our hash table becomes full we're going to see our performance degrade.

![](/images/load-factor.png)

![](/images/hashing-performance.png)

Notice that the running time of this algorithm is extremely fast given an alpha value less than 0.6. What this means is it doesn't matter how much data's in our array. Our array can have a billion records, but because alpha is only the ratio between the actual amount of data in an array and the size of the array. As long as we can keep expanding our array, we can find that our running time is absolutely phenomenal.

>  as long as we keep alpha constant, running time is going to have and `O(1)`. Because the running time is going to be proportional to alpha, not proportional to the amount of data in the array. 

### Rehashing
As we learned earlier, when we resized an array, we always want to double that array. And in doubling that array, we're going to have to do something called rehashing. 

So rehashing is the idea that if we take a value from the array, the original spot it hashed to is not necessarily going to be the new spot it hashes to, due to the compression aspect inside of our hash function. Remember, hash function gets into integers and then mods it by a value.

## Analysis
### Best Collision Strategy

- large pieces of data
  You'd rather use a pointer in LinkedList to store that data somewhere else. something like separate chaining. 
  
- Remember, the array operations are memory optimized because they're sequentially located in memory. So, if we care only about raw structure speed and we know our data itself is fairly small, we can use a close hashing technique such as linear probing, or double hashing.

### Hash table vs AVL tree
So, an AVL tree also provides a dictionary implementation. AVL do a great job with range finding a nearest neighbor. A hash table does an absolutely terrible job with that. You can't say what value is near 42 because 42 hashes to one particular spot in the array, and the value of around 42 may have nothing to do with 42 inside of the actual final array. so choose the right algorithm for a right application.

we want to use a tree-like structure if we ever need range finding or nearest neighbor. We want to use a hash table if we're always going to have the exact key. If we're always doing lookups, hash tables are phenomenal.

## Hash tables in STL
A `map`, in fact, is an implementation of a red-black tree, so these operations are going to have a `log(n)` running time. a red-black tree is another kind of balanced tree that has similar performance to an AVL tree.

![](/images/std-map-dict.png)

An `Unordered map` is the hash table implementation in C++, considering that hash tables do not have range finding abilities.

we have different functions because we have a hash function table like load factors. 

![](/images/unordered-map-dict.png)