/*
 * File:   main.cpp
 * Author: otmarpereira
 *
 * Created on 28 de Abril de 2014, 14:06
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <vector>
#include <mpi.h>
#include <stdlib.h>
#include "banco_dados.h"
using namespace std;

int main(int argc, char** argv) {

    int rank, size;
    
     

    MPI_Init(&argc, &argv); /* starts MPI */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* get current process id */
    MPI_Comm_size(MPI_COMM_WORLD, &size); /* get number of processes */
    
    banco_dados bd = banco_dados::gerar_massa_testes_issues();
    double suporte = 0.1;

    clock_t t1, t2;

    t1 = clock();

    bd.obter_conjunto_a_priori(suporte);

    t2 = clock();

    double diff = ((double) t1 - (double) t2);
    double secs = diff / CLOCKS_PER_SEC;
    cout << "\n Tempo gasto: "<< secs<<" segundos.";

    MPI_Finalize();
    return 0;
}

