#include "Gerecliente.h"
#include <cctype>
//Validações//////////////////////////////////////////////

//verifica nome sem numeros e caracteres especiais
bool Gerecliente::validaNome(string nome) {
	for (char c : nome)
	{
		//verifica se tem numeros ou caracteres especiais respetivamente
		if (isdigit(c) || ispunct(c))
		{
			cout << "Nome nao pode conter numeros ou caracteres especiais!"<<endl<<"Insira novamente: ";
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
			cout << "Telefone so pode conter numeros!"<<endl<<"Insira novamente: ";
			return false;
		}
	}
	return true;
}
//valida email e verifica se já existe
bool Gerecliente::validaEmail(string email)
{
	if (email.find("@") == string::npos || email.find(".") ==string::npos)
	{
		cout << "Email tem de conter @ e . !"<<endl<<"Insira novamente: ";
		return false;
	}
	else
	{
		//verifica se email já existe
		for (int i = 0; i < contador; i++)
		{
			if (pessoa[i].getEmail() == email)
			{
				cout << "Email ja existe!" << endl << "Insira novamente: ";
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}
//Valida NIF (9digitos) e não pode ter letras
bool Gerecliente::validaNif(string nif)
{
	if (nif.length() != 9)
	{
		cout << "Nif tem de ter 9 digitos!"<<endl<<"Insira novamente: ";
		return false;
	}
	else
	{
		for (char c : nif)
		{
			if (!isdigit(c))
			{
				cout << "Nif e composto por 9 digitos!"<<endl<<"Insira novamente: ";
				return false;
			}
		}
		//verifica se nif já existe
		for (int i = 0; i < contador; i++)
		{
			if (pessoa[i].getNif() == nif)
			{
				cout << "Nif ja existe!" << endl << "Insira novamente: ";
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
		cout << "Nif tem de ter 9 digitos!" << endl << "Insira novamente: ";
		return false;
	}
	else
	{
		for (char c : nif)
		{
			if (!isdigit(c))
			{
				cout << "Nif e composto por 9 digitos!" << endl << "Insira novamente: ";
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
		cout << "Email tem de conter @ e . !" << endl << "Insira novamente: ";
		return false;
	}
	else
	{
		return true;
	}
}

//Fim das validações///////////////////////////////////////

//Adiciona um cliente
void  Gerecliente::adicionaCliente() {
	if (contador < 100) {
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

		id = id++;
		pessoa[contador] = Cliente(nome, morada, telefone, email, nif, id);
		contador++;
	}
	else
	{
		cout << "Limite de clientes atingido!" << endl;
	}
}

//Remove um cliente pelo nome e nif
void Gerecliente::removeCliente()
{
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
			break;
		}
	}
	if (existe == false)
	{
		cout << "Cliente nao existe!" << endl;
	}
	else {
		cout<< "Cliente removido com sucesso!" << endl;	
	}
}

void Gerecliente::modificadadoCliente()
{
	string nome,nif;
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
			string nome, morada, telefone, email,nif;
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
			cout<< "Nif: ";
			do {
				cin >> nif;
			} while (!verificaNif(nif));
			pessoa[i].setNome(nome);
			pessoa[i].setMorada(morada);
			pessoa[i].setTelefone(telefone);
			pessoa[i].setEmail(email);
			pessoa[i].setNif(nif);
			existe = true;
			break;
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

void Gerecliente::listaClientes()
{
	for (int i = 0; i < contador; i++)
	{
		cout << pessoa[i].to_String() << endl;
	}
}
