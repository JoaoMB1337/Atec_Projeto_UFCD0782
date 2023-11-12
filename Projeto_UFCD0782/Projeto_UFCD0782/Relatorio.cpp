#include "Relatorio.h"
#include "Produto.h"
#include "Venda.h"
#include "GerirProduto.h"
#include "GerirVenda.h"
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>

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

    // Libertar memória alocada
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

    // Libertar memória alocada
    delete[] nomes;
    delete[] quantidades;
}
