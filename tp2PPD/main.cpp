/*
 * File:   main.cpp
 * Author: otmarpereira
 *
 * Created on 28 de Abril de 2014, 14:06
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct item {
    int id;


    bool operator < (const item &other) const
    {
        return id < other.id;
    }
};

struct transacao {
    int id_transacao;
    map<int, item> itens;
};

struct banco_dados {
    vector<transacao> transacoes;
    vector<item> itens_a_venda;
};

struct saida_apriori {
    int k;
    vector<vector<item> > L;
};

vector<vector<item> > encontrar_itemset_frequente1(banco_dados bd, float suporte_min)
{
    vector<vector<item> > L1;
    
    int n = bd.itens_a_venda.size();
    int T = bd.transacoes.size();

    for (int i=0;i<n;i++){
        int cont_i = 0;
        item item_i = bd.itens_a_venda[i];

        for (int j=0;j<T;j++){
            if (bd.transacoes[j].itens.find(item_i.id) != bd.transacoes[j].itens.end())
                cont_i++;
            }

        float suporte_i = cont_i/(1.0f*T);

        if (suporte_i > suporte_min){
            vector<item> l;
            //l.push_back(item);
            L1.push_back(l);
        }
    }

    return L1;
}

bool tem_subconjunto_infrequente(vector<vector<item> > c, vector<vector<item> > LKMenosUmFrequentItemSets){
    vector<vector<item> >::iterator it;
    
    for (it = c.begin(); it != c.end(); ++it){
        vector<item> s = *it;
        
        /*
        if (s != LKMenosUmFrequentItemSets){
            return true;
        }
         * */
    }
    
    return false;
}

vector<vector<item> > apriori_gen(vector<vector<item> > LKMenosUmFrequentItemSets){
    vector<vector<item> > Ck;
    
    vector<vector<item> >::iterator it_l1, it_l2;
    
    
    
    return Ck;
}

saida_apriori apriori(banco_dados bd, float min_sup){
    saida_apriori s;

    vector<vector<item> > L1 = encontrar_itemset_frequente1(bd, 0.7f);
    vector<vector<item> > LKmenosUm = L1;

    for (int k=2;LKmenosUm.size() > 0;k++) {

    }
    return s;
}

int main(int argc, char** argv) {

    return 0;
}

