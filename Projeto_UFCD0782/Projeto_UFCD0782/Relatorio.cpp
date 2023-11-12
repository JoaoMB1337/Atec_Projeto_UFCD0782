#include "Relatorio.h"
#include "Produto.h"
#include "Venda.h"
#include "GerirProduto.h"
#include "GerirVenda.h"
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <map>

void Relatorio::imprimirNomesQuantidades(GerirProduto& gerenciadorProdutos) {
    string* nomes;
    int* quantidades;
    int tamanho;

    gerenciadorProdutos.obterNomesQuantidades(nomes, quantidades, tamanho);

    cout << "+----------------------------------+\n";
    cout << "| Nomes e Quantidades dos Produtos |\n";
    cout << "+----------------------------------+\n";

    for (int i = 0; i < tamanho; i++) {
        cout << "| Nome: " << nomes[i] << ", Quantidade: " << quantidades[i] << "           |\n";
    }
    cout << "+----------------------------------+\n";

    // Libertar mem�ria alocada
    delete[] nomes;
    delete[] quantidades;
}

void Relatorio::imprimeSemStock(GerirProduto& gerenciadorProdutos) {
    string* nomes;
    int* quantidades;
    int tamanho;

    gerenciadorProdutos.obterNomesQuantidades(nomes, quantidades, tamanho);

	cout << "+----------------------------------+\n";
	cout << "|    Lista Produtos sem Stock      |\n";
	cout << "+----------------------------------+\n";
    for (int i = 0; i < tamanho; i++) {
        if (quantidades[i] == 0) {
			cout << "| Nome: " << nomes[i] << ", Quantidade: " << quantidades[i] << "           |\n";
		}
	}
	cout << "+----------------------------------+\n";

    // Libertar mem�ria alocada
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
    int quantidadeMenosVendido = numeric_limits<int>::max();  // Valor m�ximo de um inteiro

    map<string, int> vendasPorProduto;  // Mapa que associa o nome do produto � quantidade total vendida

    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string idVenda, nomeProduto, quantidadeProduto;
        getline(ss, idVenda, ';');  // ID da venda
        getline(ss, nomeProduto, ';');
        getline(ss, quantidadeProduto, ';');

        int quantidade = stoi(quantidadeProduto);

        // Atualizar a quantidade total vendida para cada produto
        vendasPorProduto[nomeProduto] += quantidade; // Se o produto ainda n�o existir no mapa, ser� criado com o valor 0

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
