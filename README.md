# Projeto hortifruti (primeiro semestre em ADS Unip-2024)

# Descrição
Este programa foi desenvolvido em C++ em parceria com um colega, com o objetivo de criar um sistema de gerenciamento de estoque simples e funcional executado via console. O projeto foi desenvolvido no Visual Studio Code e utiliza funções organizadas para garantir clareza e modularidade no código.

# Funcionalidades Principais
Ao iniciar a aplicação, o usuário se depara com o Menu Principal, que apresenta as seguintes opções:

1 - Frutas

2 - Vegetais

3 - Legumes

4 - Sair

Cada opção leva o usuário a um submenu correspondente ou encerra o programa.

Menus de Sessão
Cada categoria (Frutas, Vegetais ou Legumes) possui seu próprio menu, com as seguintes funcionalidades:

Adicionar Item: Permite ao usuário cadastrar um novo produto, informando:

Nome

Quantidade

Preço por quilograma

Peso
O programa gera automaticamente um índice exclusivo para cada item, facilitando sua identificação posterior.

Excluir Item: O usuário informa o índice do item a ser excluído. Após confirmação, o item é removido permanentemente da lista.

Alterar Item: O programa exibe todos os itens cadastrados e solicita o índice do item a ser alterado. Após a confirmação, o usuário poderá modificar:

Nome

Quantidade

Preço por quilograma

Peso

Exibir Itens: Lista todos os produtos cadastrados na seção selecionada, permitindo ao usuário visualizar o estoque atual.

Calculadora: Uma ferramenta simples para cálculo de custo total. O usuário insere:

Valor unitário do produto

Quantidade desejada
O programa calcula e exibe o valor total da compra.

Voltar: Retorna ao Menu Principal, permitindo a troca de categoria ou a saída do programa.

# Interface
A interface é baseada em texto e foi projetada para ser direta e intuitiva, sem o uso de gráficos ou elementos visuais complexos. Todas as interações são realizadas via terminal, garantindo portabilidade e fácil execução.

# Objetivo do Projeto
Este projeto tem como objetivo aplicar os conhecimentos de programação modular em C++, utilizando funções para separar responsabilidades e permitir a reutilização de código. Ele também oferece uma introdução prática a estruturas de dados como vetores (ou listas) e manipulação de entrada/saída via console.

# Compilação e Execução
Requisitos
Compilador C++ (como g++, incluído em distribuições do MinGW, GCC ou WSL)

Editor de código como Visual Studio Code

Terminal de comandos (CMD, PowerShell ou Terminal do VS Code)

# Instruções para instalação
g++ -o estoque main.cpp

Esse comando compila o programa e gera um executável chamado estoque.

# Autor

Criado por Enrico Leite e Leonardo Zanchi + terceiros.
