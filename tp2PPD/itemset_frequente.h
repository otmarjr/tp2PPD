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
    bool esta_vazio();
    set<item*> operator[](int index) const;
    int tamanho();
private:
    int indice_k;
    vector<set<item*> > subconjuntos_ordenados;
    set<set<item*> > subcojuntos_nao_ordenados;
};

#endif	/* ITEMSET_FREQUENTE_H */

