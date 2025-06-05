#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "quicksort.h"
#include "utils.h"

double * file2arr(char *s, int * line_count) {
    FILE *f = fopen(s, "r");
    char throwaway = 0;
    *line_count = 0;
    while(fread(&throwaway, 1, 1, f)) {
        if(throwaway == '\n')
            (*line_count)++;
    }
    rewind(f);
    char reader[32];
    double *arr = malloc(sizeof(double) * (*line_count));
    for(int i = 0; i < *line_count; i++)
    {
       fgets(reader, 32, f);
       arr[i] = atof(reader); 
    }
    fclose(f);
    return arr;
}

double **gen_matrix(double *data, int he, int width) {
    double **matrix = malloc(sizeof(double *) * he);
    for(int i = 0; i < he; i++) {
        matrix[i] = malloc(sizeof(double) * width);
    }
    for (int i = 0; i < he; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = data[i + j];
        }
    }
    return matrix;
}

double *def_y(double *data, int size, int w, int h) {
    double *y = malloc(sizeof(double) * (size - w - h + 1));
    for(int i = w - h + 1; i < size; i++) {
        y[i - w - h + 1] = data[i];
    }
    return y;
}

void genyfile(char *name, double *ydata, int size) {
    FILE *yfile = fopen(name, "w");
    for(int i = 0; i < size; i++) {
        fprintf(yfile, "%lf\n", ydata[i]);
    }
    fclose(yfile);
}

double dist(double **m1, double **m2, int width, int line1, int line2) {
    double distance = 0;
    for(int i = 0; i < width; i++) {
        distance += (m1[line1][i]-m2[line2][i]) * (m1[line1][i]-m2[line2][i]);
    }
    return sqrt(distance);
}

//dado um array de tamanho arr_size, escolhe os k menores valores para retornar
double *select_k(double *arr, int arr_size, int k) {
    double *narr = malloc(sizeof(double) * arr_size);
    for(int i = 0; i < arr_size; i++) {
        narr[i] = arr[i];
    }
    quicksort(narr, 0, arr_size - 1);
    double *returnarr = malloc(sizeof(double) * k);
    for(int i = 0; i < k; i++) {
        returnarr[i] = narr[i];
    }
    free(narr);
    return returnarr;
}

//dado um array arr1 de tamanho arr_size, acha os k números do array arr2 e retorna as posições deles no arr1
int *findk(double *arr1, int arr_size, double *arr2, int k) {
    int *arr_founds = malloc(sizeof(int) * k);
    int found = 0;
    for(int i = 0; i < arr_size && found < k; i++) {
        for(int j = 0; j < k; j++) {
            if(arr1[i] == arr2[j]) {
                arr_founds[found] = i;
                found++;
                break;
            }
        }
    }
    return arr_founds;
}

double media(double *arr, int *positions, int k) {
    double soma = 0;
    for(int i = 0; i < k; i++) {
        soma += arr[positions[i]];
    }
    return soma/k;
}