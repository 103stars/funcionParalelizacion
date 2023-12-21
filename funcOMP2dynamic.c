#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

// funcion a aplicar
int func(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return func(m - 1, 1);
    } else {
        return func(m - 1, func(m, n - 1));
    }
}

int main() {
    struct timeval start, end;

    // obtener tiempo real
    gettimeofday(&start, NULL);

    // vector a usar
    int V[] = {10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13};
    int lenV = sizeof(V) / sizeof(V[0]);  
    int VR[lenV];  


    // paralelizar for con omp
    #pragma omp parallel for num_threads(2) schedule(dynamic)
    for (int i = 0; i < lenV; ++i) {
        VR[i] = func(3, V[i]);
    }
    gettimeofday(&end, NULL);
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    // Agregar resultados a lista
    printf("VR = [");
    for (int i = 0; i < lenV; ++i) {
        printf("%d", VR[i]);
        if (i < lenV - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Tiempo de ejecución con omp 2 dynamic: %f segundos\n", elapsed);
   

    return 0;
}
