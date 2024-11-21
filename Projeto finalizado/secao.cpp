#include "secao.h"

Secao::Secao(const string& t) : titulo(t) {
    if (t.empty()) {
        throw invalid_argument("\nO titulo da secao nao pode ser vazio.\n");
    }
}

string Secao::getTitulo() const {
    return titulo;
}

void Secao::adicionarItem(const string& nome, const string& quantidade, const string& preco, const string& peso, bool exibirMensagem) {
    string arquivoPath = "./db/" + titulo + ".csv";
    ifstream arquivoLeitura(arquivoPath);

    if (!arquivoLeitura.is_open()) {
        cout << "Erro ao abrir o arquivo para carregar os dados." << endl;
        return;
    }

    string linha;
    vector<vector<string>> itensCarregados;

    // Ignorar a primeira linha que contém o título
    getline(arquivoLeitura, linha);

    // Ignorar a segunda linha que contém os cabeçalhos das colunas
    getline(arquivoLeitura, linha);

    // Ler os itens do arquivo
    while (getline(arquivoLeitura, linha)) {
        istringstream stream(linha);
        vector<string> item;
        string campo;

        // Extrair cada campo separado por vírgula
        while (getline(stream, campo, ',')) {
            // Remover aspas do campo, se houver
            if (campo.front() == '\"' && campo.back() == '\"') {
                campo = campo.substr(1, campo.size() - 2);
            }
            item.push_back(campo);
        }

        itensCarregados.push_back(item);
    }

    arquivoLeitura.close();

    try {
        string pesoValidado = validarPeso(peso);
        int novoIndice = itensCarregados.size() + 1;
        itensCarregados.push_back({ to_string(novoIndice), nome, quantidade, preco, pesoValidado });

        // Salvar os itens de volta no arquivo CSV
        ofstream arquivoEscrita(arquivoPath);
        if (!arquivoEscrita.is_open()) {
            cout << "Erro ao abrir o arquivo para salvar os dados." << endl;
            return;
        }

        // Escrever cabeçalhos novamente
        arquivoEscrita << "Titulo," << titulo << "\n";
        arquivoEscrita << "Indice, Nome, Quantidade, Preco/KG, Peso\n";

        // Escrever os itens (incluindo o novo) de volta no arquivo CSV
        for (const auto& item : itensCarregados) {
            arquivoEscrita << item[0] << ",";
            arquivoEscrita << "\"" << item[1] << "\"" << ",";
            arquivoEscrita << item[2] << ",";
            arquivoEscrita << item[3] << ",";
            arquivoEscrita << item[4] << "\n";
        }

        arquivoEscrita.close();
        if (exibirMensagem) {
            cout << "Item '" << nome << "' Adicionado com sucesso!" << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "\nErro ao adicionar item:\n " << e.what() << endl;
        cout << "Use formatos como: 1kg, 100g, 1000mg" << endl;
    }
}

void Secao::excluirItem(int index) {
    string arquivoPath = "./db/" + titulo + ".csv";
    ifstream arquivoLeitura(arquivoPath);

    if (!arquivoLeitura.is_open()) {
        cout << "Erro ao abrir o arquivo para carregar os dados." << endl;
        return;
    }

    string linha;
    vector<vector<string>> itensCarregados;

    // Ignorar a primeira linha que contém o título
    getline(arquivoLeitura, linha);

    // Ignorar a segunda linha que contém os cabeçalhos das colunas
    getline(arquivoLeitura, linha);

    // Ler os itens do arquivo
    while (getline(arquivoLeitura, linha)) {
        if (linha.empty()) continue; // Ignorando linhas vazias

        istringstream stream(linha);
        vector<string> item;
        string campo;

        // Extrair cada campo separado por vírgula
        while (getline(stream, campo, ',')) {
            // Remover aspas do campo, se houver
            if (!campo.empty() && campo.front() == '\"' && campo.back() == '\"') {
                campo = campo.substr(1, campo.size() - 2);
            }
            item.push_back(campo);
        }

        if (!item.empty()) itensCarregados.push_back(item);
    }

    arquivoLeitura.close();

    if (index < 0 || index >= static_cast<int>(itensCarregados.size())) {
        cout << "Indice invalido. Nao foi possivel excluir o item." << endl;
        return;
    }

    // Excluir o item específico
    itensCarregados.erase(itensCarregados.begin() + index);

    // Salvar os itens de volta no arquivo CSV
    ofstream arquivoEscrita(arquivoPath);
    if (!arquivoEscrita.is_open()) {
        cout << "Erro ao abrir o arquivo para salvar os dados." << endl;
        return;
    }

    // Escrever cabeçalhos novamente
    arquivoEscrita << "Titulo," << titulo << "\n";
    arquivoEscrita << "Indice, Nome, Quantidade, Preço/KG, Peso\n";

    // Escrever os itens (excluindo o item) de volta no arquivo CSV
    for (size_t i = 0; i < itensCarregados.size(); ++i) {
        const auto& item = itensCarregados[i];
        if (item.size() >= 5) {
            arquivoEscrita << (i + 1) << ",";
            arquivoEscrita << "\"" << item[1] << "\"" << ",";
            arquivoEscrita << item[2] << ",";
            arquivoEscrita << item[3] << ",";
            arquivoEscrita << item[4] << "\n";
        }
    }

    arquivoEscrita.close();
    cout << "\nItem excluido com sucesso!\n" << endl;
}

void Secao::alterarItem(int index, const string& novoNome, const string& novaQuantidade, const string& novoPreco, const string& novoPeso) {
    string arquivoPath = "./db/" + titulo + ".csv";
    ifstream arquivoLeitura(arquivoPath);

    if (!arquivoLeitura.is_open()) {
        cout << "Erro ao abrir o arquivo para carregar os dados." << endl;
        return;
    }

    string linha;
    vector<vector<string>> itensCarregados;

    // Ignorar a primeira linha que contém o título
    getline(arquivoLeitura, linha);

    // Ignorar a segunda linha que contém os cabeçalhos das colunas
    getline(arquivoLeitura, linha);

    // Ler os itens do arquivo
    while (getline(arquivoLeitura, linha)) {
        istringstream stream(linha);
        vector<string> item;
        string campo;

        // Extrair cada campo separado por vírgula
        while (getline(stream, campo, ',')) {
            // Remover aspas do campo, se houver
            if (campo.front() == '\"' && campo.back() == '\"') {
                campo = campo.substr(1, campo.size() - 2);
            }
            item.push_back(campo);
        }

        itensCarregados.push_back(item);
    }

    arquivoLeitura.close();

    if (index < 0 || index >= static_cast<int>(itensCarregados.size())) {
        cout << "Indice invalido. Nao foi possivel alterar o item." << endl;
        return;
    }

    // Alterar o item específico
    itensCarregados[index] = { to_string(index + 1), novoNome, novaQuantidade, novoPreco, novoPeso };

    // Salvar os itens de volta no arquivo CSV
    ofstream arquivoEscrita(arquivoPath);
    if (!arquivoEscrita.is_open()) {
        cout << "Erro ao abrir o arquivo para salvar os dados." << endl;
        return;
    }

    // Escrever cabeçalhos novamente
    arquivoEscrita << "Titulo," << titulo << "\n";
    arquivoEscrita << "Indice, Nome, Quantidade, Preco/KG, Peso\n";

    // Escrever os itens alterados
    for (const auto& item : itensCarregados) {
        arquivoEscrita << item[0] << ",";
        arquivoEscrita << "\"" << item[1] << "\"" << ",";
        arquivoEscrita << item[2] << ",";
        arquivoEscrita << item[3] << ",";
        arquivoEscrita << item[4] << "\n";
    }

    arquivoEscrita.close();
    cout << "\nItem alterado com sucesso!\n" << endl;
}

void Secao::exibirItens() const {
    ifstream arquivo("./db/" + titulo + ".csv");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo para carregar os dados." << endl;
        return;
    }

    string linha;
    vector<vector<string>> itensCarregados;

    // Ignorar a primeira linha que contém o título
    getline(arquivo, linha);

    // Ignorar a segunda linha que contém os cabeçalhos das colunas
    getline(arquivo, linha);

    // Ler os itens do arquivo
    while (getline(arquivo, linha)) {
        istringstream stream(linha);
        vector<string> item;
        string campo;

        // Extrair cada campo separado por vírgula
        while (getline(stream, campo, ',')) {
            // Remover aspas do campo, se houver
            if (campo.front() == '\"' && campo.back() == '\"') {
                campo = campo.substr(1, campo.size() - 2);
            }
            item.push_back(campo);
        }

        itensCarregados.push_back(item);
    }

    arquivo.close();

    if (itensCarregados.empty()) {
        cout << "\nNenhum item para exibir.\n" << std::endl;
        return;
    }

    cout << "+--------------------------------------------------------------+" << endl;
    cout << "| " << titulo;
    for (int i = titulo.length(); i < 39; i++) cout << " ";
    cout << " |" << endl;
    cout << "+--------------------------------------------------------------+" << endl;
    cout << "| Indice   | Nome       | Quantidade | Preco/KG   | Peso       |" << endl;
    cout << "+--------------------------------------------------------------+" << endl;

    for (size_t i = 0; i < itensCarregados.size(); ++i) {
        const auto& item = itensCarregados[i];
        cout << "| " << i + 1;
        for (int j = to_string(i + 1).length(); j < 8; j++) cout << " ";
        cout << " | " << item[1];  // Nome
        for (int j = item[1].length(); j < 10; j++) cout << " ";
        cout << " | " << item[2];  // Quantidade
        for (int j = item[2].length(); j < 10; j++) cout << " ";
        cout << " | " << item[3];  // Preço/KG
        for (int j = item[3].length(); j < 10; j++) cout << " ";
        cout << " | " << item[4];  // Peso
        for (int j = item[4].length(); j < 10; j++) cout << " ";
        cout << " |" << endl;
    }
    cout << "+--------------------------------------------------------------+" << endl;
}

string Secao::validarPeso(const string& peso) const {
    if (peso.empty()) {
        throw invalid_argument("Peso invalido.");
    }
    return peso;
}

string Secao::formatMoney(double value) const {
    ostringstream oss;
    oss << fixed << setprecision(2) << value;
    return oss.str();
}