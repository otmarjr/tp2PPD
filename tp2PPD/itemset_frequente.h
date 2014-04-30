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
#include <algorithm>
using namespace std;
class itemset_frequente {
public:
    itemset_frequente(int indice);
    int k();
    void adicionar_conjunto(vector<item*> conjunto);
    bool esta_vazio();
    vector<item*> operator[](int index) const;
    int tamanho();
    bool subconjunto_esta_contido(vector<item*> subconjunto);
private:
    int indice_k;
    vector<vector<item*> > subconjuntos_ordenados;
};

#endif	/* ITEMSET_FREQUENTE_H */

