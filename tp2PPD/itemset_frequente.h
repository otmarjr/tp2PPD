/* 
 * File:   itemset_frequente.h
 * Author: Otmar
 *
 * Created on 28 de Abril de 2014, 20:45
 */

#ifndef ITEMSET_FREQUENTE_H
#define	ITEMSET_FREQUENTE_H

#include <vector>
#include <set>
#include "item.h"

using namespace std;
class itemset_frequente {
public:
    itemset_frequente(int indice);
    int k();
    void adicionar_conjunto(vector<item*> conjunto);
private:
    int indice_k;
    int total_conjuntos;
    vector<vector<item*> > itens_posicional;
    set<set<item*> > itens_nao_ordenados;
    set<item*> todos_itens;
};

#endif	/* ITEMSET_FREQUENTE_H */

