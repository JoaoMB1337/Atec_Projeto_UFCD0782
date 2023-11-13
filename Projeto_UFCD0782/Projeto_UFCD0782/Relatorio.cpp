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
    string clienteMaisAtivo = "";
    int quantidadeMaisVendido = 0;
    int quantidadeMenosVendido = numeric_limits<int>::max();

    map<string, int> vendasPorProduto;
    map<string, int> vendasPorCliente;

    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string idClienteCSV, idProdutoCSV, quantidadeCSV;
        getline(ss, idClienteCSV, ';');
        getline(ss, idProdutoCSV, ';');
        getline(ss, quantidadeCSV, ';');

        int quantidade = stoi(quantidadeCSV);

        vendasPorProduto[idProdutoCSV] += quantidade;

        if (idProdutoCSV != "-1") {
            // Encontrando o produto mais e menos vendido
            if (vendasPorProduto[idProdutoCSV] > quantidadeMaisVendido) {
                quantidadeMaisVendido = vendasPorProduto[idProdutoCSV];
                produtoMaisVendido = idProdutoCSV;
            }
            // Encontrando o produto menos vendido
            if (vendasPorProduto[idProdutoCSV] < quantidadeMenosVendido) {
                quantidadeMenosVendido = vendasPorProduto[idProdutoCSV];
                produtoMenosVendido = idProdutoCSV;
            }
        }
        // Encontrando o cliente mais ativo
        vendasPorCliente[idClienteCSV] += quantidade;

        if (vendasPorCliente[idClienteCSV] > quantidadeMaisVendido) {
            quantidadeMaisVendido = vendasPorCliente[idClienteCSV];
            clienteMaisAtivo = idClienteCSV;
        }
    }
    arquivo.close();

    cout << "+----------------------------------+\n";
    cout << "|    Produto mais e menos vendido  |\n";
    cout << "+----------------------------------+\n";
    cout << "| Produto mais vendido: " << produtoMaisVendido << ", Quantidade: " << quantidadeMaisVendido << "           |\n";
    cout << "| Produto menos vendido: " << produtoMenosVendido << ", Quantidade: " << quantidadeMenosVendido << "           |\n";
    cout << "| Cliente mais ativo: " << clienteMaisAtivo << ", Quantidade: " << quantidadeMaisVendido << "           |\n";
    cout << "+----------------------------------+\n";
}
