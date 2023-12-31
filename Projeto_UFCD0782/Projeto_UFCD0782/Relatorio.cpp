#include "Relatorio.h"


Relatorio::Relatorio(){

}

void Relatorio::updatesClasses(){
    gestorCliente.updateClasseCliente();
    gestorProduto.updateClasseProduto();
    gestorVenda.updatingClasses();
}


//com stock
void Relatorio::imprimirNomesQuantidades() {
    updatesClasses();
    string* nomes;
    int* quantidades;
    int tamanho;

    gestorProduto.obterNomesQuantidades(nomes, quantidades, tamanho);


    cout << "+----------------------------------+\n";
    cout << "| Nomes e Quantidades dos Produtos |\n";
    cout << "+----------------------------------+\n";
    cout << "| Nome          | Quantidade       |\n";
    cout << "+----------------------------------+\n";
    for (int i = 0; i < tamanho; i++) {
        if (quantidades[i] > 0) {
            cout << "| " << setw(14) << left << nomes[i] << "| " << setw(17) << left << quantidades[i] << "|\n";
        }
    }
    cout << "+----------------------------------+\n";

    // Libertar mem�ria alocada
    delete[] nomes;
    delete[] quantidades;
}

//sem stock
void Relatorio::imprimeSemStock() {
    updatesClasses();
    string* nomes;
    int* quantidades;
    int tamanho;

    gestorProduto.obterNomesQuantidades(nomes, quantidades, tamanho);

	cout << "+----------------------------------+\n";
	cout << "| Nomes e Quantidades dos Produtos |\n";
	cout << "+----------------------------------+\n";
	cout << "| Nome          | Quantidade       |\n";
	cout << "+----------------------------------+\n";
	for (int i = 0; i < tamanho; i++) {
        if (quantidades[i] <= 0){
            cout << "| " << setw(14) << left << nomes[i] << "| " << setw(17) << left << quantidades[i] << "|\n";
        }
	}
	cout << "+----------------------------------+\n";

    // Libertar mem�ria alocada
    delete[] nomes;
    delete[] quantidades;
}

//relatorio total
void Relatorio::imprimeMaisMenosVendido() {
    updatesClasses();
    ifstream arquivo("venda.csv");
    if (!arquivo.is_open()) {
        cout << "erro ao abrir o arquivo vendas.csv. \n" ;
        return;
    }

    string produtomaisvendido = "";
    string produtomenosvendido = "";
    string clientemaisativo = "";
    int idCliente = 0;
    int quantidademaisvendido = 0;
    int quantidademenosvendido = INT_MAX;
    int idProdutoMaiorLucro = gestorVenda.produtoComMaiorLucro();
    string getNomePorId = gestorProduto.obterNomeProduto(idProdutoMaiorLucro);
    double maiorLucro = gestorProduto.obterPrecoProduto(idProdutoMaiorLucro);
    string getNomeCliente = gestorCliente.obterNomeCliente(idCliente);
    int maiorQuantidadeVendas = 0;

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
                produtomaisvendido = gestorProduto.obterNomeProduto(stoi(idprodutocsv));
            }

            if (vendasporproduto[idprodutocsv] < quantidademenosvendido) {
                quantidademenosvendido = vendasporproduto[idprodutocsv];
                produtomenosvendido = gestorProduto.obterNomeProduto(stoi(idprodutocsv));
            }
            // vendas totais por cliente!!!
            vendasporcliente[idclientecsv] += quantidade;

            if (vendasporcliente[idclientecsv] > vendasporcliente[clientemaisativo]) {
                clientemaisativo = idclientecsv;
                clientemaisativo = gestorCliente.obterNomeCliente(stoi(idclientecsv));
                maiorQuantidadeVendas = vendasporcliente[idclientecsv];
            }

            // lucro por produto
            lucroporproduto[idprodutocsv] += gestorProduto.obterPrecoProduto(stoi(idprodutocsv)) * quantidade;

            if (lucroporproduto[idprodutocsv] > maiorLucro) {
                maiorLucro = lucroporproduto[idprodutocsv];
                getNomePorId = gestorProduto.obterNomeProduto(stoi(idprodutocsv));
            }
        }
    }
    arquivo.close();


    cout << "+--------------------------------------+\n";
    cout << "|      Relatorio Total                 |\n";
    cout << "+--------------------------------------+\n";
    cout << "| Produto mais vendido: " <<setw(30) << left << produtomaisvendido <<endl<< "| Quantidade: " << quantidademaisvendido << "\n";
    cout << "| \n";
    cout << "| Produto menos vendido: " << setw(28) << left << produtomenosvendido << endl << "| Quantidade: " << quantidademenosvendido << "\n";
    cout << "| \n";
    cout << "| Produto com maior lucro: " << setw(27) << left << getNomePorId <<endl<< "| Lucro: " << maiorLucro << " Euros \n";
    cout << "| \n";
    cout << "| Cliente mais ativo: " << setw(31) << left << clientemaisativo <<endl<< "| Numero Compras efetuadas : " << maiorQuantidadeVendas << "\n";
    cout << "+--------------------------------------+\n";

}