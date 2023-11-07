#pragma once
#include <string>
#include <iostream>
using namespace std;

class Cliente
{
private:
	string nome;
	string morada;
	string telefone;
	string email;
	string nif;
	int id;

public:
	Cliente();
	Cliente(string nome, string morada, string telefone, string email,string nif, int id);
	string getNome();
	string getMorada();
	string getTelefone();
	string getEmail();
	string getNif();
	int getId();
	void setNome(string nome);
	void setMorada(string morada);
	void setTelefone(string telefone);
	void setEmail(string email);
	void setNif(string nif);
	void setId(int id);
	void mostrarClientes();
};
