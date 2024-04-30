#!/bin/bash
#SBATCH --job-name=postman_sort_mpi_1
#SBATCH --output=postman_sort_mpi_1_%j.out
#SBATCH --error=postman_sort_mpi_1_%j.err
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:10:00
#SBATCH --partition=normal

mpirun -np 2 ./postman_sort_mpi_1

