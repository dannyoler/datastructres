# Lab 5

In this lab, we will extend our singly linked-list implementation of
an associative array (also known as dictionary). As in the previous
lab, you will create an associative array to store keys and values
with a simple singly linked-list implementation. But you will use
doubly-linked lists.

Use the following definition of a linked list node:

```
#define MAX_KEY_LEN (32)
#define MAX_VALUE_LEN (32)

struct list_data {
  char key[MAX_KEY_LEN];
  char value[MAX_VALUE_LEN];
};


struct list_node {
	struct list_data data;
	struct list_node *next;
	struct list_node *prev;
};

struct list_node *head = NULL;
```
You have to implement the following functions for your code:

```
void list_print(struct list_node *head);
struct list_node *list_find_exact(struct list_node *head, const char *key);
struct list_node *list_find_before(struct list_node *head, const char *key);
int list_insert(struct list_node **head, struct list_node *before,
                struct list_data data);
void list_remove(struct list_node **p_head, struct list_node
*remove_node, struct list_data *p_data);
void list_destroy(struct list_node *head);
```

The exact semantics for each function are provided in the example
code, and several test files are included. Luckily, you will be able
to re-use and extend some of the previous lab's code, but you may only
reuse your own code. Be careful! In addition to the new removal
function, some of the function implementations
have to change for doubly-linked lists.

Simply typing `make` will compile your code.

Your code will output the entire list after every insertion. After inserting all of the key­value pairs There is an additional command­line argument that takes in a list of entries to search for and prints the value for each entry or an error if no entry is found.

Example run command will look like this:

```
> ./dict 1 <inputfile> <lookup_file> <removal_file>
```
(The 1 indicates that the data should be sorted.)

This example shows inserting entries, looking them up, and removing
them.

```
>./dict_full 1 dict_in_00.txt lookup_00.txt remove_00.txt 
Insert hello world in sorted order
hello world
Insert spam eggs in sorted order
DEBUG: hello <= spam
hello world
spam eggs
Insert foo bar in sorted order
DEBUG: hello > foo so return (nil)
foo bar
hello world
spam eggs
Insert aardvark blagh in sorted order
DEBUG: foo > aardvark so return (nil)
aardvark blagh
foo bar
hello world
spam eggs
Found: hello world
Found: spam eggs
Found: foo bar
Found: aardvark blagh
Failed to find: notpresent
Now removing elements.
Found node to remove: hello world
Removed node: hello world
aardvark blagh
foo bar
spam eggs
Found node to remove: spam eggs
Removed node: spam eggs
aardvark blagh
foo bar
Found node to remove: foo bar
Removed node: foo bar
aardvark blagh
Found node to remove: aardvark blagh
Removed node: aardvark blagh
Failed to find node to remove: notpresent
```

Read the code to understand the details of command line arguments. Replace `dict` with `dict_full` to run the sample executable. Note that your executable must give the exact same output as our executable. This doesn't mean that what we have is perfect, so if you believe that your results are correct and ours wrong, let us know as soon as possible.

**VERY IMPORTANT** Please read the skeleton code we gave you carefully
  line by line and understand it before you start coding. Many of you
  have struggled trying to implement a functionality that is already
  provided to you.


