#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

#define NUM_THREADS 8  

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

// pasar datos a los hilos
typedef struct {
    int *V;  // Vector de entrada
    int *VR; // Vector de resultados
    int start;
    int end;
} ThreadData;

// funcion que ejecuta los hilos
void *calculateFunc(void *threadarg) {
    ThreadData *my_data;
    my_data = (ThreadData *) threadarg;

    for (int i = my_data->start; i < my_data->end; i++) {
        my_data->VR[i] = func(3, my_data->V[i]);
    }
    pthread_exit(NULL);
}

int main() {
    struct timeval start, end;

    // tiempo real
    gettimeofday(&start, NULL);

    // vector a usar
    int V[] = {10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13};
    int lenV = sizeof(V) / sizeof(V[0]);  
    int VR[lenV];  

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int rc;
    long t;
    void *status;

    // distribuir hilos en el vector
    for(t = 0; t < NUM_THREADS; t++) {
        thread_data[t].V = V;
        thread_data[t].VR = VR;
        thread_data[t].start = t * lenV / NUM_THREADS;
        thread_data[t].end = (t + 1) * lenV / NUM_THREADS;

        rc = pthread_create(&threads[t], NULL, calculateFunc, (void *)&thread_data[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // esperar a que los hilos terminen
    for(t = 0; t < NUM_THREADS; t++) {
        rc = pthread_join(threads[t], &status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }

    // parar tiempo
    gettimeofday(&end, NULL);

    // calcular tiempo real
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    // agregar resultados a lista
    printf("VR = [");
    for (int i = 0; i < lenV; i++) {
        printf("%d", VR[i]);
        if (i < lenV - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Tiempo de ejecución con pthread-8: %f segundos\n", elapsed);

    return 0;
}
