#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_SIZE 100

void arrange(int, int);
int array[MAX_SIZE], array1[MAX_SIZE];
int i, j, temp, max, count, maxdigits = 0, c = 0;

int main() {
    int rank, size, t1, t2, k, t, n = 1;
    double start_time, end_time; // Variables para almacenar los tiempos de inicio y fin

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Medir el tiempo de inicio
    start_time = MPI_Wtime();

    if (rank == 0) {
        int list[] = {2, 4, 7, 10, 11, 45, 50, 59, 60, 66, 69, 70, 79};
        count = sizeof(list) / sizeof(list[0]);
        for (i = 0; i < count; i++) {
            array[i] = list[i];
            array1[i] = array[i];
        }
        for (i = 0; i < count; i++) {
            t = array[i];
            while (t > 0) {
                c++;
                t = t / 10;
            }
            if (maxdigits < c)
                maxdigits = c;
            c = 0;
        }
        while (--maxdigits)
            n = n * 10;
    }

    MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_n = count / size;
    int *local_array = malloc(local_n * sizeof(int));
    int *local_array1 = malloc(local_n * sizeof(int));

    MPI_Scatter(array, local_n, MPI_INT, local_array, local_n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(array1, local_n, MPI_INT, local_array1, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_n; i++) {
        for (int j = i + 1; j < local_n; j++) {
            if (local_array1[i] > local_array1[j]) {
                temp = local_array1[i];
                local_array1[i] = local_array1[j];
                local_array1[j] = temp;
                temp = local_array[i];
                local_array[i] = local_array[j];
                local_array[j] = temp;
            }
        }
    }

    MPI_Gather(local_array, local_n, MPI_INT, array, local_n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gather(local_array1, local_n, MPI_INT, array1, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < count;) {
            t1 = array[i] / n;
            for (j = i + 1; j < count && (array[j] / n) == t1; j++);
            arrange(i, j);
            i = j;
        }
        printf("\nSorted Array (Postman sort) :");
        for (i = 0; i < count; i++)
            printf("%d ", array1[i]);
        printf("\n");
    }

    free(local_array);
    free(local_array1);

    // Medir el tiempo de fin
    end_time = MPI_Wtime();

    // Calcular el tiempo de ejecución
    double execution_time = end_time - start_time;

    // Imprimir el tiempo de ejecución
    printf("Tiempo de ejecución: %.6f segundos\n", execution_time);

    MPI_Finalize();
    return 0;
}

void arrange(int k, int n) {
    for (i = k; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (array1[i] > array1[j]) {
                temp = array1[i];
                array1[i] = array1[j];
                array1[j] = temp;
                temp = array[i] % 10;
                array[i] = array[j] % 10;
                array[j] = temp;
            }
        }
    }
}

