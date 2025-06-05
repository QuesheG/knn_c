#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include "utils.h"

#define NUM_THREADS 6

double * knn(double **train_matrix, double *ytrain, double **test_matrix, double *ytest, int size_train, int size_test, int k, int w) {
    double *expected = malloc(sizeof(double) * size_test);
    #pragma omp parallel num_threads(NUM_THREADS)
    {    
        for(int i = omp_get_thread_num(); i < size_test; i += NUM_THREADS){
            double *dist_arr = malloc(sizeof(double) * size_train);
            for(int j = 0; j < size_train; j++) {
                dist_arr[j] = dist(train_matrix, test_matrix, w, j, i);
            }
            double *selected = select_k(dist_arr, size_train, k);
            int *positions = findk(dist_arr, size_train, selected, k);
            free(dist_arr);
            free(selected);
            expected[i] = media(ytrain, positions, k);
            free(positions);
        }
    }
}

int main(int argc, char *argv[])
{
    int k = 2; // n# vizinhos
    int w = 3; // janela de amostragem
    int h = 1; // valor futuro a prever

    if (argc == 2)
    {
        k = atoi(argv[1]);
    }
    else if (argc == 3)
    {
        k = atoi(argv[1]);
        w = atoi(argv[2]);
    }
    else if (argc == 4)
    {
        k = atoi(argv[1]);
        w = atoi(argv[2]);
        h = atoi(argv[3]);
    }
    else if (argc > 4)
    {
        printf("Wrong usage!\n\
                Expected less than 4 arguments.\n\
                %s %s %s %s\n\
                File input expected in execution\n",
                argv[0], argv[1], argv[2], argv[3]);
        return 1;
    }
    
    //leitura xtrain
    int line_count_train = 0;//número de linhas em x_train
    double *xtrain_data = file2arr("input/dados_xtrain.txt", &line_count_train);
    
    int strain = line_count_train - w - h + 1;//altura da matriz a ser gerada
    double *ytrain = def_y(xtrain_data, line_count_train, w, h);
    double **xtrain_matrix = gen_matrix(xtrain_data, strain, w);

    genyfile("output/ytrain_data.txt", ytrain, strain);

    printf("Input filename to be predicted: (name only)\n");
    char arquivo[32];
    scanf("%s", arquivo);
    printf("\n");

    //leitura de xtest
    int line_count_test = 0;//número de linhas em xtest_num
    char nomearquivo[42];
    sprintf(nomearquivo, "input/%s.txt", arquivo);
    double *xtest_data = file2arr(nomearquivo, &line_count_test);
    int stest = line_count_test - w - h + 1;//altura da matriz a ser gerada
    
    double *ytest, **xtest_matrix;

    ytest = def_y(xtest_data, line_count_test, w, h);
    xtest_matrix = gen_matrix(xtest_data, stest, w);

    genyfile("output/ytest_data.txt", ytest, stest);

    double start = omp_get_wtime();
    double *result = knn(xtrain_matrix, ytrain, xtest_matrix, ytest, strain, stest, k, w);
    printf("Parallelized time: %lf\n", omp_get_wtime() - start);
    
    FILE *expecfile = fopen("output/predicted_data.txt", "w");
    for(int i = 0; i < stest; i++) {
        fprintf(expecfile, "%lf\n", result[i]);
    }

    return 0;
}