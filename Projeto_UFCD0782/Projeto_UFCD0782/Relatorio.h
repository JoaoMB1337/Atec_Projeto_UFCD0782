#pragma once
#include "GereCliente.h"
#include "GerirProduto.h"
#include "GerirVenda.h"
#include <cctype>
#include <fstream>
#include <sstream>

class Relatorio {
private:

	GerirProduto gestorProduto;
	Gerecliente gestorCliente;
	GerirVenda gestorVenda;

public:

	Relatorio();
	void imprimirNomesQuantidades();
	void imprimeSemStock();
	void imprimeMaisMenosVendido();
};

