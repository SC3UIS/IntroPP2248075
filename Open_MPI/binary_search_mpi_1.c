#include <stdio.h>
#include <mpi.h>

void binary_search(int [], int, int, int);
void bubble_sort(int [], int);

int main()
{
    int key, size, i;
        int list[] = {2, 4, 7, 10, 11, 45, 50, 59, 60, 66, 69, 70, 79};
            size = sizeof(list) / sizeof(list[0]);
            
                bubble_sort(list, size);
                
                    key = 66; // Definimos la clave directamente aquí
                    
                        MPI_Init(NULL, NULL);
                            binary_search(list, 0, size, key);
                                MPI_Finalize();
                                
                                    return 0;
                                    }
                                    
                                    void bubble_sort(int list[], int size)
                                    {
                                        int temp, i, j;
                                            for (i = 0; i < size; i++)
                                                {
                                                        for (j = i; j < size; j++)
                                                                {
                                                                            if (list[i] > list[j])
                                                                                        {
                                                                                                        temp = list[i];
                                                                                                                        list[i] = list[j];
                                                                                                                                        list[j] = temp;
                                                                                                                                                    }
                                                                                                                                                            }
                                                                                                                                                                }
                                                                                                                                                                }
                                                                                                                                                                
                                                                                                                                                                void binary_search(int list[], int lo, int hi, int key)
                                                                                                                                                                {
                                                                                                                                                                    int mid;
                                                                                                                                                                        int rank;
                                                                                                                                                                            MPI_Comm_rank(MPI_COMM_WORLD, &rank);
                                                                                                                                                                            
                                                                                                                                                                                if (lo > hi)
                                                                                                                                                                                    {
                                                                                                                                                                                            if (rank == 0) {
                                                                                                                                                                                                        printf("Key not found\n");
                                                                                                                                                                                                                }
                                                                                                                                                                                                                        return;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                mid = (lo + hi) / 2;
                                                                                                                                                                                                                                    if (list[mid] == key)
                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                if (rank == 0) {
                                                                                                                                                                                                                                                            printf("Key found at index %d\n", mid);
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                            else if (list[mid] > key)
                                                                                                                                                                                                                                                                                {
                                                                                                                                                                                                                                                                                        binary_search(list, lo, mid - 1, key);
                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                else if (list[mid] < key)
                                                                                                                                                                                                                                                                                                    {
                                                                                                                                                                                                                                                                                                            binary_search(list, mid + 1, hi, key);
                                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                                }
