#include "banco_dados.h"

#include <vector>
using namespace std;


vector<item*> massa_testes_itens()
{
    vector<item*> v;
    
    for (int i=1;i<=5;i++){
        v.push_back(new item(i));
    }
    
    return v;
}
vector<transacao*> massa_testes_vendas(vector<item*> itens)
{
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

banco_dados::banco_dados(vector<item*> itens_a_venda, vector<transacao*> vendas)
{
    this->itens_a_venda = itens_a_venda;
    this->vendas = vendas;
}

banco_dados banco_dados::gerar_massa_testes(){
    vector<item*> its = massa_testes_itens();
    vector<transacao*> v = massa_testes_vendas(its);
    return banco_dados(its, v);
}

vector<vector<item*> > banco_dados::obter_conjunto_a_priori(float suporte_minimo){
    vector<vector<item*> > apriori;
    
    return apriori;
}