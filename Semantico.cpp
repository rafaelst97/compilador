#include "Semantico.h"
#include "Constants.h"
#include <vector>
#include <iostream>
#include <stack>
#include "SemanticError.h"
#include "dependencies/json.hpp"
#include <fstream>
#include <QFile>
#include <QTextStream>
//#include <QDebug>

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

//geração de codigo
string ponto_data = ".data\n";
string ponto_text = ".text\n";
string entrada_saida_dado = "";
vector<string> pilha_operador;
string recebe_atrib = "";
int vetor_tamanho = 0;
bool escrever_text = false;
bool temp1 = false;
bool temp2 = false;
bool temp3 = false;
bool calculando_indice = false;
bool inicio_atribuicao = true;
bool entrando_no_indice = false;

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
    simbolo simb_aux;
    string operador;

    if (pilha_escopo.empty()) {
        pilha_escopo.push_back(0);
    }

    cout << "action: " << action << " str: " << str << endl;

    switch (action) {

    case 1:
        tipo_declaracao = str;
        lista_simb_aux.clear();

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

        // geração de codigo

        for (auto& i : lista_simb_aux) {
            for (auto& s : lista_simbolos) {
                if (s.nome == i.nome && s.escopo == i.escopo) {

                    if (s.vetor == false) {
                        ponto_data += s.nome + ":0\n";

                        escrever_text = true;
                    }
                }
            }
        }
        //geração de codigo



        tipo_declaracao = "";

        break;

    case 4:
        if (procura_simbolo(str) == false) {
            throw SemanticError("Variavel nao declarada.");
        }
        else {
            //lista_simb_aux.clear();
            for (auto& s : lista_simbolos) {
                if (s.nome == str and s.escopo == pilha_escopo[pilha_escopo.size() - 1]) {
                    cout << "insere na lista aux" << s.nome << s.escopo << endl << endl;
                    lista_simb_aux.push_back(s);

                }
            }

            escrever_text = true;

            if (entrada_saida_dado == "ENTRADA") {
                ponto_text += "\nLD $in_port";
                ponto_text += "\nSTO " + str;
                entrada_saida_dado = "";
            }
            else if (entrada_saida_dado == "SAIDA") {
                ponto_text += "\nLD " + str;
                ponto_text += "\nSTO $out_port";
                entrada_saida_dado = "";
            }

            if (recebe_atrib == "") {
                recebe_atrib = str;
            }
        }


        break;

    case 5:
        if (procura_simbolo(str, true) == false) {
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
        for (auto& i : lista_simb_aux) {
            for (auto& s : lista_simbolos) {
                if (s.nome == i.nome && s.escopo == i.escopo) {
                    s.iniciado = true;

                    if (s.vetor == true) {
                        ponto_text += "\nSTO 1002";
                        temp3 = true;
                    }
                }
            }
        }

        inicio_atribuicao = false;
        break;

    case 11:
        for (auto& i : lista_simb_aux) {
            for (auto& s : lista_simbolos) {
                if (s.nome == i.nome && s.escopo == i.escopo) {
                    s.vetor = true;

                    // adiciona no .data o nome do vetor
                    ponto_data += s.nome + ":";

                    // e a quantidade de '0' para definir o tamanho
                    for (int i = 0; i < vetor_tamanho; i++) {
                        ponto_data += '0';
                        if (i < vetor_tamanho - 1) {
                            ponto_data += ',';
                        }
                    }
                    ponto_data += "\n";

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

        // geracao de codigo


        if (!pilha_operador.empty()) {
            operador = pilha_operador.back();
        }
        else {
            operador = "";
        }

        if (operador == "") {
            ponto_text += "\nLD " + str;
            if (temp1 == false && calculando_indice == false) {
                ponto_text += "\nSTO 1000";
                temp1 = true;

            }
        }
        else if (operador == "SOMA") {
            ponto_text += "\nADD " + str;
            pilha_operador.pop_back();
        }
        else if (operador == "SUBTRACAO") {
            ponto_text += "\nSUB " + str;
            pilha_operador.pop_back();
        }
        else if (operador == "AND") {
            if (temp1 == true) {
                ponto_text += "\nLD 1000";
                ponto_text += "\nAND " + str;
                ponto_text += "\nSTO 1000";

                pilha_operador.pop_back();
            }
        }
        else if (operador == "OR_BIT") {
            if (temp1 == true) {
                ponto_text += "\nLD 1000";
                ponto_text += "\nOR " + str;
                ponto_text += "\nSTO 1000";

                pilha_operador.pop_back();
            }
        }
        else if (operador == "XOR_BIT") {
            if (temp1 == true) {
                ponto_text += "\nLD 1000";
                ponto_text += "\nXOR " + str;
                ponto_text += "\nSTO 1000";

                pilha_operador.pop_back();
            }
        }
        else if (operador == "NOT") {
            ponto_text += "\nNOT " + str;
            //ponto_text += "\nSTO 1000";

            pilha_operador.pop_back();
        }

        entrando_no_indice = false;

        break;

    case 13:

        cout << str;
        break;

    case 14:

        if (str == "+") {
            pilha_operador.push_back("SOMA");
        }
        else if (str == "-") {
            pilha_operador.push_back("SUBTRACAO");
        }

        break;

    case 20:
        // geracao de codigo

        if (pilha_operador.empty() == false) {
            operador = pilha_operador.back();
        }
        else {
            operador = "";
        }

        if (operador == "" || (operador == "" && calculando_indice == true)) {
            if (escrever_text) {
                ponto_text += "\nLDI " + str;

                if (temp1 == false && calculando_indice == false) {
                    ponto_text += "\nSTO 1000";
                    temp1 = true;
                }
                entrando_no_indice = false;
            }
            vetor_tamanho = atoi(str.c_str());
        }
        else if (operador == "SOMA") {
            if (escrever_text) {
                if (calculando_indice == false) {
                    if (temp1 == true) {
                        ponto_text += "\nLD 1000";
                        ponto_text += "\nADDI " + str;
                        ponto_text += "\nSTO 1000";
                        pilha_operador.pop_back();
                    }

                }
                else if (calculando_indice == true && entrando_no_indice == false) {
                    ponto_text += "\nADDI " + str;
                    pilha_operador.pop_back();
                }
                else if (calculando_indice == true && entrando_no_indice == true) {
                    ponto_text += "\nLDI " + str;
                    entrando_no_indice = false;
                }
            }

            //pilha_operador.pop_back();
            vetor_tamanho += atoi(str.c_str());
        }
        else if (operador == "SUBTRACAO") {
            if (escrever_text) {
                if (calculando_indice == false) {
                    if (temp1 == true) {
                        ponto_text += "\nLD 1000";
                        ponto_text += "\nSUBI " + str;
                        ponto_text += "\nSTO 1000";
                        pilha_operador.pop_back();
                    }

                }
                else if (calculando_indice == true && entrando_no_indice == false) {
                    ponto_text += "\nSUBI " + str;
                    pilha_operador.pop_back();
                }
                else if (calculando_indice == true && entrando_no_indice == true) {
                    ponto_text += "\nLDI " + str;
                    entrando_no_indice = false;
                }
            }

            //pilha_operador.pop_back();
            vetor_tamanho += atoi(str.c_str());
        }
        else if (operador == "AND") {
            if (escrever_text) {
                if (temp1 == true) {
                    ponto_text += "\nLD 1000";
                    ponto_text += "\nANDI " + str;
                    ponto_text += "\nSTO 1000";

                    pilha_operador.pop_back();
                }
            }
        }
        else if (operador == "OR_BIT") {
            if (escrever_text) {
                if (temp1 == true) {
                    ponto_text += "\nLD 1000";
                    ponto_text += "\nORI " + str;
                    ponto_text += "\nSTO 1000";

                    pilha_operador.pop_back();
                }
            }
        }
        else if (operador == "XOR_BIT") {
            if (escrever_text) {
                if (temp1 == true) {
                    ponto_text += "\nLD 1000";
                    ponto_text += "\nXORI " + str;
                    ponto_text += "\nSTO 1000";

                    pilha_operador.pop_back();
                }
            }
        }
        else if (operador == "NOT") {
            if (escrever_text) {
                ponto_text += "\nNOT " + str;

                pilha_operador.pop_back();
            }
        }

        break;

    case 21:
        entrada_saida_dado = "ENTRADA";
        break;

    case 22:
        entrada_saida_dado = "SAIDA";
        break;


    case 23:

        if (!pilha_operador.empty()) {
            operador = pilha_operador.back();
        }
        else {
            operador = "";
        }

        /*
        if (lista_simb_aux.size() >= 2) {
            simb_aux = lista_simb_aux.back();
            ponto_text += "\nSTO $indr";
            ponto_text += "\nLDV" + simb_aux.nome;
        }
        */

        if (temp1 == false) {
            ponto_text += "\nSTO 1000";
            temp1 = true;
        }
        else if (temp1 == true && operador != "") {
            ponto_text += "\nSTO 1001 CUUUU";
            ponto_text += "\nLD 1000";

            if (operador == "SOMA") {
                ponto_text += "\nADD 1001";
            }
            else if (operador == "SUBTRACAO") {
                ponto_text += "\nSUB 1001";
            }
            ponto_text += "\nSTO 1000";
            if (!pilha_operador.empty()) {
                pilha_operador.pop_back();
            }
        }

        break;

    case 24:
        pilha_operador.push_back("AND");
        break;

    case 25:

        for (auto& i : lista_simb_aux) {
            for (auto& s : lista_simbolos) {
                if (s.nome == i.nome && s.escopo == i.escopo) {
                    ponto_text += "\nLD 1000 ";
                    ponto_text += "\nSTO " + s.nome;
                }
            }
        }

        break;

    case 26:
        lista_simb_aux.clear();
        tipo_declaracao = "";
        entrada_saida_dado = "";
        pilha_operador.clear();
        recebe_atrib = "";
        vetor_tamanho = 0;
        escrever_text = false;
        temp1 = false;
        temp2 = false;
        temp3 = false;
        inicio_atribuicao = true;
        entrando_no_indice = false;


        break;

    case 27:

        simb_aux = lista_simb_aux.front();

        if (temp3 == true) {
            ponto_text += "\nLD 1002";
            ponto_text += "\nSTO $indr";

            if (temp1 == true) {
                ponto_text += "\nLD 1000";
                ponto_text += "\nSTOV " + simb_aux.nome;

            }

        }
        else {
            if (temp1 == true) {
                ponto_text += "\nLD 1000";
                ponto_text += "\nSTO " + simb_aux.nome;

            }
        }

        break;

    case 28:
        // inicio de indice vetor

        calculando_indice = true;
        entrando_no_indice = true;

        break;



    case 30:
        pilha_operador.push_back("OR_BIT");
        break;

    case 31:
        pilha_operador.push_back("XOR_BIT");
        break;

    case 32:
        pilha_operador.push_back("NOT");
        break;

    case 29:
        // fim de indice vetor
        calculando_indice = false;

        if (!pilha_operador.empty()) {
            operador = pilha_operador.back();
        }
        else {
            operador = "";
        }

        const auto& i = lista_simb_aux.back();

        if (inicio_atribuicao == false) {
            ponto_text += "\nSTO $indr";
            ponto_text += "\nLDV " + i.nome;
        }

        if (inicio_atribuicao == false) {

            if (temp1 == false) {
                ponto_text += "\nSTO 1000";
                temp1 = true;
            }
            else {
                ponto_text += "\nSTO 1001";
                temp2 = true;

                ponto_text += "\nLD 1000";
                if (operador == "SOMA") {
                    ponto_text += "\nADD 1001";
                    ponto_text += "\nSTO 1000";
                    temp2 = false;
                    pilha_operador.pop_back();

                }
                else if (operador == "SUBTRACAO") {
                    ponto_text += "\nSUB 1001";
                    ponto_text += "\nSTO 1000";
                    temp2 = false;
                    pilha_operador.pop_back();
                }

            }
        }
        break;


    }


    // Iterando pela lista e imprimindo os símbolos
    cout << endl << "------------- lista de simbolos ------------" << endl;
    for (const auto& s : lista_simbolos) {
        std::cout << "Tipo: " << s.tipo << ", Nome: " << s.nome << ", Escopo: " << s.escopo << ", Iniciado: " << s.iniciado << ", Vetor: " << s.vetor << ", Usado: " << s.usado << std::endl;
    }
    // Iterando pela lista e imprimindo os símbolos
    cout << endl << "------------- Pilha de escopo ------------" << endl;
    for (const auto& e : pilha_escopo) {
        cout << "Escopo: " << e << endl;
    }
    cout << "------------- Fim ------------" << endl << endl;

    cout << "------------ codigo ------------" << endl << endl;
    cout << ponto_data << endl << ponto_text << endl << "HLT 0" << endl;


    // Criando o JSON com a lista de símbolos
    json jsonSimbolos;
    QString codigoAssembly = QString::fromStdString(ponto_data) + "\n";
    codigoAssembly += QString::fromStdString(ponto_text);

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

    if (!codigoAssembly.isEmpty()){
        // Nome do arquivo onde a string será salva
        QString nomeDoArquivo = "temp.tmp";
        // Cria uma instância de QFile e abre o arquivo
        QFile arquivo(nomeDoArquivo);

        // Verificar se o arquivo foi aberto corretamente
        if (arquivo.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            // Cria um QTextStream para escrever no arquivo
            QTextStream saida(&arquivo);
            // Escreve a string no arquivo
            saida << codigoAssembly;
            // Fecha o arquivo
            arquivo.close();
            //qDebug() << "String salva com sucesso no arquivo" << nomeDoArquivo;
        } else {
            //qDebug() << "Não foi possível abrir o arquivo" << nomeDoArquivo;
        }
    }

}

void Semantico::limpaSemantico(){
    lista_simbolos.clear();
    pilha_escopo.clear();
}


