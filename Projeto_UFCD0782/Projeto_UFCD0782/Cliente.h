#pragma once

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
	string id;

public:
	Cliente();
	Cliente(string nome, string morada, string telefone, string email,string nif, string id);
	string getNome();
	string getMorada();
	string getTelefone();
	string getEmail();
	string getNif();
	string getId();
	void setNome(string nome);
	void setMorada(string morada);
	void setTelefone(string telefone);
	void setEmail(string email);
	void setNif(string nif);
	void setId(string id);
	string to_String();
};
