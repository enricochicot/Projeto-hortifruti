#include "view.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <limits>

using namespace std;

void View::limparConsole() {
#ifdef _WIN32
    system("cls"); // Limpa o console no Windows
#else
    system("clear");  // Limpa o console em sistemas Unix (Linux e macOS)
#endif
}

string View::formatMoney(double value) {
    stringstream ss;
    ss << fixed << setprecision(2) << "R$ " << value;
    return ss.str();
}

bool View::confirmarOperacao(const string &mensagem) {
    char resposta;
    cout << mensagem << " (s/n): ";
    cin >> resposta;
    return (tolower(resposta) == 's');
}

bool View::validarPreco(const string &preco, double &precoValidado) {
    try {
        string precoLimpo = preco;
        size_t pos = precoLimpo.find("R$");
        if (pos != string::npos) {
            precoLimpo = precoLimpo.substr(pos + 2);
        }
        precoLimpo.erase(
            remove_if(precoLimpo.begin(), precoLimpo.end(), [](unsigned char c) { return isspace(c); }),
            precoLimpo.end());

        replace(precoLimpo.begin(), precoLimpo.end(), ',', '.');

        precoValidado = stod(precoLimpo);

        if (precoValidado <= 0) {
            throw invalid_argument("O preco deve ser maior que zero");
        }
        if (precoValidado > 1000000) {
            throw invalid_argument("Preco excede o limite maximo permitido");
        }

        return true;
    } catch (const exception &e) {
        cout << "Erro na validacao do preco: " << e.what() << endl;
        return false;
    }
}

bool View::validarQuantidade(const string &quantidade, int &quantidadeValidada) {
    try {
        string qtdLimpa = quantidade;
        qtdLimpa.erase(remove_if(qtdLimpa.begin(), qtdLimpa.end(), [](unsigned char c) { return isspace(c); }),
                       qtdLimpa.end());

        if (!all_of(qtdLimpa.begin(), qtdLimpa.end(), [](unsigned char c) { return isdigit(c); })) {
            throw invalid_argument("A quantidade deve conter apenas numeros");
        }

        quantidadeValidada = stoi(qtdLimpa);

        if (quantidadeValidada <= 0) {
            throw invalid_argument("A quantidade deve ser maior que zero");
        }
        if (quantidadeValidada > 10000) {
            throw invalid_argument("Quantidade excede o limite maximo permitido");
        }

        return true;
    } catch (const exception &e) {
        cout << "Erro na validacao da quantidade: " << e.what() << endl;
        return false;
    }
}

string View::validarPeso(const string &peso) {
    try {
        string pesoLimpo = peso;
        transform(pesoLimpo.begin(), pesoLimpo.end(), pesoLimpo.begin(), ::tolower);

        pesoLimpo.erase(remove_if(pesoLimpo.begin(), pesoLimpo.end(),
                                  [](unsigned char c) { return isspace(c); }),
                        pesoLimpo.end());

        string valorStr;
        string unidade;
        size_t pos = pesoLimpo.find_first_of("kmg");

        if (pos == string::npos) {
            throw invalid_argument("Unidade de peso nao especificada (use kg, g ou mg)");
        }

        valorStr = pesoLimpo.substr(0, pos);
        unidade = pesoLimpo.substr(pos);

        double valor = stod(valorStr);

        if (valor <= 0) {
            throw invalid_argument("O peso deve ser maior que zero");
        }

        double pesoEmKg = valor;
        if (unidade == "mg") {
            pesoEmKg /= 1000000;
        } else if (unidade == "g") {
            pesoEmKg /= 1000;
        } else if (unidade != "kg") {
            throw invalid_argument("Unidade de peso invalida (use kg, g ou mg)");
        }

        if (pesoEmKg > 1000) {
            throw invalid_argument("Peso excede o limite maximo permitido (1000 kg)");
        }

        char resultado[50];
        sprintf(resultado, "%.3f%s", pesoEmKg, "kg");
        return string(resultado);
    } catch (const exception &e) {
        throw invalid_argument(string("Erro na validacao do peso: ") + e.what());
    }
}

