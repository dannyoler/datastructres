## Introduction

Matrix multiplication is a common computing operation, but its performance is extremely sensitive to the implementation. In this project, you are asked to write a simple matrix multiplication program in C, and profile its performance. The tricky part here is that the matrix is actually a 1-D array interpreted as a 2-D array.

You can run the example program in several ways:
```
./matrix file_a file_b
```
will read a coefficient file for matrices A and B, and compute C = A * B.

#### Example:
```
>./matrix a_3_5.matrix b_5_3.matrix
a is a 3 by 5:
    2     0     7     4     9 
    1     1     3     2     3 
    1     8     9     0     9 

b is a 5 by 3:
    4     6     1 
    6     0     6 
    0     3     4 
    7     9     2 
    2     5     7 

c is a 3 by 3:
   54   114   101 
   30    48    44 
   70    78   148 
```

If you run the example program like this:
```
	./matrix 3 5 4
```
it will generate a random (3x5) matrix A, multiply it by a random (5x4) matrix B, and display the results.

```
a is a 3 by 5:
    3     6     7     5     3 
    5     6     2     9     1 
    2     7     0     9     3 

b is a 5 by 4:
    6     0     6     2 
    6     1     8     7 
    9     2     0     2 
    3     7     5     9 
    2     2     8     9 

c is a 3 by 4:
  138    61   115   134 
  113    75   131   146 
   87    76   137   161 
```

### Performance Analysis

When you finish implementing your code, you will measure it's performance with different input sizes. Measuring time in a Linux system is fairly easy.

```
> time ./matrix 200 200 200 0
real    0m0.078s
user    0m0.072s
sys     0m0.004s
```
Note that 78 milliseconds is a very small amount of time and very open to "noise" in your measurements. You should make your code run in the order of seconds. You should be able to analyze to complexity and anticipate how slow your algorithm will get as you increase the matrix size. 

Just take a note of real time and create a table for different sizes of square matrices. Plot your results, and create a short(1-2 pages) report, discussing the results. And submit the report(pdf file, please) in the same tarball as your assignment.
