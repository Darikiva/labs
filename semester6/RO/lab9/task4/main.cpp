#include <iostream>
#include <omp.h>
#include <iomanip>
#include <chrono>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <chrono>

using namespace std;
const int N = 2000;

void init(int *A)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i * N + j] = rand() % 5;
}

int main()
{
    srand(time(NULL));
    int i, j, k;

    int *A = new int[N * N];
    int *B = new int[N * N];
    int *C = new int[N * N];
    init(A);
    init(B);
    auto begin_time = std::chrono::steady_clock::now();

#pragma omp parallel for private(j, k) num_threads(4)
    for (i = 0; i < N; i++)
        for (k = 0; k < N; k++)
        {
            int sum = 0;
            for (j = 0; j < N; j++)
                sum += A[i * N + j] * B[j * N + k];
            C[i * N + k] = sum;
        }
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();
    std::cout << "N = " << N << "; time = " << duration << "ms\n";

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}