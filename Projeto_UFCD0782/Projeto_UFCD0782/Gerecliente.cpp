#include "Gerecliente.h"
#include <cctype>
#include <fstream>
#include <sstream>

const string NOME_FICHEIRO = "cliente.csv";

void Gerecliente::updateClasseCliente(){
	ifstream arquivo(NOME_FICHEIRO);
	if (!arquivo.is_open()) {
		cout << "Arquivo de clientes n�o encontrado. \n ";
		contador = 0;
		pessoa = nullptr;
		return;
	}

	string linha;
	contador = 0;

	// Ler quantas linhas tem o csv
	while (getline(arquivo, linha)) {
		contador++;
	}

	arquivo.close();

	pessoa = new Cliente[contador];

	arquivo.open(NOME_FICHEIRO);
	contador = 0;

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
		pessoa[contador] = Cliente(nomeCSV, morada, telefone, email, nif, id);
		contador++;
	}
	arquivo.close();
}

#pragma region  Valida�oes 

//verifica nome sem numeros e caracteres especiais
bool Gerecliente::validaNome(string nome) {
	for (char c : nome)
	{
		//verifica se tem numeros ou caracteres especiais respetivamente
		if (isdigit(c) || ispunct(c))
		{
			cout << "Nome nao pode conter numeros ou caracteres especiais!" << endl << "Insira novamente: ";
			return false;
		}
	}
	return true;
}

//verifica se telefone apenas tem numeros
bool Gerecliente::validaTelefone(string telefone)
{
	for (char c : telefone)
	{
		if (!isdigit(c))
		{
			cout << "Telefone so pode conter numeros!" << endl << "Insira novamente: ";
			return false;
		}
	}
	return true;
}

//valida email e verifica se j� existe
bool Gerecliente::validaEmail(string email)
{
	if (email.find("@") == string::npos || email.find(".") == string::npos)
	{
		cout << "Email tem de conter @ e . !" << endl << "Insira novamente: ";
		return false;
	}
	for (int i = 0; i < contador; i++)
	{
		if (pessoa[i].getEmail() == email)
		{
			cout << "Email ja existe!" << endl << "Insira novamente: ";
			return false;
		}
	}
	return true;
}

//Valida NIF (9digitos) e n�o pode ter letras
bool Gerecliente::validaNif(string nif)
{
	if (nif.length() != 9)
	{
		cout << "Nif tem de ter 9 digitos! \n Insira novamente: ";
		return false;
	}
	else
	{
		for (char c : nif)
		{
			if (!isdigit(c))
			{
				cout << "Nif e composto por 9 digitos! \n Insira novamente: ";
				return false;
			}
		}
		//verifica se nif j� existe
		for (int i = 0; i < contador; i++)
		{
			if (pessoa[i].getNif() == nif)
			{
				cout << "Nif ja existe! \n Insira novamente: ";
				return false;
			}
		}
		return true;
	}
}

//verifica nif (modificar dados)
bool Gerecliente::verificaNif(string nif)
{
	if (nif.length() != 9)
	{
		cout << "Nif tem de ter 9 digitos!  \n Insira novamente: ";
		return false;
	}
	else
	{
		for (char c : nif)
		{
			if (!isdigit(c))
			{
				cout << "Nif e composto por 9 digitos! \n Insira novamente: ";
				return false;
			}
		}
		return true;
	}
}

//verifica email (modificar dados)
bool Gerecliente::verificaEmail(string email)
{
	if (email.find("@") == string::npos || email.find(".") == string::npos)
	{
		cout << "Email tem de conter @ e . ! \n Insira novamente: ";
		return false;
	}
	else
	{
		return true;
	}
}

#pragma endregion

void Gerecliente::guardaInformacoes() {
	ofstream arquivo(NOME_FICHEIRO, ios::out);

	if (!arquivo.is_open()) {
		cout << "Erro ao abrir o arquivo cliente.csv." << endl;
		return;
	}

	for (int i = 0; i < contador; i++) {
		arquivo << pessoa[i].getNome() << "," << pessoa[i].getMorada() << ","
			<< pessoa[i].getTelefone() << "," << pessoa[i].getEmail() << ","
			<< pessoa[i].getNif() << "," << pessoa[i].getId();
		if (i < contador - 1) {
			arquivo << endl; // Evita uma linha em branco no final
		}
	}
	arquivo.close();
	updateClasseCliente();
}

Gerecliente::Gerecliente() {
	updateClasseCliente();
}

