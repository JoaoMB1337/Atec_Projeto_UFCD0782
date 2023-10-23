#pragma once
#include "cliente.h"
#include <string>
class Gerecliente
{
private:
	Cliente pessoa[100];
	int contador = 0;
	int id = 0;
public:
	void adicionaCliente();
	void removeCliente();
	void modificadadoCliente();
	void listaClientes();
	bool validaEmail(string email);
	bool validaNome(string nome);
	bool validaNif(string nif);
	bool validaTelefone(string telefone);
	bool verificaNif(string nif);
	bool verificaEmail(string email);
};
