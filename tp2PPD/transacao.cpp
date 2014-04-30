/* 
 * File:   transacao.cpp
 * Author: Otmar
 * 
 * Created on 28 de Abril de 2014, 21:07
 */

#include "transacao.h"
#include <algorithm>

transacao::transacao(int id) {
    this->id_transacao = id;
}

bool transacao::possui_item(item* it) const{
    return std::binary_search(this->itens_comprados.begin(), this->itens_comprados.end(), it);
}

int transacao::id(){
    return this->id_transacao;
}

void transacao::adicionar_item_comprado(item* it){
    int p=0;
    for (int i=0;i<this->itens_comprados.size();i++){
        if (it < this->itens_comprados[i]){
            break;
        }
        else{
            p++;
        }
    }
    
    this->itens_comprados.insert(this->itens_comprados.begin() + p, it);
}

vector<vector<item*> > obter_subconjuntos(int posicao_inicial, int tamanho_subconjunto,vector<item*> conjunto){
    vector<vector<item*> > v;
    
    if (tamanho_subconjunto == 1){
        for (int i=posicao_inicial;i<conjunto.size();i++){
            vector<item*> v2;
            v2.push_back(conjunto[i]);
            v.push_back(v2);
        }
    }
    else {
        for (int i=posicao_inicial;i<posicao_inicial+tamanho_subconjunto;i++){
            vector<vector<item*> > subs_a_frente = obter_subconjuntos(posicao_inicial+1,tamanho_subconjunto-1,conjunto);
            for (int j=0;j<subs_a_frente.size();j++){
                vector<item*> v2 = subs_a_frente[i];
                v2.insert(v2.begin(), conjunto[i]);
                v.push_back(v2);
            }
        }
    }
    
    return v;
}

vector<vector<item*> > transacao::recuperar_subconjuntos_candidatos(vector<item*> Ck)
{
    int K = Ck.size();
    int T = this->itens_comprados.size();
    
    if (K<=T){
        return obter_subconjuntos(0,K, this->itens_comprados);
    }
    else{
        vector<vector<item*> > vazio;
        return vazio;
    }
}