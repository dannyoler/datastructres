# Lab 9 Heap Sort

In this lab, we will implement sorting with heaps and
perform some timing analysis compared to your binary search tree
implementation.

**If your binary search tree code from those previous assignments does
not work properly, you will not be able to complete this lab. Be sure
your previous code works properly.**

# Part 2: Implementing Heaps and Sorting

You are provided a new main() function and the declaration of a new
heap data type to store plain integers.

```
struct heap {
	int *A;
	size_t n_max;
	size_t n;
};

```

Notice that the heap stores a simple array, A, of integers. This array
will be dynamically allocated and managed.

Your function prototypes are:
```
int heap_init(struct heap *h, size_t n_max);
int heap_insert(struct heap *h, int data);
int heap_delete(struct heap *h, int *p_min);
void heap_destroy(struct heap *h);
```

In addition, some helper functions are provided to you:
```
int heap_validate(const struct heap *h);
void heap_print(const struct heap *h);
```

The heap_validate function tests the heap ordering property P <= L and
P <= R for all elements and returns 1 if the heap is valid and 0
otherwise.

This validation function is called in main after every insertion and
deletion to help make sure your code is working correctly.

The main function just reads a list of integers from a file and
inserts them into the heap. (This is very similar to the previous Tree
Sort code you have used.) It will then remove elements one-by-one from
the heap. Each removed element should be in ascending order.

We have provided some data files, reused from a previous lab, in order
to help test the correctness of your implementation. For example, the
file rand-100.txt contains 100 integers in random order, that the
program will print in order.

# Using the input generator

You can use the same imput generator Python script as in the previous
lab to help generate data for your analysis. You can run rand.py with
an argument specifying the number of integers in the range [0 to 10M]
to generate. 

# Part 2: Timing analysis
We want to perform timing analysis of sorting, not printing and
validating. So once your heap sort code is working correctly, comment
out the calls to heap_validate. And you can redirect the output to
/dev/null.


```
>time ./heap_full numbers.txt > /dev/null
0.80user 0.00system 0:00.81elapsed 99%CPU (0avgtext+0avgdata 680maxresident)k
0inputs+0outputs (0major+216minor)pagefaults 0swaps

```
This reports that the program took 0.81 seconds to execute.

Next, you should measure the runtime of your program for N=100, N=200,
etc. up to N=1M (but with a sequential percentage of 0%, i.e. entirely
random).

You are required to compare your heap sort code execution with the
tree sort execution time from your previous lab. You do not have to
re-run all of your tree sort experiments, but you do have to make sure
you use the same input files for heap sort and tree sort.

# What to turn in
You are required to submit your code, along with a report, **including
at at least two plots**. The plot should show the heap sort runtime
for up to N=1M items. The second plot should show the relative
performance of heap sort and tree sort. I.e. compute the ratio runtime
of heap sort / runtime of tree sort and plot for up to N=1M elements.

Include some explanations of what you observe and explain why you
think that one implementation is faster or slower than the other.

Your programs must run correctly, and must be free of memory misuse
and memory leaks. And be sure you are not printing extraneous
information to the output as you measure the runtime.
