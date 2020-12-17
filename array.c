#ifndef __stdio_h_
#include <stdio.h>
#endif

#ifndef __stdlib_h_
#include <stdlib.h>
#endif

#ifndef __string_h_
#include <string.h>
#endif

#ifndef __array_h_
#include "array.h"
#endif

// Allocates memory for the struct 'Performance' and initializes its values
struct Performance *newPerformance(){
    struct Performance *performance = malloc(sizeof(struct Performance));
    if (performance == NULL){
        fprintf(stderr, "The allocation of memory for the Performance Struct has failed\n");
        exit(1);
    }
    performance -> reads = 0;
    performance -> writes = 0;
    performance -> mallocs = 0;
    performance -> frees = 0;
    return performance;
}

// Allocates memory for the struct 'Array' and intializes its values
struct Array *newArray(struct Performance *performance, unsigned int width, unsigned int capacity){
    struct Array *array = malloc(sizeof(struct Array));
    if (array == NULL){
        fprintf(stderr, "The allocation of memory for the Array Struct has failed\n");
        free(performance);
        exit(1);
    }
    array -> width = width;
    array -> nel = 0;
    array -> capacity = capacity;
    array -> data = malloc(width * capacity);
    if(array -> data == NULL){
        fprintf(stderr, "The allocation of memory for the data inside the Array Struct has failed\n");
        free(performance);
        free(array);
        exit(1);
    }
    performance ->  mallocs += 1;
    return array;
}

// Reads the data at given index and copies it to dest
void readItem(struct Performance *performance, struct Array *array, unsigned int index, void *dest){
    if(index >= array -> nel){
        fprintf(stderr, "readItem: the index you are trying to read has not been initialized\n");
        freeArray(performance, array);
        free(performance);
        exit(1);
    }
    void *indexPointer = (array -> data); 
    indexPointer = (char*)indexPointer + (index * (array -> width));
    memcpy(dest, indexPointer, array -> width);
    performance -> reads += 1;
}

// Writes the data held in src at the given index
void writeItem(struct Performance *performance, struct Array *array, unsigned int index, void *src){
    if(index > array -> nel || index >= array -> capacity){
        fprintf(stderr, "writeItem: the index you are trying to write to cannot be accessed\n");
        freeArray(performance, array);
        free(performance);
        exit(1);
    }else if (index == array -> nel){
        array -> nel += 1;
    }
    void *indexPointer = (array -> data);
    indexPointer = (char*)indexPointer + (index * (array -> width));
    memcpy(indexPointer, src, array -> width);
    performance -> writes += 1;
}

// Removes the final element in the array by changing the maxsize (NOTE: this does not destroy the data... just our access to it)
void contract(struct Performance *performance, struct Array *array){
    if (array -> nel == 0){
        fprintf(stderr, "contract: there is nothing held inside the array");
        exit(1);
    }
    array -> nel -= 1;
}

// Frees all the data inside of the struct Array and frees the struct itself
void freeArray(struct Performance *performance, struct Array *array){
    free(array -> data);
    free(array);
    performance -> frees += 1;
}

// Adds an item to the end of an array
void appendItem(struct Performance *performance, struct Array *array, void *src){
    writeItem(performance, array, array -> nel, src);
}

// Inserts an item into an array at the given index
void insertItem(struct Performance *performance, struct Array *array, unsigned int index, void *src){
    void *temp = malloc(array -> width);
    if(temp == NULL){
        fprintf(stderr, "insertItem: memory allocation error\n");
        freeArray(performance, array);
        free(performance);
        exit(1);
    }
    int signedIndex = (int)index;
    for(int i = ((array -> nel) - 1); i >= signedIndex; i--){
        readItem(performance, array, i, temp);
        writeItem(performance, array, i+1, temp);
    }
    writeItem(performance, array, signedIndex, src);
    free(temp);
}

// Adds an item to the begining of the array
void prependItem(struct Performance *performance, struct Array *array, void *src){
    insertItem(performance, array, 0, src); 
}

// Removes the data at a given index
void deleteItem(struct Performance *performance, struct Array *array, unsigned int index){
    void *temp = malloc(array -> width);
    if(temp == NULL){
        fprintf(stderr, "deleteItem: memory allocation error\n");
        freeArray(performance, array);
        free(performance);
        exit(1);
    }
    for(int i = index + 1; i < array -> nel; i++){
        readItem(performance, array, i, temp);
        writeItem(performance, array, i-1, temp);
    }
    contract(performance, array);
    free(temp);
}

// Performs a linear serach on the array
// Uses the campar function to compare the elements to the target
int findItem(struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target){
    void *item = malloc(array -> width);
    if(item == NULL){
        fprintf(stderr, "findItem: memory allocation error\n");
        freeArray(performance, array);
        free(performance);
        exit(1);
    }
    for(int i = 0; i < (array -> nel); i++){
        readItem(performance, array, i, item);
        if((*compar)(item, target) == 0){
            free(item);
            return i;
        }
    }
    free(item);
    return -1;
}

// Performs a binary search on the array
/// Uses the campar function to compare the elements to the target
int searchItem(struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target){
    int high = (array -> nel) - 1, low = 0;
    int i;
    void *item = malloc(array -> width);
    if(item == NULL){
        fprintf(stderr, "searchItem: memory allocation error\n");
        freeArray(performance, array);
        free(performance);
        exit(1);
    }
    while(high >= low){
        i = (high + low) / 2;
        readItem(performance, array, i, item);
        if((*compar)(item, target) == 0){
            free(item);
            return i;
        } else if ((*compar)(item, target) < 0){
            low = i + 1;
        }else{
            high = i - 1;
        }
    }

    free(item);
    return -1;
}