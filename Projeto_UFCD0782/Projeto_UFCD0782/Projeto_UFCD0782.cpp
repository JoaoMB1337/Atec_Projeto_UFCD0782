#include <iostream>
#include <string>
#include "GerirProduto.h"

int main() {
    GerirProduto gerenciador;
    int opcao;

    do {
        std::cout << "Menu de Gerenciamento de Produtos:" << std::endl;
        std::cout << "1. Adicionar Produto" << std::endl;
        std::cout << "2. Remover Produto" << std::endl;
        std::cout << "3. Modificar Produto" << std::endl;
        std::cout << "4. Mostrar Produtos" << std::endl;
        std::cout << "5. Sair" << std::endl;
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
        case 1: {
            int id, stock;
            double precoCusto, iva;
            std::string nome;

            std::cout << "Informe o ID do produto: ";
            std::cin >> id;
            std::cin.ignore(); // Limpar o buffer de entrada
            std::cout << "Informe o nome do produto: ";
            std::getline(std::cin, nome);
            std::cout << "Informe o estoque do produto: ";
            std::cin >> stock;
            std::cout << "Informe o preço de custo do produto: ";
            std::cin >> precoCusto;
            std::cout << "Informe o IVA do produto: ";
            std::cin >> iva;

            gerenciador.adicionarProduto(id, nome, stock, precoCusto, iva);
            break;
        }

        case 2: {
            std::string nome;
            std::cout << "Informe o nome do produto a ser removido: ";
            std::cin.ignore();
            std::getline(std::cin, nome);
            gerenciador.removerProduto(nome);
            break;
        }

        case 3: {
            std::string nome;
            int novoStock;
            double novoPrecoCusto, novoIva;

            std::cout << "Informe o nome do produto a ser modificado: ";
            std::cin.ignore();
            std::getline(std::cin, nome);
            std::cout << "Informe o novo estoque: ";
            std::cin >> novoStock;
            std::cout << "Informe o novo preço de custo: ";
            std::cin >> novoPrecoCusto;
            std::cout << "Informe o novo IVA: ";
            std::cin >> novoIva;

            gerenciador.modificarProduto(nome, novoStock, novoPrecoCusto, novoIva);
            break;
        }

        case 4:
            gerenciador.mostrarProdutos();
            break;

        case 5:
            std::cout << "Saindo do programa." << std::endl;
            break;

        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;
            break;
        }

    } while (opcao != 5);

    return 0;
}
