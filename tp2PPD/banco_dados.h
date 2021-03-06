/* 
 * File:   banco_dados.h
 * Author: Otmar
 *
 * Created on 28 de Abril de 2014, 21:06
 */

#ifndef BANCO_DADOS_H
#define	BANCO_DADOS_H

#include <vector>
#include "item.h"
#include "transacao.h"
#include "itemset_frequente.h"

using namespace std;

#define ID_PROCESSO_MESTRE 0
class banco_dados {
public:
    banco_dados(vector<item*> itens_a_venda, vector<transacao*> vendas);
    static banco_dados gerar_massa_testes();
    static banco_dados gerar_massa_testes_issues();
    vector<itemset_frequente> obter_conjunto_a_priori(double suporte_minimo);
    int obter_id_processo_atual();
    int obter_quantidade_processos();
    bool e_processo_mestre();
private:
    vector<item*> itens_a_venda;
    vector<transacao*> transacoes;
    itemset_frequente f1_itemset(double suporte_minimo);
    itemset_frequente apriori_gen(itemset_frequente Lkmenos1);
    bool tem_sub_conjunto_infrequente(vector<item*> c, itemset_frequente Lkmenos1);
    vector<vector<item*> > subconjunto_tamanho_k_menos_um(vector<item*> c);
};

#endif	/* BANCO_DADOS_H */

