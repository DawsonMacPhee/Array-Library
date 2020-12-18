This is a collection of functions that work together to act as an array data structure.

Functions

    struct Performance *newPerformance()
        Creates a structure holding information about the efficiency of the array.
        
    struct Array *newArray(struct Performance *performance, unsigned int width, unsigned int capacity)
        Creates a new array with each index holding "width" number of bytes and the total array holding "capacity" number of indicies.
        
    void readItem(struct Performance *performance, struct Array *array, unsigned int index, void *dest)
        Copies the item at given index of array into the dest pointer.
        
    void writeItem(struct Performance *performance, struct Array *array, unsigned in index, void *src)
        Copies the item in src to the array at the given index.
        
    void constract(struct Performance *performance, struct Array *array)
        Removes the last element in the array by changing the maxsize.
        
    void freeArray(struct Performance *performance, struct Array *array)
        Free all the memory allocated to the array.
        
    void appendItem(struct Performance *performance, struct Array *array, void *src)
        Adds an item to the end of the array (does not increase capacity).
        
    void insertItem(struct Performance *performance, struct Array *array, unsigned int index, void *src)
        Inserts an item into the array at a given index.
        
    void prependItem(struct Performance *performance, struct Array *array, void *src)
        Adds an item to the begining of the array.
        
    void deleteItem(struct Performance *performance, struct Array *array, unsigned int index)
        Removes an item at a given index.
        
    int findItem(struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *). void *target)
        Performs a linear search on the array looking for the target and returns the item's index.
        Compares using the given compar function pointer.
        
    int searchItem(struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *). void *target)
        Performs a binary search on the array looking fo the target and returns the item's index.
        Compares using the given compar function pointer.

Files

    array.c
        Contains all the functions in the library
        
    array.h
        Contains all the function declarations for the functions in array.c
        
    test1.c - test8.c
        A collection of main functions to be used to test the array data structure
        
    names1.txt - names 3.txt
        Text files containing values to load as arrays for testing purposes

Usage (make)

    all
        Compiles all the functions for the library and creates test executables
        
    array.o
        Compiles all functions in array.c into an object file
        
    test1.o
        Creates object file test1.o
        
    test2.o
        Creates object file test2.o
        
    test3.o
        Creates object file test3.o
        
    test4.o
        Creates object file test4.o
        
    test5.o
        Creates object file test5.o
        
    test6.o
        Creates object file test6.o
        
    test7.o
        Creates object file test7.o
        
    test8.o
        Creates object file test8.o
        
    test1
        Creates executable test1
        
    test2
        Creates executable test2
        
    test3
        Creates executable test3
        
    test4
        Creates executable test4
        
    test5
        Creates executable test5
        
    test6
        Creates executable test6
        
    test7
        Creates executable test7
        
    test8
        Creates executable test8
        
    clean
        Removes the object files and executables
