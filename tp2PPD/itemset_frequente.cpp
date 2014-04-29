/* 
 * File:   itemset_frequente.cpp
 * Author: Otmar
 * 
 * Created on 28 de Abril de 2014, 20:45
 */

#include "itemset_frequente.h"

itemset_frequente::itemset_frequente(int indice) {
    this->indice_k = indice;
    this->total_conjuntos = 0;
}

int itemset_frequente::k() {
    return this->indice_k;
}

void itemset_frequente::adicionar_conjunto(vector<item*> conjunto){
    this->total_conjuntos++;
    
    // this->itens_nao_ordenados.insert(); // TODO - Continue daqui!!!
}