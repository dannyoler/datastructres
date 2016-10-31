# Lab 8 Tree Sort

In this lab, we will implement sorting with binary search trees, and
perform some timing analysis of your sorting algorithms

**If your binary search tree code from those previous assignments does
not work properly, you will not be able to complete this lab. Be sure
your previous code works properly.**

You are provided a new main() function and you will reuse your binary
search tree implementation from your last lab, but there will be major
changes in your implementation. Specifically, you will store plain
integers, instead of key-value strings.


# Part 1: Program Changes
Copy-paste the relevant parts from lab 7 into the new dict_tree.c file
and make the following changes to your definition of a tree node:

```
struct tree_node {
	int data;
	struct tree_node *left;
	struct tree_node *right;
};
```

Your modified function prototypes are:
```
struct tree_node *tree_find(struct tree_node *root, int data);
int tree_insert(struct tree_node **p_root, int data);
```

Notice that your data is no longer a key-value pair struct, just a
plain integer. Modify your source code to accommodate the new data
type. This includes: changing your function arguments as described
above, the printf in the tree_print(), and the comparisons in
tree_insert() and tree_find().

For the comparisons, you can use a line similar to:
```
    int cmp = node->data < data ? -1 : 1;
```

When you first run your code against a file containing a list of integers,
you should see a printout all of the integers in sorted order from the
tree_print function.

```
>./dict_tree rand-100.txt
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 

tree count is 0
tree depth is 0
```

The file rand-100.txt contains 100 integers in random order, that the
program prints in order. (Notice that the count and depth printed out
are incorrect for now).

# Part 2: Sorting using Binary Search Trees

In order to sort values, it is not enough to just print the contents
of a BST in order. We would like to copy these out linearly into an
array. In order to do that, we need to write several helper
functions:

```
int tree_count(struct tree_node *node);
int tree_depth(struct tree_node *root);
int tree_items(struct tree_node *node, int *A, int idx);

```

The tree_count function will simply return the number of items in the
binary search tree.

The tree_depth function will return recursively find the depth of the
binary search tree. 

The tree_items function will recursively copy the items in a tree to
an array starting at position &A[idx]. It will return the count of
items it has copied into the array. By recursively invoking this
function with different values of idx, we can sort the input
data. This function is tricky to implement. 

The actual tree_sort function is provided to you. It will count the
number of items needed, allocate space for them, and copy them out
using tree_items().

Once your code is correctly sorting, the code in main() will print the
contents of your sorted array. ***The print out from tree_print and
from printing the sorted array should match exactly! ***

# Part 3: Using the input generator
We have supplied a Python script to help generate data for your
analysis. You can run rand.py with an argument specifying the number of
integers in the range [0 to 10M] to generate.

Example:
```
python rand.py 1000 > rand-1000.txt
```
This writes 1000 random integers to a file called rand-1000.txt.

An optional second argument specifies the sequential probability.
```
python rand.py 1000 .90 > p90-1000.txt
```
This writes 1000 integers to a file called p90-1000.txt, but
each integer has a 90% chance of being sequential to the previous
one.

Of course, to generate 1000 sequential integers, just run:
```
python rand.py 1000 1.0 > seq-1000.txt
```

First, you should generate input sizes for run time for N=100, N=200,
N=500, N=1000, N=2000, N=5000 items. Vary the sequential percentage
and record how the depth of the tree changes. Plot these in a graph.


# Part 4: Timing analysis
We want to perform timing analysis of sorting, not printing, so we'll
modify our previous code to not print elements as they're inserted or
looked up. Instead of commenting out your printfs as in previous labs,
this time you can redirect the output to /dev/null.

```
>python rand.py 1000000 > rand-1000000.txt
>time ./dict_tree rand-1000000.txt > /dev/null
1.75user 0.02system 0:01.78elapsed 99%CPU (0avgtext+0avgdata 31888maxresident)k
0inputs+0outputs (0major+8017minor)pagefaults 0swaps
```
This creates a file containing 1M random integers, runs the program,
and reports that the program took 1.78 seconds to execute.

Next, you should measure the runtime of your program for N=100, N=200,
etc. up to N=1M and sequential percentages of 0%, 25%, 50%, 75%, 90%,
and 100%.

# What to turn in
You are required to submit your code, along with a report, **including
some graphs**. The first graph should show how the height varies for
different sequential percentages up to N=5000 items. The second should
show plot the runtime for up to N=1M items.

Include some explanations of what you observe and explain why you
think that one program is faster or slower than the other.

Your programs must run correctly, and must be free of memory misuse
and memory leaks. And be sure you are not printing extraneous
information to the output as you measure the runtime.
