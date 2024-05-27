#include "Semantico.h"
#include "Constants.h"
#include <vector>
#include <iostream>
#include <stack>
#include "SemanticError.h"
#include "dependencies/json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;


struct simbolo {
    string tipo;
    string nome;
    bool iniciado;
    bool usado;
    int escopo;
    bool parametro;
    int pos_param;
    bool vetor;
    bool matriz;
    bool ref;
    bool funcao;
    bool proc; // procedimento || funcao sem return || void
};

vector<simbolo> lista_simbolos;
vector<int> pilha_escopo;
vector<simbolo> lista_simb_aux; // essa lista serve pra marcar os simbolos como inicializados
string tipo_declaracao;
int escopo_cont = 0;

bool verifica_escopo(int simb_escopo) {

    // Percorre o vetor procurando pelo valor
    for (int i = 0; i < pilha_escopo.size(); ++i) {
        if (pilha_escopo[i] == simb_escopo) {
            return true;
        }
    }
    return false;

}

bool procura_simbolo(string nome) {
    // Iterando pela lista
    for (auto& s : lista_simbolos) {
        if (s.nome == nome) {
            if (verifica_escopo(s.escopo)){
                return true;
            }
        }
    }
    return false;
}

bool procura_simbolo(string nome, bool funcao) {
    // Iterando pela lista
    for (const auto& s : lista_simbolos) {
        if (s.nome == nome && s.funcao == funcao) {
            if (verifica_escopo(s.escopo)) {
                return true;
            }
        }

    }
    return false;
}

simbolo iniciliaza_simbolo() {
    simbolo simb;
    simb.tipo       = "";
    simb.nome       = "";
    simb.iniciado   = false;
    simb.usado      = false;
    simb.escopo     = 0;
    simb.parametro  = false;
    simb.pos_param  = 0;
    simb.vetor      = false;
    simb.matriz     = false;
    simb.ref        = false;
    simb.funcao     = false;
    simb.proc       = false;
    return simb;
}

void insere_na_tabela(simbolo simb) {

    for (const auto& s : lista_simbolos) {
        // Verifica se a variável já foi declarada no mesmo escopo
        if (simb.nome == s.nome && simb.escopo == s.escopo) {
            throw SemanticError("Variavel ja declarada no escopo atual.");
        }
    }
    lista_simbolos.push_back(simb);
}

