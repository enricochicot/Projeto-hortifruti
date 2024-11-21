#ifndef SECAO_H
#define SECAO_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Secao
{
private:
    string titulo;
    vector<vector<string>> itens;
    string validarPeso(const string& peso) const;
    string formatMoney(double value) const;

public:
    Secao(const string& t);

    string getTitulo() const;
    void adicionarItem(const string& nome, const string& quantidade, const string& preco, const string& peso, bool exibirMensagem = true);
    void excluirItem(int index);
    void alterarItem(int index, const string& novoNome, const string& novaQuantidade, const string& novoPreco, const string& novoPeso);
    void exibirItens() const;
    void salvarDadosEmArquivo() const;
};

#endif // SECAO_H