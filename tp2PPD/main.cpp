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

#define OUTPUT_DEBUG true

#include "banco_dados.h"
using namespace std;

int main(int argc, char** argv) {

    banco_dados bd = banco_dados::gerar_massa_testes();
    
    bd.obter_conjunto_a_priori(0.22);
    return 0;
}

