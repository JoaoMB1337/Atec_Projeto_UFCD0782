#pragma once
#include "cliente.h"

class Gerecliente
{
private:
	Cliente pessoa[100];
	int contador = 0;
public:
	void adicionaCliente();
	void removeCliente();
	void modificanomeCliente();
	void listaClientes();
	bool verificaEmail(string email);
};
