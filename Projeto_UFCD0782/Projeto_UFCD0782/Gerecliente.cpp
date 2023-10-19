#include "Gerecliente.h"

//Adiciona um cliente
void  Gerecliente::adicionaCliente() {
	string nome, morada, telefone, email, nif, id;
	cout << "Nome: ";
	cin >> nome;
	cout << "Morada: ";
	cin >> morada;
	cout << "Telefone: ";
	cin >> telefone;
	cout << "Email: ";
	//valida email
	do {
		cin >> email;
		if (verificaEmail(email))
		{
			if (email == "") {
				cout << "Email nao pode estar vazio!";
			}
			else {
				cout << "\nEsse email ja existe! Insira outro por favor:\n";
			}
		};
	} while (verificaEmail(email));
	pessoa[contador] = Cliente(nome, morada, telefone, email, nif, id);
	contador++;
	cout << "Nif";
	cin >> nif;
}


void Gerecliente::removeCliente()
{
	string nome;
	cout << "Nome: ";
	cin >> nome;
	for (int i = 0; i < contador; i++)
	{
		if (pessoa[i].getNome() == nome)
		{
			pessoa[i] = pessoa[contador - 1];
			contador--;
			break;
		}
	}
}

void Gerecliente::modificanomeCliente()
{
	string nome;
	cout << "Nome: ";
	cin >> nome;
	for (int i = 0; i < contador; i++)
	{
		if (pessoa[i].getNome() == nome)
		{
			string nome, morada, telefone, email;
			cout << "Nome: ";
			cin >> nome;
			cout << "Morada: ";
			cin >> morada;
			cout << "Telefone: ";
			cin >> telefone;
			cout << "Email: ";
			cin >> email;
			pessoa[i].setNome(nome);
			pessoa[i].setMorada(morada);
			pessoa[i].setTelefone(telefone);
			pessoa[i].setEmail(email);
			break;
		}
	}
}

void Gerecliente::listaClientes()
{
	for (int i = 0; i < contador; i++)
	{
		cout << pessoa[i].to_String() << endl;
	}
}


//validações
//verifica se o email existe ou se não está vazio
bool Gerecliente::verificaEmail(string email)
{
	if (email == "")
	{
		return true;
	}
	for (int i = 0; i < contador; i++)
	{
		if (pessoa[i].getEmail() == email)
		{
			return true;
		}
	}
	return false;
}

