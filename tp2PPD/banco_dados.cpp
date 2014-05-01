#include "banco_dados.h"
#include "transacao.h"

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<item*> massa_testes_itens() {
    vector<item*> v;

    for (int i = 1; i <= 5; i++) {
        v.push_back(new item(i));
    }

    return v;
}

vector<transacao*> massa_testes_vendas(vector<item*> itens) {
    vector<transacao*> t;

    transacao* t100 = new transacao(100);
    t100->adicionar_item_comprado(itens[0]);
    t100->adicionar_item_comprado(itens[1]);
    t100->adicionar_item_comprado(itens[4]);

    transacao* t200 = new transacao(200);
    t200->adicionar_item_comprado(itens[1]);
    t200->adicionar_item_comprado(itens[3]);

    transacao* t300 = new transacao(300);
    t300->adicionar_item_comprado(itens[1]);
    t300->adicionar_item_comprado(itens[2]);

    transacao* t400 = new transacao(400);
    t400->adicionar_item_comprado(itens[0]);
    t400->adicionar_item_comprado(itens[1]);
    t400->adicionar_item_comprado(itens[3]);

    transacao* t500 = new transacao(500);
    t500->adicionar_item_comprado(itens[0]);
    t500->adicionar_item_comprado(itens[2]);

    transacao* t600 = new transacao(600);
    t600->adicionar_item_comprado(itens[1]);
    t600->adicionar_item_comprado(itens[2]);

    transacao* t700 = new transacao(700);
    t700->adicionar_item_comprado(itens[0]);
    t700->adicionar_item_comprado(itens[2]);

    transacao* t800 = new transacao(800);
    t800->adicionar_item_comprado(itens[0]);
    t800->adicionar_item_comprado(itens[1]);
    t800->adicionar_item_comprado(itens[2]);
    t800->adicionar_item_comprado(itens[4]);

    transacao* t900 = new transacao(900);
    t900->adicionar_item_comprado(itens[0]);
    t900->adicionar_item_comprado(itens[1]);
    t900->adicionar_item_comprado(itens[2]);

    t.push_back(t100);
    t.push_back(t200);
    t.push_back(t300);
    t.push_back(t400);
    t.push_back(t500);
    t.push_back(t600);
    t.push_back(t700);
    t.push_back(t800);
    t.push_back(t900);

    return t;
}

banco_dados::banco_dados(vector<item*> itens_a_venda, vector<transacao*> vendas) {
    this->itens_a_venda = itens_a_venda;
    this->transacoes = vendas;
}

banco_dados banco_dados::gerar_massa_testes() {
    vector<item*> its = massa_testes_itens();
    vector<transacao*> v = massa_testes_vendas(its);
    return banco_dados(its, v);
}

itemset_frequente banco_dados::f1_itemset(float suporte_minimo) {
    int k = 1;
    itemset_frequente f1(k);
    for (int i = 0; i<this->itens_a_venda.size(); i++) {
        item* it = this->itens_a_venda[i];

        int count_i = 0;
        int T = this->transacoes.size();
        for (int j = 0; j < T; j++) {
            transacao* t = this->transacoes[j];

            if (t->possui_item(it)) {
                count_i++;
            }
        }

        if (count_i / (1.0f * T) >= suporte_minimo) {
            vector<item*> is1;
            is1.push_back(it);
            f1.adicionar_conjunto(is1);
        }
    }

    return f1;
}

vector<itemset_frequente> banco_dados::obter_conjunto_a_priori(float suporte_minimo) {
    vector<itemset_frequente> L;
    
    
    itemset_frequente L1 = f1_itemset(suporte_minimo);
    itemset_frequente LkmenosUm = L1;

    L.push_back(L1);
    
    for (int k = 2; !LkmenosUm.esta_vazio(); k++) {
        itemset_frequente Ck = apriori_gen(LkmenosUm);
        vector<int> count_c(Ck.tamanho(),0);
       
        for (int i = 0; i<this->transacoes.size(); i++) {
            vector<vector<item*> > Ct = this->transacoes[i]->recuperar_subconjuntos_candidatos(Ck.k());

            for (int x = 0; x < Ck.tamanho(); x++) {
                vector<item*> c = Ck[x];

                for (int j = 0; j < Ct.size(); j++) {
                    if (std::includes(Ct[j].begin(), Ct[j].end(), c.begin(), c.end())) {
                        count_c[x] = count_c[x] + 1;
                    }
                    
                }
            }
        }

        for (int y=0;y<Ck.tamanho();y++){
            cout<<"\n Ck[: "<<y<<"] = ";
            for (int y2=0;y2<Ck[y].size();y2++){
                cout<<" "<<Ck[y][y2]->identificador();
            }
            
            cout<<" count = "<<count_c[y];
        }
        
        int T = this->transacoes.size();
        itemset_frequente Lk(k);
        L.push_back(Lk);
        
        for (int i=0;i<count_c.size();i++){
            if (count_c[i]/(1.0f*T) >= suporte_minimo){
                Lk.adicionar_conjunto(Ck[i]);
            }
        }
        
        LkmenosUm = Lk; // Prepara para próxima iteração.
    }

    return L;
}

itemset_frequente banco_dados::apriori_gen(itemset_frequente Lkmenos1) {
    int k = Lkmenos1.k();
    int kMenosUm = k-1; // Offset por conta do índice 0
    int KMenosDois = k-2; // Offset por conta do índice 0
    
    if (KMenosDois < 0){
        KMenosDois = 0;
    }
    
    if (kMenosUm < 0){
        kMenosUm = 0;
    }
    
    itemset_frequente Ck(k+1);

    for (int i = 0; i < Lkmenos1.tamanho(); i++) {
        vector<item*> l1 = Lkmenos1[i];

        for (int j = 0; j < Lkmenos1.tamanho(); j++) {

            bool igualAteKMenosDois = true;
            vector<item*> l2 = Lkmenos1[j];

            for (int x = 0; x < KMenosDois; x++) {
                if (l1[x] != l2[x]) {
                    igualAteKMenosDois = false;
                    break;
                }
            }

            int l1KMenosUm =l1[kMenosUm]->identificador();
            int l2LKmenosUm = l2[kMenosUm]->identificador();
            if (igualAteKMenosDois && l1KMenosUm < l2LKmenosUm) {
                vector<item*> c12(l1);
                c12.push_back(l2[kMenosUm]);

                if (!tem_sub_conjunto_infrequente(c12, Lkmenos1)) {
                    Ck.adicionar_conjunto(c12);
                }
            }
        }
    }

    int Ck40 = Ck[4][0]->identificador();
    int Ck41 = Ck[4][1]->identificador();
    return Ck;
}

vector<vector<item*> > banco_dados::subconjunto_tamanho_k_menos_um(vector<item*> c) {
    vector<vector<item*> > p;

    for (int i = 0; i < c.size(); i++) { // Para um conjunto de tamanho k, faz os subconjuntoss k-1 excluindo cada i-ésimo elemento uma vez
        vector<item*> s(c);
        s.erase(std::remove(s.begin(), s.end(), c[i]));
        p.push_back(s);
    }

    return p;
}

bool banco_dados::tem_sub_conjunto_infrequente(vector<item*> c, itemset_frequente Lkmenos1) {
    vector<vector<item*> > subconjuntos_k_menos_um = this->subconjunto_tamanho_k_menos_um(c);

    for (int i = 0; i < subconjuntos_k_menos_um.size(); i++) {
        vector<item*> s = subconjuntos_k_menos_um[i];

        if (!Lkmenos1.subconjunto_esta_contido(s)) {
            return true;
        }
    }

    return false;
}