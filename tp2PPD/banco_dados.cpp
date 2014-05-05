#include "banco_dados.h"
#include "transacao.h"
#include "globals.h"
#include <mpi.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <time.h>
using namespace std;

vector<item*> massa_testes_itens() {
    vector<item*> v;

    for (int i = 1; i <= 500; i++) {
        v.push_back(new item(i));
    }

    return v;
}

vector<transacao*> massa_testes_vendas(vector<item*> itens) {
    vector<transacao*> t;

    srand(time(NULL));

    for (int i = 0; i < 100000; i++) {

        int num_itens = rand() % 5 + 20;

        transacao* trans = new transacao(i + 1);

        for (int j = 0; j < num_itens; j++) {
            trans->adicionar_item_a_transacao(itens[rand() % 500 + 1]);
        }

        t.push_back(trans);
    }


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

map<int, vector<int> > carregar_arquivo_issues() {
    map<int, vector<int> > m;

    string linha;
    ifstream arquivo("/home/otmar/Downloads/issue_comments_PPD.csv");

    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            int posicao_separador = linha.find(";");
            string texto_issue_id = linha.substr(0, posicao_separador);
            int issue_id = atoi(texto_issue_id.c_str());

            string comentaristas_issue = linha.substr(posicao_separador + 1, linha.length() - posicao_separador - 1);
            stringstream ss(comentaristas_issue);
            vector<int> ids_comentaristas((istream_iterator<int>(ss)), (istream_iterator<int>()));
            m[issue_id] = ids_comentaristas;
        }
    } else {
        cout << "\nNão foi possível abrir o arquivo. Verifique se o processo corrente tem permissão de acesso.";
    }
    arquivo.close();

    return m;
}

banco_dados banco_dados::gerar_massa_testes_issues() {
    map<int, vector<int> > arquivo = carregar_arquivo_issues();

    map<int, item*> ids_comentaristas;
    vector<item*> comentaristas;
    vector<transacao*> issues;


    map<int, vector<int> >::iterator it_arquivo;

    for (it_arquivo = arquivo.begin(); it_arquivo != arquivo.end(); it_arquivo++) {
        int id_issue = it_arquivo->first;
        transacao* nova_issue = new transacao(id_issue);

        issues.push_back(nova_issue);
        for (int j = 0; j < it_arquivo->second.size(); j++) {
            int id_comentarista = it_arquivo->second[j];

            if (ids_comentaristas.count(id_comentarista) == 0) {
                item* novo_comentarista = new item(id_comentarista);
                ids_comentaristas[id_comentarista] = novo_comentarista;
                comentaristas.push_back(novo_comentarista);
                nova_issue->adicionar_item_a_transacao(novo_comentarista);
            } else {
                nova_issue->adicionar_item_a_transacao(ids_comentaristas[id_comentarista]);
            }
        }
    }


    return banco_dados(comentaristas, issues);
}

bool banco_dados::e_processo_mestre()
{
    return this->obter_id_processo_atual() == ID_PROCESSO_MESTRE;
}

itemset_frequente banco_dados::f1_itemset(double suporte_minimo) {
    int k = 1;
    itemset_frequente f1(k);
    int rank = this->obter_id_processo_atual();
    
    int N = this->itens_a_venda.size();
    int valor_inicial = N*this->obter_id_processo_atual()/this->obter_quantidade_processos()+1;
    if (rank==0){
        valor_inicial=0;
    }
    int valor_final = N*(this->obter_id_processo_atual()+1)/this->obter_quantidade_processos();
    double maior_sup;
    int total_enviados;
    int total_recebidos;
    int enviados[N];
    int recebidos[N];
    
    total_enviados = 0;
    total_recebidos = 0;
    maior_sup = 0;
    
    for (int i = valor_inicial; i<valor_final; i++) {
        item* it = this->itens_a_venda[i];

        int count_i = 0;
        int T = this->transacoes.size();
        for (int j = 0; j < T; j++) {
            transacao* t = this->transacoes[j];

            if (t->possui_item(it)) {
                count_i++;
            }
        }

        double suporte = count_i / (1.0 * T);
        
        if (suporte >= suporte_minimo) {
            enviados[total_enviados] = i;
            total_enviados++;
        }
        
        if (suporte > maior_sup){
            maior_sup = suporte;
        }
    }
    
    int posicao_ultimo_enviado = 0; 

    if (rank != ID_PROCESSO_MESTRE)
    {
        MPI_Send(&enviados,total_enviados, MPI_INT, ID_PROCESSO_MESTRE,1,MPI_COMM_WORLD);
    }
    else
    {
        posicao_ultimo_enviado = total_enviados; // continua do último do processo 0
        
        for (int j=1;j<this->obter_quantidade_processos();j++)
        {
            MPI_Status status;
            MPI_Recv(&recebidos,N, MPI_INT,j,1,MPI_COMM_WORLD,&status);
            MPI_Get_count(&status, MPI_INT, &total_recebidos);
            
            for (int k=posicao_ultimo_enviado;k<posicao_ultimo_enviado+total_recebidos;k++)
            {
                enviados[k] = recebidos[k-posicao_ultimo_enviado];
            }
            
            posicao_ultimo_enviado += total_recebidos;
        }
    }
    MPI_Bcast(&enviados, posicao_ultimo_enviado, MPI_INT, 0, MPI_COMM_WORLD);
    
    
    for (int i=0;i<posicao_ultimo_enviado;i++)
    {
        vector<item*> v;
        v.push_back(this->itens_a_venda[enviados[i]]);
        f1.adicionar_conjunto(v);
    }
    
    return f1;
}