void Semantico::executeAction(int action, const Token* token) noexcept(false)
{
    int a, b;
    string str;
    str = token->getLexeme();
    simbolo simb;

    if (pilha_escopo.empty()) {
        pilha_escopo.push_back(0);
    }

    cout << "action: " << action << " str: " << str << endl;

    switch (action) {

    case 1:
        tipo_declaracao = str;
        break;

    case 2:
        if (!tipo_declaracao.empty()) { // verifica se foi definido o tipo do simbolo [ex: int, float, etc...]
            simb = iniciliaza_simbolo();
            simb.nome = str;
            simb.tipo = tipo_declaracao;
            simb.escopo = pilha_escopo[pilha_escopo.size() - 1];
            insere_na_tabela(simb);

            lista_simb_aux.push_back(simb); //coloca na lista para caso chegar na action #10, marcar como inicializado
        }
        else
        {
            throw SemanticError("Tipo nao declarado.");
        }
        break;

    case 3:
        tipo_declaracao = "";
        lista_simb_aux.clear();
        //lista_simb_aux.clear();
        break;

    case 4:
        if (procura_simbolo(str) == false) {
            throw SemanticError("Variavel nao declarada.");
        }
        else {
            for (auto& s : lista_simbolos) {
                if (s.nome == str and s.escopo == pilha_escopo[pilha_escopo.size() - 1]) {
                    cout << "insere na lista aux" << s.nome << s.escopo << endl << endl;
                    lista_simb_aux.push_back(s);

                }
            }
        }
        break;

    case 5:
        if (procura_simbolo(str,true) == false){
            throw SemanticError("Funcao nao declarada.");
        }
        break;

    case 6:
        if (!tipo_declaracao.empty()) {
            simb = iniciliaza_simbolo();
            simb.nome = str;
            simb.tipo = tipo_declaracao;
            simb.funcao = true;
            insere_na_tabela(simb);
        }
        else
        {
            throw SemanticError("Tipo nao declarado.");
        }
        break;

    case 7:
        simb = iniciliaza_simbolo();
        simb.nome = str;
        simb.proc = true;
        insere_na_tabela(simb);
        break;

    case 8:
        escopo_cont++;
        pilha_escopo.push_back(escopo_cont);
        break;

    case 9:
        pilha_escopo.pop_back();
        break;

    case 10:
        cout << lista_simb_aux.size();
        for (auto& i : lista_simb_aux) {
            cout <<endl<<"CU "<< i.nome << endl;
            for (auto& s : lista_simbolos) {
                if (s.nome == i.nome && s.escopo == i.escopo) {
                    cout << "Entrou no iniciado";
                    s.iniciado = true;
                }
            }
        }
        //lista_simb_aux.clear();
        break;

    case 11:
        for (auto& i : lista_simb_aux) {
            for (auto& s : lista_simbolos) {
                if (s.nome == i.nome && s.escopo == i.escopo) {
                    s.vetor = true;
                }
            }
        }
        break;

    case 12:

        cout << endl << "------------- lista de simbolos ------------" << endl;
        for (auto& s : lista_simbolos) {
            if (s.nome == str and s.escopo == pilha_escopo[pilha_escopo.size() - 1]) {
                s.usado = true;
            }
        }
        break;

    case 13:

        cout << str;
        break;

    case 14:

        cout << str;
        break;
    }

    // Iterando pela lista e imprimindo os símbolos
    cout << endl << "------------- lista de simbolos ------------" << endl;
    for (const auto& s : lista_simbolos) {
        std::cout << "Tipo: " << s.tipo << ", Nome: " << s.nome << ", Escopo: " << s.escopo <<  ", Iniciado: " << s.iniciado <<  ", Vetor: " << s.vetor <<  ", Usado: " << s.usado  << std::endl;
    }
    // Iterando pela lista e imprimindo os símbolos
    cout << endl << "------------- Pilha de escopo ------------" << endl;
    for (const auto& e : pilha_escopo) {
        cout << "Escopo: " << e <<endl;
    }
    cout << "------------- Fim ------------" << endl << endl;


    // Criando o JSON com a lista de símbolos
    json jsonSimbolos;
    for (const auto& s : lista_simbolos) {
        json simboloJson;
        simboloJson["tipo"] = s.tipo;
        simboloJson["nome"] = s.nome;
        simboloJson["iniciado"] = s.iniciado;
        simboloJson["usado"] = s.usado;
        simboloJson["escopo"] = s.escopo;
        simboloJson["parametro"] = s.parametro;
        simboloJson["pos_param"] = s.pos_param;
        simboloJson["vetor"] = s.vetor;
        simboloJson["matriz"] = s.matriz;
        simboloJson["ref"] = s.ref;
        simboloJson["funcao"] = s.funcao;
        simboloJson["proc"] = s.proc;
        jsonSimbolos.push_back(simboloJson);
    }
    if (!jsonSimbolos.empty()) {
        // Abrir o arquivo para escrita
        std::ofstream outputFile("simbolos.json");
        // Verificar se o arquivo foi aberto corretamente
        if (outputFile.is_open()) {
            // Escrever o JSON no arquivo
            outputFile << jsonSimbolos.dump(4);
            // Fechar o arquivo
            outputFile.close();
        } else {
            // Se houver um problema ao abrir o arquivo, exibir uma mensagem de erro
            cout << "Erro ao abrir o arquivo para escrita." << endl;
        }
    }

}

void Semantico::limpaSemantico(){
    lista_simbolos.clear();
    pilha_escopo.clear();
}