//Adiciona um cliente
void  Gerecliente::adicionaCliente() {
	int id;
	string nome, morada, telefone, email, nif;

	cout << "Nome: ";
	do {
		cin >> nome;
	} while (!validaNome(nome));

	cout << "Morada: ";
	cin >> morada;

	cout << "Telefone: ";
	do {
		cin >> telefone;
	} while (!validaTelefone(telefone));

	cout << "Email: ";
	do {
		cin >> email;
	} while (!validaEmail(email));

	cout << "Nif: ";
	do {
		cin >> nif;
	} while (!validaNif(nif));



	Cliente* newpessoa = new Cliente[contador + 1];
	for (int i = 0; i < contador; i++) {
		newpessoa[i] = pessoa[i];
	}
	//ordenar por id
	Cliente aux;
	for (int i = 0; i < contador; i++)
	{
		for (int j = i + 1; j < contador; j++)
		{
			if (pessoa[i].getId() > pessoa[j].getId())
			{
				aux = pessoa[i];
				pessoa[i] = pessoa[j];
				pessoa[j] = aux;
			}
		}
	}
	//cria id unico que n�o pode ser alterado mesmo que o cliente seja removido
	if (contador == 0) {
		id = 1;
	}
	else {
		id = pessoa[contador - 1].getId() + 1;
	}

	newpessoa[contador] = Cliente(nome, morada, telefone, email, nif, id);
	if (pessoa != nullptr) {
		delete[] pessoa;
	}
	pessoa = newpessoa;
	contador++;
	guardaInformacoes();
}

//Remove um cliente pelo nome e nif
void Gerecliente::removeCliente() {
	string nome, nif;
	bool existe = false;
	cout << "Nome: ";
	cin >> nome;
	cout << "Nif: ";
	cin >> nif;
	for (int i = 0; i < contador; i++)
	{
		if (pessoa[i].getNome() == nome && pessoa[i].getNif() == nif)
		{
			pessoa[i] = pessoa[contador - 1];
			contador--;
			existe = true;
			guardaInformacoes();
		}
	}
	if (existe == false)
	{
		cout << "Cliente nao existe! \n";
	}
	else {
		cout << "Cliente removido com sucesso! \n";
	}
}

//Modifica o procurando o cliente por o nome e o NIF cliente 
void Gerecliente::modificadadoCliente() {
	string nome, nif;
	bool existe = false;
	cout << "Insira o nome do cliente que pretende modificar: ";
	do {
		cin >> nome;
	} while (!validaNome(nome));
	cout << "Insira o nif do cliente que pretende modificar: ";
	do {
		cin >> nif;
	} while (!verificaNif(nif));
	for (int i = 0; i < contador; i++)
	{
		if (pessoa[i].getNome() == nome && pessoa[i].getNif() == nif)
		{
			string nome, morada, telefone, email, nif;
			cout << "Nome: ";
			do {
				cin >> nome;
			} while (!validaNome(nome));
			cout << "Morada: ";
			cin >> morada;
			cout << "Telefone: ";
			do {
				cin >> telefone;
			} while (!validaTelefone(telefone));
			cout << "Email: ";
			do {
				cin >> email;
			} while (!verificaEmail(email));
			cout << "Nif: ";
			do {
				cin >> nif;
			} while (!verificaNif(nif));
			pessoa[i].setNome(nome);
			pessoa[i].setMorada(morada);
			pessoa[i].setTelefone(telefone);
			pessoa[i].setEmail(email);
			pessoa[i].setNif(nif);
			existe = true;
			guardaInformacoes();
			return;
		}
	}
	if (existe == false)
	{
		cout << "Cliente nao existe!" << endl;
	}
	else {
		cout << "Cliente modificado com sucesso!" << endl;
	}
}

void Gerecliente::listaClientes() {
	for (int i = 0; i < contador; i++)
	{
		pessoa[i].mostrarClientes();
	}
}

bool Gerecliente::verificaCliente(int idCliente) {
	for (int i = 0; i < contador; i++) {
		if (pessoa[i].getId() == idCliente) {
			return true;
		}
	}
	cout << "Cliente nao existe!! \n";
	return false;
}

string Gerecliente::obterNomeCliente(int idCliente)
{
	for (int i = 0; i < contador; i++) {
		if (pessoa[i].getId() == idCliente) {
			return pessoa[i].getNome();
		}
	}
	return "Nao Existe!";
}
