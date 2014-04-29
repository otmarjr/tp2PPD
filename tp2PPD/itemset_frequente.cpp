/* 
 * File:   itemset_frequente.cpp
 * Author: Otmar
 * 
 * Created on 28 de Abril de 2014, 20:45
 */

#include "itemset_frequente.h"

itemset_frequente::itemset_frequente(int indice) {
    this->indice_k = indice;
}

int itemset_frequente::k() {
    return this->indice_k;
}

void itemset_frequente::adicionar_conjunto(vector<item*> conjunto){
    set<item*> s(conjunto.begin(), conjunto.end());
    
    this->subconjuntos_ordenados.push_back(s);
    this->subcojuntos_nao_ordenados.insert(s);
}

bool itemset_frequente::esta_vazio(){
    return this->subcojuntos_nao_ordenados.size() == 0;
}
int itemset_frequente::tamanho()
{
    return this->subconjuntos_ordenados.size();
}

set<item*> itemset_frequente::operator[](int indice) const
{
    return this->subconjuntos_ordenados[indice];
}