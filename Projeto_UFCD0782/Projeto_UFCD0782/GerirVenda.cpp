#include "GerirVenda.h"
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <ctime>

const string NOME_FICHEIRO = "venda.csv";
const int MAX_ID_VENDA = 100;

void GerirVenda::updateClasseVenda(){
	ifstream arquivo(NOME_FICHEIRO);
	if (!arquivo.is_open()) {
		cout << "Arquivo de vendas não encontrado." << endl;
		contador = 0;
		venda = nullptr;
		return;
	}
	string linha;
	contador = 0;
	// Conta quantas linhas tem o CSV
	while (getline(arquivo, linha)) {
		contador++;
	}
	arquivo.close();
	venda = new Venda[contador];
	arquivo.open(NOME_FICHEIRO);
	contador = 0;
	while (getline(arquivo, linha)) {
		stringstream ss(linha);
		string idClienteCSV, idProdutoCSV, quantidadeCSV, idVendaCSV, dataCSV, totalCSV, valorEntregueCSV, trocoCSV, sorteioCSV;
		getline(ss, idClienteCSV, ';');
		getline(ss, idProdutoCSV, ';');
		getline(ss, quantidadeCSV, ';');
		getline(ss, idVendaCSV, ';');
		getline(ss, dataCSV, ';');
		getline(ss, totalCSV, ';');
		getline(ss, valorEntregueCSV, ';');
		getline(ss, trocoCSV, ';');
		getline(ss, sorteioCSV, ';');

		int idCliente = stoi(idClienteCSV);
		int idProduto = stoi(idProdutoCSV);
		int quantidade = stoi(quantidadeCSV);
		int idVenda = stoi(idVendaCSV);
		double total = stod(totalCSV);
		double valorEntregue = stod(valorEntregueCSV);
		double troco = stod(trocoCSV);
		bool sorteio = stoi(sorteioCSV);
		venda[contador] = Venda(idCliente, idProduto, quantidade, idVenda, dataCSV, total, valorEntregue, troco, sorteio);
		contador++;
	}
	arquivo.close();
}

string GerirVenda::obterHora() {
	time_t agora = time(0);
	struct tm dataHora;
	localtime_s(&dataHora, &agora);

	char data[20];
	strftime(data, 20, "%d/%m/%Y %H:%M:%S", &dataHora);

	return string(data);
}

bool GerirVenda::gerarSorteio(int idCompra){
	srand(time(NULL));
	int numeroSorteio = rand() % 100 + 1;
	if (numeroSorteio == idCompra) {
		cout << "\n\n Parabens! A sua compra foi sorteada.\n"
			<< " Nao precisa pagar a conta.\n\n";
			return true;
	}
	else {
		cout << "\n\n Infelizmente, a sua compra nao foi sorteada.\n"
			<< " Lembre-se de pagar a conta.\n\n";
		return false;
	}
}

GerirVenda::GerirVenda(){
	updateClasseVenda(); // Funçao usada para preencher a classe venda quando o programa for atulizado
}

void GerirVenda::imprimirTalao(int idcompra) {
	double totalSemIVA = 0,totalComIVA = 0,valorEntregue = 0,valorTroco = 0;
	int numeroLinha = 1;

	cout << setw(40) << right << "Talao da Fatura - Numero: " << idcompra << endl;
	cout << setw(40) << right << "+--------------------------------------------------------------+" << endl;
	cout << setw(4) << right << "| No |" << right << "Nome Produto" << setw(5) << right << "| Quantidade |"
		<< setw(12) << right << "Preco s/IVA |" << setw(5) << right << "IVA |" << setw(13) << right << "Total C/IVA  |" << endl;
	cout << setw(40) << right << "+--------------------------------------------------------------+" << endl;

	for (int i = 0; i < contador; i++) {
		if (venda[i].getIdVenda() == idcompra) {
			if (venda[i].getIdProduto() != -1) {
				// Imprime as informações da linha do talão
				cout << "|" << numeroLinha << " | " << produtos.obterNomeProduto(venda[i].getIdProduto())
					<< " | " << venda[i].getQuantidade() << " | " << produtos.obterPrecoSemIva(venda[i].getIdProduto())
					<< " | " << produtos.obterIvaProduto(venda[i].getIdProduto()) << "% | " << venda[i].getTotal() << " |" << endl;

				// Calculo de total
				totalSemIVA += venda[i].getQuantidade() * produtos.obterPrecoSemIva(venda[i].getIdProduto());
				totalComIVA += venda[i].getTotal();
				numeroLinha++;
			}
			else {
				valorEntregue = venda[i].getValorEntrege();
				valorTroco = venda[i].getTroco();
			}
		}
	}

	cout << setw(40) << right << "+--------------------------------------------------------------+" << endl;
	cout << setw(40) << "Total s/IVA:" << setw(14) << totalSemIVA << setw(10) << "|" << endl;
	cout << setw(40) << "Total c/IVA:" << setw(14) << totalComIVA << setw(10) << "|" << endl;
	cout << setw(40) << "Valor Entrege:" << setw(14) << valorEntregue << setw(10) << "|" << endl;
	cout << setw(40) << "Troco:" << setw(14) << valorTroco << setw(10) << "|" << endl;
	cout << setw(40) << right << "+--------------------------------------------------------------+" << endl;
}

