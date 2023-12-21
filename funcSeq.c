#include <stdio.h>
#include <time.h>

// Declaración de la función
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
    // Iniciar el temporizador
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    // Vector de entrada completo
    int V[] = { 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13};
    int lenV = sizeof(V) / sizeof(V[0]);  // Longitud del vector V
    int VR[lenV];  // Vector para almacenar los resultados

    // Aplicar la función a cada elemento de V y almacenar en VR
    for (int i = 0; i < lenV; ++i) {
        VR[i] = func(3, V[i]);
    }

    // Detener el temporizador y calcular el tiempo utilizado
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Imprimir los resultados del vector VR
    printf("VR = [");
    for (int i = 0; i < lenV; ++i) {
        printf("%d", VR[i]);
        if (i < lenV - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    printf("Tiempo de ejecución: %f segundos\n", cpu_time_used);

    return 0;
}
