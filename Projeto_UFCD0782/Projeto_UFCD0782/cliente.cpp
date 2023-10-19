#include "Cliente.h"

Cliente::Cliente()
{
	this->nome = "";
	this->morada = "";
	this->telefone = "";
	this->email = "";
	this->nif = "";
	this->id = "";
}

Cliente::Cliente(string nome, string morada, string telefone, string email,string nif, string id)
{
	this->nome = nome;
	this->morada = morada;
	this->telefone = telefone;
	this->email = email;
	this->nif = nif;
	this->id = id;
}

string Cliente::getNome()
{
	return nome;
}

string Cliente::getMorada()
{
	return morada;
}

string Cliente::getTelefone()
{
	return telefone;
}

string Cliente::getEmail()
{
	return email;
}

string Cliente::getNif()
{
	return nif;
}

string Cliente::getId()
{
	return id;
}

void Cliente::setNome(string nome)
{
	this->nome = nome;
}

void Cliente::setMorada(string morada)
{
	this->morada = morada;
}

void Cliente::setTelefone(string telefone)
{
	this->telefone = telefone;
}

void Cliente::setEmail(string email)
{
	this->email = email;
}

void Cliente::setNif(string nif)
{
	this->nif = nif;
}


void Cliente::setId(string id)
{
	this->id = id;	
}

string Cliente::to_String()
{

	return "Nome: " + this->nome + 
		"\nMorada: " + this->morada +
		"\nTelefone: " + this->telefone +
		"\nEmail: " +this->email +
		"\nNIF :" + this->nif +
		"\n ID: " + this->id + "\n";
}



