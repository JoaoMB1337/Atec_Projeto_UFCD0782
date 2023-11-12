#include "Relatorio.h"
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <map>

Relatorio::Relatorio(){

}

void Relatorio::imprimirNomesQuantidades() {
    string* nomes;
    int* quantidades;
    int tamanho;

    gestorProduto.obterNomesQuantidades(nomes, quantidades, tamanho);

    cout << "+----------------------------------+\n";
    cout << "| Nomes e Quantidades dos Produtos |\n";
    cout << "+----------------------------------+\n";

    for (int i = 0; i < tamanho; i++) {
        cout << "| Nome: " << nomes[i] << ", Quantidade: " << quantidades[i] << "           |\n";
    }
    cout << "+----------------------------------+\n";

    // Libertar memória alocada
    delete[] nomes;
    delete[] quantidades;
}

void Relatorio::imprimeSemStock() {
    string* nomes;
    int* quantidades;
    int tamanho;

    gestorProduto.obterNomesQuantidades(nomes, quantidades, tamanho);

	cout << "+----------------------------------+\n";
	cout << "|    Lista Produtos sem Stock      |\n";
	cout << "+----------------------------------+\n";
    for (int i = 0; i < tamanho; i++) {
        if (quantidades[i] == 0) {
			cout << "| Nome: " << nomes[i] << ", Quantidade: " << quantidades[i] << "           |\n";
		}
	}
	cout << "+----------------------------------+\n";

    // Libertar memória alocada
    delete[] nomes;
    delete[] quantidades;
}

void Relatorio::imprimeMaisMenosVendido() {

    ifstream arquivo("venda.csv");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo vendas.csv." << endl;
        return;
    }

    string produtoMaisVendido = "";
    string produtoMenosVendido = "";
    int quantidadeMaisVendido = 0;
    int quantidadeMenosVendido = numeric_limits<int>::max();  // Valor máximo de um inteiro

    map<string, int> vendasPorProduto;  // Mapa que associa o nome do produto à quantidade total vendida

    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string idVenda, nomeProduto, quantidadeProduto;
        getline(ss, idVenda, ';');  // ID da venda
        getline(ss, nomeProduto, ';');
        getline(ss, quantidadeProduto, ';');

        int quantidade = stoi(quantidadeProduto);

        // Atualizar a quantidade total vendida para cada produto
        vendasPorProduto[nomeProduto] += quantidade; // Se o produto ainda não existir no mapa, será criado com o valor 0

        // Atualizar o produto mais vendido
        if (vendasPorProduto[nomeProduto] > quantidadeMaisVendido) {
            quantidadeMaisVendido = vendasPorProduto[nomeProduto];
            produtoMaisVendido = nomeProduto;
        }

        // Atualizar o produto menos vendido
        if (vendasPorProduto[nomeProduto] < quantidadeMenosVendido) {
            quantidadeMenosVendido = vendasPorProduto[nomeProduto];
            produtoMenosVendido = nomeProduto;
        }

    }
    arquivo.close();
    
    cout << "+----------------------------------+\n";
    cout << "|    Produto mais e menos vendido  |\n";
    cout << "+----------------------------------+\n";
    cout << "| Produto mais vendido: " << produtoMaisVendido << ", Quantidade: " << quantidadeMaisVendido << "           |\n";
    cout << "| Produto menos vendido: " << produtoMenosVendido << ", Quantidade: " << quantidadeMenosVendido << "           |\n";
    cout << "+----------------------------------+\n";
}