vector<itemset_frequente> banco_dados::obter_conjunto_a_priori(double suporte_minimo) {
    vector<itemset_frequente> L;

    itemset_frequente L1 = f1_itemset(suporte_minimo);
    
    itemset_frequente LkmenosUm = L1;
    itemset_frequente Lk = L1;
    L.push_back(L1);

    for (int k = 2; !LkmenosUm.esta_vazio(); k++) {
        itemset_frequente Ck = apriori_gen(LkmenosUm);
        vector<int> count_c(Ck.tamanho(), 0);

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

        
        int T = this->transacoes.size();
        Lk = itemset_frequente(k);
        L.push_back(Lk);

        for (int i = 0; i < count_c.size(); i++) {
            if (count_c[i] / (1.0f * T) >= suporte_minimo) {
                Lk.adicionar_conjunto(Ck[i]);
            }
        }

        LkmenosUm = Lk; // Prepara para próxima iteração.
    }

    return L;
}

itemset_frequente banco_dados::apriori_gen(itemset_frequente Lkmenos1) {
    if (this->obter_id_processo_atual()==1)
        cout<<"Processo 1 entrou no apriori gen - DENTRO DO MÉTODO!";
    
    int k = Lkmenos1.k();
    int kMenosUm = k - 1; // Offset por conta do índice 0
    int KMenosDois = k - 2; // Offset por conta do índice 0

    if (KMenosDois < 0) {
        KMenosDois = 0;
    }

    if (kMenosUm < 0) {
        kMenosUm = 0;
    }

    itemset_frequente Ck(k + 1);

    int rank = this->obter_id_processo_atual();
    int N = Lkmenos1.tamanho();
    
    int valor_inicial = N*rank/this->obter_quantidade_processos()+1;
    if (rank==0){
        valor_inicial=0;
    }
    
    int valor_final = N*(rank+1)/this->obter_quantidade_processos();
    
    int total_enviados=0;
    int enviados[2*N];
    int recebidos[2*N];
    
    
    
    for (int i = valor_inicial; i < valor_final; i++) {
        vector<item*> l1 = Lkmenos1[i];

        for (int j = 0; j < N; j++) {

            bool igualAteKMenosDois = true;
            vector<item*> l2 = Lkmenos1[j];

            for (int x = 0; x < KMenosDois; x++) {
                if (l1[x] != l2[x]) {
                    igualAteKMenosDois = false;
                    break;
                }
            }

            int l1KMenosUm = l1[kMenosUm]->identificador();
            int l2LKmenosUm = l2[kMenosUm]->identificador();
            if (igualAteKMenosDois && l1KMenosUm < l2LKmenosUm) {
                vector<item*> c12(l1);
                item* l2 = &l2[kMenosUm];
                c12.push_back(l2);
               

                if (!tem_sub_conjunto_infrequente(c12, Lkmenos1)) {
                    //Ck.adicionar_conjunto(c12);
                    enviados[total_enviados] = i;
                    enviados[total_enviados+1] = j;
                    total_enviados+=2;
                }
            }
        }
    }

    int posicao_ultimo_enviado = 0; 
    int total_recebidos = 0;
    if (rank != ID_PROCESSO_MESTRE)
    {
        MPI_Send(&enviados,total_enviados, MPI_INT, ID_PROCESSO_MESTRE,1,MPI_COMM_WORLD);
    }
    else
    {
        posicao_ultimo_enviado = total_enviados; // continua do último que o processo 0 registrou.
        
        for (int j=1;j<this->obter_quantidade_processos();j++)
        {
            MPI_Status status;
            MPI_Recv(&recebidos,N, MPI_INT,j,1,MPI_COMM_WORLD,&status);
            MPI_Get_count(&status, MPI_INT, &total_recebidos);
            
            for (int k=posicao_ultimo_enviado;k<posicao_ultimo_enviado+total_recebidos;k++)
            {
                enviados[k] = recebidos[k-posicao_ultimo_enviado];
            }
            
            posicao_ultimo_enviado += total_recebidos;
        }
    }
    MPI_Bcast(&enviados, posicao_ultimo_enviado, MPI_INT, 0, MPI_COMM_WORLD);
    
    
    for (int i=0;i<posicao_ultimo_enviado-1;i+=2)
    {
        vector<item*> l1 = Lkmenos1[i];
        vector<item*> l2 = Lkmenos1[i+1]; // Posição a frente guardou j
        vector<item*> c12(l1);
        item* li2 = l2[kMenosUm];
        c12.push_back(li2);
        Ck.adicionar_conjunto(c12);
    }
    
    if (OUTPUT_DEBUG) {
        for (int i = 0; i < Ck.tamanho(); i++) {
            cout << "\nCk[" << i << "] = {";
            for (int j = 0; j < Ck[i].size(); j++) {
                cout << " " << Ck[i][j]->identificador();
            }
            cout << "}";
        }
    }
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

int banco_dados::obter_id_processo_atual() {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    return rank;
}

int banco_dados::obter_quantidade_processos() {
    int tamanho;
    MPI_Comm_size(MPI_COMM_WORLD, &tamanho); /* get number of processes */
    return tamanho;
}