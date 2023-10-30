#pragma once
#include "Gerecliente.h"
#include "GerirProduto.h"
#include <stdlib.h>
#include <cctype>
#include <string>
class Interface
{
public:
	Interface();
	void menuPrincipal();
private:
	int converteStringParaInt(string opcao);
	void menuProduto(GerirProduto gerirProduto);
	void menuCliente(Gerecliente gerirCliente);

};
