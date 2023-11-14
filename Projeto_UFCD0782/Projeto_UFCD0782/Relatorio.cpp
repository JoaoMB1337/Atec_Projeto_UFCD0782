#include "Relatorio.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <sstream>
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
        cout << "erro ao abrir o arquivo vendas.csv." << endl;
        return;
    }

    string produtomaisvendido = "";
    string produtomenosvendido = "";
    string clientemaisativo = "";
    int quantidademaisvendido = 0;
    int quantidademenosvendido = INT_MAX;
    int idProdutoMaiorLucro = gestorVenda.produtoComMaiorLucro();
    string getNomePorId = gestorProduto.obterNomeProduto(idProdutoMaiorLucro);
    double maiorLucro = gestorProduto.obterPrecoProduto(idProdutoMaiorLucro);

    map<string, int> vendasporproduto;
    map<string, int> vendasporcliente;
    map<string , int> lucroporproduto;

    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string idclientecsv, idprodutocsv, quantidadecsv;
        getline(ss, idclientecsv, ';');
        getline(ss, idprodutocsv, ';');
        getline(ss, quantidadecsv, ';');

        int quantidade = stoi(quantidadecsv);

        vendasporproduto[idprodutocsv] += quantidade;

        if (idprodutocsv != "-1") {
            if (vendasporproduto[idprodutocsv] > quantidademaisvendido) {
                quantidademaisvendido = vendasporproduto[idprodutocsv];
                produtomaisvendido = idprodutocsv;
            }
            if (vendasporproduto[idprodutocsv] < quantidademenosvendido) {
                quantidademenosvendido = vendasporproduto[idprodutocsv];
                produtomenosvendido = idprodutocsv;
            }
        }

        // vendas totais por cliente!!!
        vendasporcliente[idclientecsv] += quantidade;

        if (vendasporcliente[idclientecsv] > vendasporcliente[clientemaisativo]) {
            clientemaisativo = idclientecsv;
        }

        // lucro por produto
        lucroporproduto[idprodutocsv] += gestorProduto.obterPrecoProduto(stoi(idprodutocsv)) * quantidade;

        if (lucroporproduto[idprodutocsv] > maiorLucro) {
			maiorLucro = lucroporproduto[idprodutocsv];
			getNomePorId = gestorProduto.obterNomeProduto(stoi(idprodutocsv));
		}
    }
    arquivo.close();

    cout << "+----------------------------------+\n";
    cout << "|      Produto mais e menos vendido|\n";
    cout << "+----------------------------------+\n";
    cout << "| Produto mais vendido: " <<setw(30) << left << produtomaisvendido << "| Quantidade: " << setw(10) <<right << quantidademaisvendido << "|\n";
    cout << "| Produto menos vendido: " << setw(28) <<left << produtomenosvendido << "| Quantidade: " << setw(10) << right << quantidademenosvendido << "|\n";
    cout << "| Produto com maior lucro: " << setw(27) << left << getNomePorId << "| Lucro: " << setw(14) << right << maiorLucro << "|\n";
    cout << "| Cliente mais ativo: " << setw(31) << left << clientemaisativo << "| Quantidade: " <<setw(10) <<right << vendasporcliente[clientemaisativo] << "|\n";
    cout << "+----------------------------------+\n";

}