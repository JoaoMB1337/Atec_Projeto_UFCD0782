#include "GerirVenda.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <map>
#include <ctime>

const string NOME_FICHEIRO = "venda.csv";
const int MAX_ID_VENDA = 100;

int GerirVenda::converterStringToInt(string str){
	try {
		int strToInt = stoi(str);
		return strToInt;
	}
	catch (invalid_argument&) {
		return -2;
	}
}

double GerirVenda::converterStringToDouble(string str){
	try {
		double strToDouble = stod(str);
		return strToDouble;
	}
	catch (invalid_argument&) {
		return -2;
	}
}

void GerirVenda::updateClasseVenda(){
	ifstream arquivo(NOME_FICHEIRO);
	if (!arquivo.is_open()) {
		cout << "Arquivo de vendas n�o encontrado." << endl;
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

int GerirVenda::obterUltimoIdVenda(){
	int ultimoIdVenda = 0;
	ifstream arquivoLeitura(NOME_FICHEIRO);

	if (arquivoLeitura.is_open()) {
		// Encontrar o �ltimo ID de venda
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
		arquivoLeitura.close();
	}
	return ultimoIdVenda;
}

int GerirVenda::encontrarClientePorIdVenda(int idcompra){
	for (int i = 0; i < contador; i++) {
		if (venda[i].getIdVenda() == idcompra) {
			 return venda[i].getIdCliente();
			break;
		}
	}
}

bool GerirVenda::encontrarSorteioPorIdVenda(int idcompra){
	for (int i = 0; i < contador; i++) {
		if (venda[i].getIdVenda() == idcompra) {
			if (venda[i].getSorteio()) {
				return true;
			}
		}
	}
	return false;
}

GerirVenda::GerirVenda(){
	updateClasseVenda(); // Fun�ao usada para preencher a classe venda quando o programa for atulizado
}

void GerirVenda::imprimirTalao(int idcompra) {
	int numeroCliente = encontrarClientePorIdVenda(idcompra);
	double totalSemIVA = 0,totalComIVA = 0,valorEntregue = 0,valorTroco = 0;
	int numeroLinha = 1;
	bool sorteioEncontrado = encontrarSorteioPorIdVenda(idcompra);

	cout << setw(40) << right << "Talao da Fatura - Numero: " << idcompra <<"\n";
	cout << setw(40) << right << "+--------------------------------------------------------------+\n";
	cout << setw(40) << right << "Numero Cliente: " << numeroCliente << endl;
	cout << setw(40) << right << "+--------------------------------------------------------------+\n";
	cout << setw(4) << right << "| No |" << right << "Nome Produto" << setw(5) << right << "| Quantidade |"
		<< setw(12) << right << "Preco s/IVA |" << setw(5) << right << "IVA |" << setw(13) << right << "Total C/IVA  |\n";
	cout << setw(40) << right << "+--------------------------------------------------------------+\n";

	for (int i = 0; i < contador; i++) {
		if (venda[i].getIdVenda() == idcompra) {
			if (venda[i].getIdProduto() != -1) {
				// Imprime as informa��es da linha do tal�o
				cout << "|" << numeroLinha << " | " << produtos.obterNomeProduto(venda[i].getIdProduto())
					<< " | " << venda[i].getQuantidade() << " | " << produtos.obterPrecoSemIva(venda[i].getIdProduto())
					<< " | " << produtos.obterIvaProduto(venda[i].getIdProduto()) << "% | " << venda[i].getTotal() << " |\n";

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
	if (!sorteioEncontrado) {
		cout << setw(40) << right << "+--------------------------------------------------------------+\n";
		cout << setw(40) << "Total s/IVA:" << setw(14) << totalSemIVA << setw(10) << "|\n";
		cout << setw(40) << "Total c/IVA:" << setw(14) << totalComIVA << setw(10) << "|\n" ;
		cout << setw(40) << "Valor Entrege:" << setw(14) << valorEntregue << setw(10) << "|\n" ;
		cout << setw(40) << "Troco:" << setw(14) << valorTroco << setw(10) << "|\n";
		cout << setw(40) << right << "+--------------------------------------------------------------+\n" ;
	}
	else {
		cout << setw(40) << right << "+--------------------------------------------------------------+\n";
		cout << setw(40) << "Esta venda foi sorteada!!\n";
		cout << setw(40) << right << "+--------------------------------------------------------------+\n";
	}
}

void GerirVenda::adicionaVenda() {
	string IdClienteString,idProdutoString,quantidadeString, quantiaEntregueString;
	int idCliente, idProduto, quantidade = 0;
	string dataCSV = obterHora();
	double totalQuantia = 0, totalCompra = 0, quantiaEntregue = 0, troco = 0;
	int ultimoIdVenda = obterUltimoIdVenda();
	bool resultadoSorteio = false;

	if (ultimoIdVenda >= MAX_ID_VENDA) {
        cout << "Limite de vendas atingido. O conteudo do arquivo sera apagado.\n";
        ofstream arquivo(NOME_FICHEIRO, ios::trunc);  // 'trunc' para truncar o arquivo (apagar o conteúdo)
        arquivo.close();
        contador = 0;  // Zerar o contador
        return;
    }
	
	// Verifica se idCliente � igual ao id  de algum cliente guardado na classe
	do {
		cout << "ID Cliente: ";
		cin >> IdClienteString;
		idCliente = converterStringToInt(IdClienteString);
	} while (!clientes.verificaCliente(idCliente));

	ofstream arquivo(NOME_FICHEIRO, ios::app);
	if (!arquivo.is_open()) {
		cout << "Erro ao abrir o arquivo venda.csv." << endl;
		return;
	}

	resultadoSorteio = gerarSorteio(ultimoIdVenda);

	// Loop para adicionar produtos � venda
	do {
		cout << "ID Produto (insira 0 para encerrar a compra): ";
		cin >> idProdutoString;
		idProduto = converterStringToInt(idProdutoString);
		if (idProduto != 0) {
			// Verifica se idProduto � igual ao id do produto Produtos.csv
			while (!produtos.verificaProduto(idProduto) || idProduto <= 0) {
				cout << "ID Produto inválido. Tente novamente: ";
				cin >> idProduto;
			}

			cout << "Quantidade: ";
			cin >> quantidadeString;
			quantidade = converterStringToInt(quantidadeString);

			while (quantidade <= 0 || quantidade > produtos.obterQuantidadeDisponivel(idProduto)) {
				cout << "Quantidade invalida ou indisponível. Tente novamente: ";
				cin >> quantidadeString;
				quantidade = converterStringToInt(quantidadeString);
			}

			if (quantidade > 0) {
				produtos.dimunirQuantidadeStock(idProduto, quantidade);
				totalQuantia = (produtos.obterPrecoProduto(idProduto) * quantidade);
				totalCompra = totalCompra + totalQuantia;
				// Adiciona o produto � venda no arquivo CSV
				arquivo << idCliente << ";" << idProduto << ";" << quantidade << ";" << ultimoIdVenda + 1 << ";"
					<< dataCSV << ";" << totalQuantia << ";" << quantiaEntregue << ";" << troco << ";" << resultadoSorteio << endl;
			}
			contador++; // Incrementa o contador
		}
	} while (idProduto != 0);

	if (!resultadoSorteio) {
		cout << "Total da Compra: " << totalCompra << "\n";
		do {

			cout << "Valor entregue: ";
			cin >> quantiaEntregueString;

			while (!converterStringToDouble(quantiaEntregueString) || stod(quantiaEntregueString) < totalCompra) {
				cout << "Valor inválido. Insira um valor igual ou superior ao total da compra: ";
				cin >> quantiaEntregueString;
			}

			quantiaEntregue = stod(quantiaEntregueString);
			troco = quantiaEntregue - totalCompra;

			if (troco < 0) {
				troco = 0;
			}

			cout << "Troco: " << troco << "\n";
			idProduto = -1;

			arquivo << idCliente << ";" << idProduto << ";" << quantidade << ";" << ultimoIdVenda + 1 << ";"
				<< dataCSV << ";" << totalCompra << ";" << quantiaEntregue << ";" << troco << ";" << resultadoSorteio << endl;
		} while (quantiaEntregue < totalCompra);
	}
	arquivo.close();
	ultimoIdVenda++;
	system("cls");
	updateClasseVenda();
	imprimirTalao(ultimoIdVenda);
	arquivo.close();
}

void GerirVenda::imprimeVendaPorProduto() {
	string nomeProduto;
	bool encontrou = false;
	cout << "Insira o nome do produto: ";
	cin >> nomeProduto;

	cout << "+--------------------------------------+\n";
	cout << "|    Relatorio de Vendas por Produto   |\n";
	cout << "+--------------------------------------+\n";

	for (int i = 0; i < contador; ++i) {
		if (nomeProduto == produtos.obterNomeProduto(venda[i].getIdProduto())) {
			venda[i].mostrarVendas();
			encontrou = true;
		}
	}
	if (!encontrou) {
		cout << "Nenhuma venda encontrada para o produto: " << nomeProduto << endl;
	}
}

int GerirVenda::produtoComMaiorLucro(){
	if (contador == 0) {
		cout << "Nenhuma venda realizada ainda. \n";
		return -1;
	}

	double maiorLucro = -1;
	int idProdutoMaiorLucro = -1;

	for (int i = 0; i < contador; ++i) {
		int idProduto = venda[i].getIdProduto();
		int quantidade = venda[i].getQuantidade();  // Add this line to get the quantity

		if (idProduto != -1) {
			double precoVenda = produtos.obterPrecoProduto(idProduto);
			double precoCusto = produtos.obterPrecoSemIva(idProduto);
			double lucro = venda[i].calcularLucro(precoVenda, precoCusto, quantidade);

			if (lucro > maiorLucro) {
				maiorLucro = lucro;
				idProdutoMaiorLucro = idProduto;
			}
		}
	}

	if (idProdutoMaiorLucro != -1) {
		return idProdutoMaiorLucro;
	}
	else {
		cout << "Nenhum produto encontrado. \n" ;
		return -1;
	}
}
