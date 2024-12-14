#include <stdio.h>
#include <stdlib.h>

int partition(double * A, int lo, int hi){
    double pivot = A[hi];
    int i = lo - 1;

    for(int j = lo; j < hi; j++){
        if (A[j] <= pivot){
            i = i + 1;
            double helper = A[i];
            A[i] = A[j];
            A[j] = helper;
        }
    }
    i = i + 1;
    double helper = A[i];
    A[i] = A[hi];
    A[hi] = helper;
    return i;
}

void quicksort(double * A, int lo, int hi){
    if(lo>=hi || lo < 0) return ;
    int p = partition(A, lo, hi);

    quicksort(A, lo, p - 1);
    quicksort(A, p + 1, hi);
}