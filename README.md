# Ford-Johnson merge-insertion sort

## Overview

This project implements the Ford-Johnson merge-insertion sort algorithm, for both `std::vector` and `std::deque` containers. It takes a sequence of unique positive integers as input and sorts them using a hybrid sorting algorithm that combines the advantages of both merge sort and insertion sort. It aims to reduce the number of comparisons needed compared to a pure insertion sort, especially for larger datasets.

## Features

*   **Merge-Insertion Sort:** Implements the efficient merge-insertion sort algorithm.
*   **Time Complexity Analysis:** Measures and compares the time taken to sort using two different containers type.
*   **Testing:** Includes a comprehensive test suite to ensure correctness and performance.

## Building and Running

### Prerequisites

*   C++ compiler with C++17 support (e.g., g++)
*   Make

### Compilation

1.  Clone the repository:

    ```bash
    git clone <repository_url>
    cd PmergeSortAlgo
    ```

2.  Compile the project using `make`:

    ```bash
    make
    ```

3. Run the test using `make test`:

    ```bash
    make test
    ```

### Usage

```bash
./PmergeMe <positive_integer_1> <positive_integer_2> [...]
```


### References
- [Merge-insertion sort](https://en.wikipedia.org/wiki/Merge-insertion_sort)
- [Art of Computer Programming, Chapter 5, The: Volume 3: Sorting and Searching, 2nd Edition
Donald E. Knuth](https://learning.oreilly.com/library/view/the-art-of/9780321635792/)
- [Ford-Johnson merge-insertion sort](https://codereview.stackexchange.com/questions/116367/ford-johnson-merge-insertion-sort)
