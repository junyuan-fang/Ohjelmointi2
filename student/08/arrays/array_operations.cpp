#include "array_operations.hh"
#include<iostream>
using namespace std;
/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int size: number of elements to be examined
 * return value: the greatest element of the array
 */
int greatest_v1(int* itemptr, int size){
    int greatest_num=*itemptr;
    int* flag= itemptr;
    while(itemptr<flag+size){
        if(*itemptr>=greatest_num){
            greatest_num=*itemptr;
        }
        ++itemptr;
    }
    return greatest_num;

}

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int* endptr: pointer to the memory address after the last element of the array
 * return value: the greatest element of the array
 */
int greatest_v2(int* itemptr, int* endptr){
    int greatest_num=*itemptr;
    while (itemptr<endptr){
        if(*itemptr>=greatest_num){
            greatest_num=*itemptr;
        }
        ++itemptr;
    }

    return greatest_num;
}

/* Copies the content of the array to another array
 * int* itemptr: pointer to the first array element to be copied
 * int* endptr: pointer to the memory address after the last element of the array to be copied
 * int* targetptr: pointer to the head of the array, to which to copy
 */
void copy(int* itemptr, int* endptr, int* targetptr){
    while (itemptr<endptr){
        *targetptr=*itemptr;
        ++itemptr;
        ++targetptr;
    }
}

/* Reverses the elements of the array
 * int* leftptr: pointer to the first element of the reversable part
 * int* rightptr: pointer to the next memory address after the reversable part
 */
void reverse(int* leftptr, int* rightptr){
    int tallennus;
    int size=rightptr-leftptr;int keski=size/2;
    --rightptr;
    int *flag=leftptr;
    while(leftptr<flag+keski){
        tallennus=*leftptr;
        *leftptr=*rightptr;
        *rightptr=tallennus;
        ++leftptr;
        --rightptr;
    }
}


