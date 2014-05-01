/* 
 * File:   itemset_frequente.cpp
 * Author: Otmar
 * 
 * Created on 28 de Abril de 2014, 20:45
 */

#include "itemset_frequente.h"
#include <algorithm>
using namespace std;
itemset_frequente::itemset_frequente(int indice) {
    this->indice_k = indice;
}

int itemset_frequente::k() {
    return this->indice_k;
}

bool comparar_itens(item* i1, item* i2){
    return i1->identificador() < i2->identificador();
}

void itemset_frequente::adicionar_conjunto(vector<item*> conjunto){
    vector<item*> v_aux (conjunto);
    
    std::sort(v_aux.begin(), v_aux.end(), comparar_itens);
    
    this->subconjuntos_ordenados.push_back(v_aux);
    
}

bool itemset_frequente::esta_vazio(){
    return this->subconjuntos_ordenados.size() == 0;
}
int itemset_frequente::tamanho()
{
    return this->subconjuntos_ordenados.size();
}

vector<item*> itemset_frequente::operator[](int indice) const
{
    return this->subconjuntos_ordenados[indice];
}

bool itemset_frequente::subconjunto_esta_contido(vector<item*> subconjunto){
    std::sort(subconjunto.begin(), subconjunto.end());
    
    for (int i=0;i<this->subconjuntos_ordenados.size();i++){
        
        if (std::includes(this->subconjuntos_ordenados[i].begin(),this->subconjuntos_ordenados[i].end(), subconjunto.begin(), subconjunto.end())){
            return true;
        }
    }
    
    return false;
}