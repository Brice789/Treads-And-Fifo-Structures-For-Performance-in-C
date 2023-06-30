#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
pthread_mutex_t lock;

#define M 200
#define N 300
#define P 400
#define X 2 // Number of Threads
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"

int A[M][N], B[N][P], C[M][P], D[M][P];

int row = 0;

void *matrixMulti(void *arg)
{
    pthread_mutex_lock(&lock);
    int i = row++;

    for (int j = 0; j < P; j++)
    {
        C[i][j] = 0;
        for (int k = 0; k < N; k++)
        {
            C[i][j] += A[i][k] * B[k][j];
        }
    }

    
    pthread_exit(NULL);
    pthread_mutex_unlock(&lock);
}

void matrixMultiplicationWithoutThreading();
void matrixMultiplicationWithThreading();
void verifyIfBothMatrixAreSame();
int main()
{
    int m, n, p;
    // A: m*n Matrix, B: n*p Matrix
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = rand() % 10;
    // scanf("%d", &A[i][j]);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < P; j++)
            B[i][j] = rand() % 10;
    // scanf("%d", &B[i][j]);
    
    struct timeval start, end;
    gettimeofday(&start, NULL);
    matrixMultiplicationWithoutThreading();
    gettimeofday(&end, NULL);
    double time = (end.tv_sec - start.tv_sec) * 1e6;
    time = (time + end.tv_usec - start.tv_usec) * 1e-6;
    printf("The time taken by simple matrix calculation without threding is %0.6f\n", time);

    struct timeval start_th, end_th;
    gettimeofday(&start_th, NULL);
    matrixMultiplicationWithThreading();
    gettimeofday(&end_th, NULL);
    time = (end_th.tv_sec - start_th.tv_sec) * 1e6;
    time = (time + end_th.tv_usec - start_th.tv_usec) * 1e-6;
    printf("The time taken by using the Threading Method with %d threads is %0.6f\n", X, time);

    verifyIfBothMatrixAreSame();
}

void matrixMultiplicationWithThreading()
{
    pthread_t threads[X];
    for (int i = 0; i < X; i++)
    {
        threads[i] = (pthread_t)-1;
    }

    // Computation Started:
    for (int i = 0; i < M; i++)
    {

        // At any moment only X threads at max are working
        if (threads[i] == (pthread_t)-1)
            pthread_create(&threads[i % X], NULL, matrixMulti, NULL);
        else
        {
            pthread_join(threads[i % X], NULL);
            pthread_create(&threads[i % X], NULL, matrixMulti, NULL);
        }
    }
    for (int i = 0; i < X; i++)
        pthread_join(threads[i], NULL);
    // Computation Done:
}

void matrixMultiplicationWithoutThreading()
{
    // Computation Started:
    for (int i = 0; i < M; i++)
        for (int j = 0; j < P; j++)
        {
            D[i][j] = 0;
            for (int k = 0; k < N; k++)
                D[i][j] += A[i][k] * B[k][j];
        }
    // Computation Done:
}
void verifyIfBothMatrixAreSame()
{
    for (int i = 0; i < M; i++)
        for (int j = 0; j < P; j++)
        {
            if (C[i][j] != D[i][j])
            {
                printf(RED "\nMatrix's are not equal something wrong with the computation\n");
                return;
            }
        }
    printf(GREEN "\nBoth Matrixes are equal thus verifying the computation\n");
}