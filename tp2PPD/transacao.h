/* 
 * File:   transacao.h
 * Author: Otmar
 *
 * Created on 28 de Abril de 2014, 21:07
 */

#include "item.h"
#include "itemset_frequente.h"

#include <set>
#include <vector>
using namespace std;

#ifndef TRANSACAO_H
#define	TRANSACAO_H

class transacao {
public:
    transacao(int id);
    bool possui_item(item* it) const;
    int id();
    void adicionar_item_a_transacao(item* it);
    vector<vector<item*> > recuperar_subconjuntos_candidatos(int K);
private:
    int id_transacao;
    vector<item*> itens_comprados;
};

#endif	/* TRANSACAO_H */

