/* 
 * File:   main.cpp
 * Author: otmarpereira
 *
 * Created on 28 de Abril de 2014, 14:06
 */

#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct item {
    int id;
};

struct transacao {
    int id_transacao;
    set<item> itens;
};

struct banco_dados {
    vector<transacao> transacoes;
    vector<item> itens_a_venda;
};

struct saida_apriori {
    int k;
    set<set<item> > L;
};

set<set<item> > encontrar_itemset_frequente1(banco_dados bd, float suporte_min)
{
    set<set<item > > L1;
    int n = bd.itens_a_venda.size();
    int T = bd.transacoes.size();
    
    for (int i=0;i<n;i++){
        int cont_i = 0;
        item item_i = bd.itens_a_venda[i];
        
        for (int j=0;j<T;j++){
            if (bd.transacoes[j].itens.find(item_i)) {
                cont_i++;
            }
        }
        
        float suporte_i = cont_i/(1.0f*T);
        
        if (suporte_i > suporte_min){
            set<item> s(item);
            L1.insert(s);
        }
    }
    
    return L1;
}

saida_apriori apriori(banco_dados bd, float min_sup){
    saida_apriori s;
    
    set<set<item> > L1 = encontrar_itemset_frequente1(bd);
    
    return s;
}

int main(int argc, char** argv) {
    
    return 0;
}

