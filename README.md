This library implements some simple methods for matrix operation in C such as: matrix addition, matrix multiplication, matrix inversion and etc.
It differs from V1 by the fact that the matrices are allocated using a pointer to pointers rather than organizing the data in one array. some advantages disatvantages: 
Advatages:
1. easier to code and implement algorithms when one can write A[i][j] instead of \*A(i+A->cols\*j) as implemented in V1.
2. It offers a much better time performance when swapping between rows, sin ce row swapping can be done by just a single swap of pointer value rather than O(n) swaps of data between rows.
3. Perhaps the biggest advantage is that allocating k times chunks of N bytes is much more likely to succeed than than allocating a continous chung of k\*N bytes due to how memory is managed in most operating systems.

Disadvantages: 
1. Using a pointer to pointers adds a significant memory overhead to smaller matrices.  
Also included are some python scripts to generate tests for this library in the python library. 
A test library is also implemented, specifically for mulitplication and inversion. You can test it yourself by doing the following steps:
1. generating tests using the python scripts provided
2. compiling the program using "make test" 
3. evaluate the output of the implemented function in C in comparision to the expected output from common python libraries (implemented in my script using existing numpy methods)

