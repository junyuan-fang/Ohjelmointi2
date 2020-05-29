#include <iostream>
#include "swap.hh"


void swap ( int& luku1, int& luku2){
    int varasto_luku;
    varasto_luku =luku1;
    luku1=luku2;
    luku2=varasto_luku;
}