void GerirVenda::adicionaVenda() {

	int idCliente, idProduto, quantidade = 0;
	string dataCSV = obterHora();
	double totalQuantia = 0, totalCompra = 0, quantiaEntregue = 0, troco = 0;
	int ultimoIdVenda = 0;  // Variável para armazenar o último ID de venda
	bool resultadoSorteio = false;
	// Verifica se idCliente é igual ao id  de algum cliente guardado na classe
	do {
		cout << "ID Cliente: ";
		cin >> idCliente;
	} while (!clientes.verificaCliente(idCliente));

	// Abre o arquivo em modo leitura para encontrar o último ID de venda
	ifstream arquivoLeitura(NOME_FICHEIRO);

	if (arquivoLeitura.is_open()) {
		// Encontrar o último ID de venda
		string linha;
		while (getline(arquivoLeitura, linha)) {
			stringstream ss(linha);
			string idClienteCSV, idProdutoCSV, quantidadeCSV, idVendaCSV, dataCSV, totalCSV, valorEntregueCSV, trocoCSV, sorteioCSV;

			getline(ss, idClienteCSV, ';');
			getline(ss, idProdutoCSV, ';');
			getline(ss, quantidadeCSV, ';');
			getline(ss, idVendaCSV, ';');
			getline(ss, dataCSV, ';');
			getline(ss, totalCSV, ';');
			getline(ss, valorEntregueCSV, ';');
			getline(ss, trocoCSV, ';');
			getline(ss, sorteioCSV, ';');

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
	resultadoSorteio = gerarSorteio(ultimoIdVenda);

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

			while (quantidade > produtos.obterQuantidadeDisponivel(idProduto)) {
				cout << "Quantidade Indisponivel. Tente Novamente!!\n";
				cout << "Quantidade: ";
				cin >> quantidade;
			}
			if (quantidade > 0){ 
				produtos.dimunirQuantidadeStock(idProduto, quantidade);
				totalQuantia = (produtos.obterPrecoProduto(idProduto) * quantidade);
				totalCompra = totalCompra + totalQuantia;
				// Adiciona o produto à venda no arquivo CSV
				arquivo << idCliente << ";" << idProduto << ";" << quantidade << ";" << ultimoIdVenda + 1 << ";"
					<< dataCSV << ";" << totalQuantia << ";" << quantiaEntregue << ";" << troco << ";" << resultadoSorteio << endl;
			}
			contador++; // Incrementa o contador
		}
	} while (idProduto != 0);
	
	if (!resultadoSorteio){
		cout << "Total da Compra: " << totalCompra << "\n";
		do {
			cout << "Valor entregue: ";
			cin >> quantiaEntregue;

		} while (quantiaEntregue <= totalCompra);

		troco = quantiaEntregue - totalCompra;
		cout << "Troco: " << troco << "\n";
		idProduto = -1;
		arquivo << idCliente << ";" << idProduto << ";" << quantidade << ";" << ultimoIdVenda + 1 << ";"
			<< dataCSV << ";" << totalCompra << ";" << quantiaEntregue << ";" << troco << ";" << resultadoSorteio << endl;
	}
	arquivo.close();
	// Incrementa o último ID de venda no final da compra
	ultimoIdVenda++;
	system("cls");
	updateClasseVenda();
	imprimirTalao(ultimoIdVenda);
}