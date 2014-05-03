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

#include "banco_dados.h"
using namespace std;

int main(int argc, char** argv) {

    vector<float> tempos;
    
    for (int i=0;i<5;i++)
    {
        clock_t t1, t2;
        t1 = clock();
        banco_dados bd = banco_dados::gerar_massa_testes_issues();
    
        bd.obter_conjunto_a_priori(0.0025);
        t2 = clock();
        
        float diff = ((float)t1-(float)t2);
        float secs = diff/ CLOCKS_PER_SEC;
        tempos.push_back(secs);
    }
    
    for (int i=0;i<5;i++)
    {
        cout<<"\n Execução "<<i<<" levou "<<tempos[i]<<" segundos";
    }
    
    return 0;
}

