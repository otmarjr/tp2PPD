/* 
 * File:   transacao.cpp
 * Author: Otmar
 * 
 * Created on 28 de Abril de 2014, 21:07
 */

#include "transacao.h"

transacao::transacao(int id) {
    this->id_transacao = id;
}

bool transacao::possui_item(item* it) const{
    return this->itens_comprados.find(it) != this->itens_comprados.end();
}

int transacao::id(){
    return this->id_transacao;
}

void transacao::adicionar_item_comprado(item* it){
    this->itens_comprados.insert(it);
}
