#ifndef _UTILS_H_
#define _UTILS_H_
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double * file2arr(char *s, int * line_count);
double **gen_matrix(double *data, int he, int width);
double *def_y(double *data, int size, int w, int h);
void genyfile(char *name, double *ydata, int size);
double dist(double **m1, double **m2, int width, int line1, int line2);
double *select_k(double *arr, int arr_size, int k);
int *findk(double *arr1, int arr_size, double *arr2, int k);
double media(double *arr, int *positions, int k);
#endif