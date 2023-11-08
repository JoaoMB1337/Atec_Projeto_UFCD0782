#include "GerirVenda.h"
#include <cctype>
#include <fstream>
#include <sstream>

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

void GerirVenda::adicionaVenda()
{

	int idCliente, idProduto, quantidade, idVenda;
	string dataCSV, pessoa;
	double total;

	//verifica se idCliente é igual ao id do cliente Cliente.csv
	cout << "ID Cliente: ";
	do {
		cin >> idCliente;
	}
	while(!verificaCliente(idCliente));
	

	//verifica se idProduto é igual ao id do produto produtos.csv
	cout << "ID Produto: ";
	do {
		cin >> idProduto;
	} while (!verificaProduto(idProduto));
	


	cout << "Quantidade: ";
	cin >> quantidade;
	cout << "ID Venda: ";
	cin >> idVenda;
	cout << "Data: ";
	cin >> dataCSV;
	cout << "Total: ";
	cin >> total;


	Venda* newvenda = new Venda[contador + 1];
	for (int i = 0; i < contador; i++) {
		newvenda[i] = venda[i];
	}
	newvenda[contador] = Venda(idCliente, idProduto, quantidade, idVenda, dataCSV, total);
	if (venda != nullptr) {
		delete[] venda;
	}
	venda = newvenda;
	contador++;
	guardaInformacoes();
}

bool GerirVenda::verificaCliente(int idCliente)
{
	string pessoa;
	ifstream arquivo("cliente.csv");
	if (!arquivo.is_open()) {
		cout << "Arquivo de clientes não encontrado." << endl;
		contador = 0;
		pessoa = nullptr;
		return false;
	}
	bool existe = false;
	string linha;
	while (getline(arquivo, linha)) {
		stringstream ss(linha);
		string idCSV, nomeCSV, morada, telefone, email, nif;
		getline(ss, nomeCSV, ',');
		getline(ss, morada, ',');
		getline(ss, telefone, ',');
		getline(ss, email, ',');
		getline(ss, nif, ',');
		getline(ss, idCSV, ',');

		int id = stoi(idCSV);
		if (idCliente == id) {
			existe = true;
			return true;
		}
	}
	arquivo.close();
	if (existe == false) {
		cout << "ID Cliente não existe." << endl;
		return false;
	}

	return false;
}

bool GerirVenda::verificaProduto(int idProduto)
{
	string produto;
	ifstream arquivo2("produtos.csv");
	if (!arquivo2.is_open()) {
		cout << "Arquivo de produtos não encontrado." << endl;
		contador = 0;
		produto = nullptr;
		return false;
	}
	bool existe2 = false;
	string linha2;
	while (getline(arquivo2, linha2)) {
		stringstream ss(linha2);
		string idCSV, nomeCSV, precoCSV, stockCSV;
		getline(ss, nomeCSV, ',');
		getline(ss, precoCSV, ',');
		getline(ss, stockCSV, ',');
		getline(ss, idCSV, ',');

		int id = stoi(idCSV);
		if (idProduto == id) {
			existe2 = true;
			return true;
		}
	}
	arquivo2.close();
	if (existe2 == false) {
		cout << "ID Produto não existe." << endl;
		return false;
	}

	return false;
}

bool GerirVenda::verificarStock(int stock){
	return false;
}
