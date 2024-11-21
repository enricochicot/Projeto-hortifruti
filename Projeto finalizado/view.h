#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <limits>

#include "Secao.h"

using namespace std;

class View {
public:
    // Função para limpar o console
    void limparConsole();

    // Função para formatar valores monetários como uma string
    string formatMoney(double value);

    // Função para confirmar uma operação com o usuário
    bool confirmarOperacao(const string &mensagem);

    // Função para validar um preço e convertê-lo para double
    bool validarPreco(const string &preco, double &precoValidado);

    // Função para validar uma quantidade e convertê-la para int
    bool validarQuantidade(const string &quantidade, int &quantidadeValidada);

    // Função para validar um peso e retorná-lo como uma string formatada
    string validarPeso(const string &peso);

    // Função para exibir o menu da seção e processar as opções do usuário
    void menuSecao(Secao &secao);

    void start();
};
#endif // VIEW_H