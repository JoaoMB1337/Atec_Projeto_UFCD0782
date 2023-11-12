#include "GerirVenda.h"
#include "GerirProduto.h"
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <ctime>

string GerirVenda::obterHora(){
	time_t agora = time(0);
	struct tm dataHora;
	localtime_s(&dataHora, &agora);

	char data[20];
	strftime(data, 20, "%d/%m/%Y %H:%M:%S", &dataHora);

	return string(data);
}

void GerirVenda::guardaInformacoes()
{
	ofstream arquivo("venda.csv", ios::out);

	if (!arquivo.is_open()) {
		cout << "Erro ao abrir o arquivo cliente.csv." << endl;
		return;
	}

	for (int i = 0; i < contador; i++) {
		arquivo << venda[i].getIdCliente() << ";" << venda[i].getIdProduto() << ";" << venda[i].getQuantidade() << ";" << venda[i].getIdVenda() << ";" << venda[i].getData() << ";" << venda[i].getTotal() << endl;
	}
	arquivo.close();
}

GerirVenda::GerirVenda()
{
	ifstream arquivo("venda.csv");
	if (!arquivo.is_open()) {
		cout << "Arquivo de vendas não encontrado." << endl;
		contador = 0;
		venda = nullptr;
		return;
	}
	string linha;
	contador = 0;
	// Ler quantas linhas tem o csv
	while (getline(arquivo, linha)) {
		contador++;
	}
	arquivo.close();
	venda = new Venda[contador];
	arquivo.open("venda.csv");
	contador = 0;
	while (getline(arquivo, linha)) {
		stringstream ss(linha);
		string idClienteCSV, idProdutoCSV, quantidadeCSV, idVendaCSV, dataCSV, totalCSV;
		getline(ss, idClienteCSV, ';');
		getline(ss, idProdutoCSV, ';');
		getline(ss, quantidadeCSV, ';');
		getline(ss, idVendaCSV, ';');
		getline(ss, dataCSV, ';');
		getline(ss, totalCSV, ';');

		int idCliente = stoi(idClienteCSV);
		int idProduto = stoi(idProdutoCSV);
		int quantidade = stoi(quantidadeCSV);
		int idVenda = stoi(idVendaCSV);
		double total = stod(totalCSV);
		venda[contador] = Venda(idCliente, idProduto, quantidade, idVenda, dataCSV, total);
		contador++;
	}
	arquivo.close();
}

const int MAX_VENDA = 100;

void GerirVenda::imprimirTalao(int idcompra) {
	ifstream arquivoLeitura("venda.csv");

	if (!arquivoLeitura.is_open()) {
		cout << "Erro ao abrir o arquivo venda.csv." << endl;
		return;
	}

	double totalSemIVA = 0;
	double totalComIVA = 0;
	int numeroLinha = 1;

	// Imprime o cabeçalho do talão
	cout << "Talao da Fatura - Numero: " << idcompra << endl;
	//cout << "Cliente: " << numeroCliente << endl;
	cout << "+------------------------------------+" << endl;
	cout << "| No | Nome Produto | Quantidade | Preco s/IVA | IVA | Total C/IVA |" << endl;
	cout << "+------------------------------------+" << endl;

	// Lê o arquivo e imprime as linhas do talão
	string linha;
	while (getline(arquivoLeitura, linha)) {
		stringstream ss(linha);
		string idClienteCSV, idProdutoCSV, quantidadeCSV, idVendaCSV, dataCSV, totalCSV;

		getline(ss, idClienteCSV, ';');
		getline(ss, idProdutoCSV, ';');
		getline(ss, quantidadeCSV, ';');
		getline(ss, idVendaCSV, ';');
		getline(ss, dataCSV, ';');
		getline(ss, totalCSV, ';');

		int idCliente = stoi(idClienteCSV);
		int idProduto = stoi(idProdutoCSV);
		int quantidade = stoi(quantidadeCSV);
		int idVenda = stoi(idVendaCSV);
		double total = stod(totalCSV);
		if(idcompra == idVenda){
		// Imprime as informações da linha do talão
		cout << "|"  << numeroLinha << " | " << produtos.obterNomeProduto(idProduto) 
			<< " | "  << quantidade << " | "  << produtos.obterPrecoSemIva(idProduto)
			<< " | "  << produtos.obterIvaProduto(idProduto) << "% | "  << total << " |" << endl;

		// Atualiza os totais
		totalSemIVA += quantidade * produtos.obterPrecoSemIva(idProduto);
		totalComIVA += total;
		numeroLinha++;
		}
	}

	// Imprime os totais do talão
	cout << "+------------------------------------+" << endl;
	cout << "| Total s/IVA: " << totalSemIVA << " |" << endl;
	cout << "| Total c/IVA: " << totalComIVA << " |" << endl;
	cout << "+------------------------------------+" << endl;
	// Fecha o arquivo
	arquivoLeitura.close();
}

