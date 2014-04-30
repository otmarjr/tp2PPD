/* 
 * File:   transacao.h
 * Author: Otmar
 *
 * Created on 28 de Abril de 2014, 21:07
 */

#include "item.h"
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
    void adicionar_item_comprado(item* it);
    vector<vector<item*> > recuperar_subconjuntos_candidatos(vector<item*> Ck);
private:
    int id_transacao;
    vector<item*> itens_comprados;
};

#endif	/* TRANSACAO_H */