void View::menuSecao(Secao &secao) {
    int choice;
    do {
        limparConsole();
        // Adicionar uma linha indicando a seção atual
        cout << "\n=== Secao Atual:\n " << secao.getTitulo() << " ===" << endl;
        // Você precisará adicionar um getter getTitulo() na classe Secao
        cout << "\n1. Adicionar Item" << endl;
        cout << "2. Excluir Item" << endl;
        cout << "3. Alterar Item" << endl;
        cout << "4. Exibir Itens" << endl;
        cout << "5. Calculadora" << endl;
        cout << "6. Voltar" << endl;
        cout << "\nEscolha uma opcao: \n";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nOpcao invalida. Por favor, insira um numero.\n" << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Adicione esta linha para limpar o buffer

        switch (choice) {
            case 1: {
                secao.exibirItens(); // Certifique-se de que esta função está implementada corretamente
                string nome, quantidade, preco, peso;
                cout << "Digite o nome do item: ";
                getline(cin, nome);
                cout << "Digite a quantidade do item: ";
                getline(cin, quantidade);
                cout << "Digite o preco do item: ";
                getline(cin, preco);
                cout << "Digite o peso do item (ex: 1kg, 100g, 1000mg): ";
                getline(cin, peso);
                secao.adicionarItem(nome, quantidade, preco, peso);
                break;
            }
            case 2: {
                limparConsole();
                secao.exibirItens(); // Exibe os itens para o cliente
                int index;
                char confirmacao;
                cout << "Digite o indice do item a ser excluido: ";
                cin >> index;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nTem certeza que deseja excluir este item? (s/n): ";
                cin >> confirmacao;
                if (tolower(confirmacao) == 's') {
                    secao.excluirItem(index - 1);
                } else {
                    cout << "\nOperacao de exclusao cancelada.\n" << endl;
                }
                break;
            }
            case 3: {
                limparConsole();
                secao.exibirItens(); // Exibe os itens para o cliente
                int index;
                char confirmacao; // Adição de uma variável char confirmacao para armazenar a resposta do usuário
                string novoNome, novaQuantidade, novoPreco, novoPeso;
                cout << "Digite o indice do item a ser alterado: ";
                cin >> index;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nTem certeza que deseja alterar este item? (s/n): ";
                cin >> confirmacao;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (tolower(confirmacao) == 's') {
                    // Uso de tolower() para aceitar tanto 's' quanto 'S' como confirmação
                    cout << "Digite o novo nome do item: ";
                    getline(cin, novoNome);
                    cout << "Digite a nova quantidade do item: ";
                    getline(cin, novaQuantidade);
                    cout << "Digite o novo preco do item: ";
                    getline(cin, novoPreco);
                    cout << "Digite o novo peso do item: ";
                    getline(cin, novoPeso);
                    secao.alterarItem(index - 1, novoNome, novaQuantidade, novoPreco, novoPeso);
                } else {
                    cout << "\nOperacao de alteracao cancelada.\n" << endl;
                }
                break;
            }
            case 4:
                limparConsole();
                secao.exibirItens();
                cout << "\nPressione Enter para voltar...\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            case 5: {
                limparConsole();
                secao.exibirItens();

                double valorProduto, quantidade;
                cout << "\nCalculadora de Precos\n";
                cout << "--------------------\n";
                cout << "Digite o valor do produto (em reais): R$ ";
                cin >> valorProduto;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nValor invalido. Por favor, digite um numero valido.\n";
                    break;
                }

                cout << "Digite a quantidade desejada: ";
                cin >> quantidade;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nQuantidade invalida. Por favor, digite um numero valido.\n";
                    break;
                }

                double total = valorProduto * quantidade;
                cout << fixed << setprecision(2);
                cout << "\nResumo da compra:";
                cout << "\n----------------";
                cout << "\nValor unitario: R$ " << valorProduto;
                cout << "\nQuantidade: " << quantidade;
                cout << "\nValor total: R$ " << total;

                cout << "\n\nPressione Enter para continuar...\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
            case 6:
                limparConsole();
                cout << "\nVoltando ao menu principal...\n" << endl;
                break;
            default:
                cout << "\nOpcao invalida. Por favor, escolha uma opcao valida.\n" << endl;
        }
    } while (choice != 6);
}

void View::start() {
    int choice;
    Secao frutas("Frutas");
    Secao vegetais("Vegetais");
    Secao legumes("Legumes");

    while (true) {
        limparConsole();
        cout << "Bem-vindo ao Horti Fruti!" << endl;
        cout << "\nEscolha uma secao para visualizar:\n" << endl;
        cout << "1. Frutas" << endl;
        cout << "2. Vegetais" << endl;
        cout << "3. Legumes" << endl;
        cout << "4. Sair" << endl;
        cout << "\nDigite o numero da sua escolha:\n";
        cin >> choice;

        if (cin.fail()) {
            cin.ignore();
            cout << "\nOpcao invalida. Por favor, insira um numero.\n" << endl;
            continue;
        }

        switch (choice) {
            case 1:
                menuSecao(frutas);
                break;
            case 2:
                menuSecao(vegetais);
                break;
            case 3:
                menuSecao(legumes);
                break;
            case 4:
                limparConsole();
                cout << "\nObrigado por utilizar nosso sistema!\n" << endl;
                exit(0);
                break;
            default:
                cout << "\nOpcao invalida. Por favor, escolha uma opcao valida.\n" << endl;
        }
    }
}