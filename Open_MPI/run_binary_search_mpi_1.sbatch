#!/bin/bash
#SBATCH --job-name=binary_search_mpi_1
#SBATCH --output=binary_search_mpi_1_%j.out
#SBATCH --error=binary_search_mpi_1_%j.err
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:10:00
#SBATCH --partition=normal

mpirun -np 2 ./binary_search_mpi_1