void GerirVenda::adicionaVenda() {
	
	int idCliente, idProduto, quantidade=0;
	string dataCSV = obterHora();
	double total = 0;
	int ultimoIdVenda = 0;  // Variável para armazenar o último ID de venda

	// Verifica se idCliente é igual ao id  de algum cliente guardado na classe
	do {
		cout << "ID Cliente: ";
		cin >> idCliente;
	} while (!clientes.verificaCliente(idCliente));

	// Abre o arquivo em modo leitura para encontrar o último ID de venda
	ifstream arquivoLeitura("venda.csv");

	if (arquivoLeitura.is_open()) {
		// Encontrar o último ID de venda
		string linha;
		while (getline(arquivoLeitura, linha)) {
			stringstream ss(linha);
			string idClienteCSV, idProdutoCSV, quantidadeCSV, idVendaCSV, dataCSV, totalCSV;
			getline(ss, idClienteCSV, ';');
			getline(ss, idProdutoCSV, ';');
			getline(ss, quantidadeCSV, ';');
			getline(ss, idVendaCSV, ';');
			getline(ss, dataCSV, ';');
			getline(ss, totalCSV, ';');

			int idVenda = stoi(idVendaCSV);
			if (idVenda > ultimoIdVenda) {
				ultimoIdVenda = idVenda;
			}
		}
		// Fecha o arquivo de leitura
		arquivoLeitura.close();
	}
	// Abre o arquivo em modo append (adiciona ao final do arquivo)
	ofstream arquivo("venda.csv", ios::app);

	if (!arquivo.is_open()) {
		cout << "Erro ao abrir o arquivo venda.csv." << endl;
		return;
	}

	// Loop para adicionar produtos à venda
	do {
		cout << "ID Produto (insira 0 para encerrar a compra): ";
		cin >> idProduto;

		if (idProduto != 0) {
			// Verifica se idProduto é igual ao id do produto Produtos.csv
			while (!produtos.verificaProduto(idProduto)) {
				cout << "ID Produto invalido. Tente novamente: ";
				cin >> idProduto;
			}

			cout << "Quantidade: ";
			cin >> quantidade;

			while (quantidade > produtos.obterQuantidadeDisponivel(idProduto)){
				cout << "Quantidade Indisponivel. Tente Novamente!!\n";
				cout << "Quantidade: ";
				cin >> quantidade;
			}
			produtos.dimunirQuantidadeStock(idProduto, quantidade);
			total =  (produtos.obterPrecoProduto(idProduto) * quantidade);

			// Adiciona o produto à venda no arquivo CSV
			arquivo << idCliente << ";" << idProduto << ";" << quantidade << ";" << ultimoIdVenda + 1 << ";" << dataCSV << ";" << total << endl;
			// Incrementa o contador
			contador++;
		}
	} while (idProduto != 0);
	// Incrementa o último ID de venda no final da compra
	ultimoIdVenda++;
	imprimirTalao(ultimoIdVenda);
	arquivo.close();
}

void GerirVenda::imprimeVendaPorProduto(GerirProduto& gerenciadorProdutos, GerirVenda& gerenciadorVendas) {
	cout << "Insira o nome do produto: ";
	string nomeProduto;
	cin >> nomeProduto;

	cout << "+--------------------------------------+\n";
	cout << "|    Relatorio de Vendas por Produto   |\n";
	cout << "+--------------------------------------+\n";

	bool encontrou = false;

	for (int i = 0; i < contador; ++i) {
		string nomeVendaProduto = gerenciadorProdutos.obterNomeProduto(venda[i].getIdProduto());
		if (nomeVendaProduto == nomeProduto) {
			venda[i].mostrarVendas();
			encontrou = true;
		}
	}

	if (!encontrou) {
		cout << "Nenhuma venda encontrada para o produto: " << nomeProduto << endl;
	}
}
