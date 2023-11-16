#pragma once
#include "GereCliente.h"
#include "GerirProduto.h"
#include "GerirVenda.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>
#include <map>

class Relatorio {
private:

	GerirProduto gestorProduto;
	Gerecliente gestorCliente;
	GerirVenda gestorVenda;

public:

	Relatorio();
	void updatesClasses();
	void imprimirNomesQuantidades();
	void imprimeSemStock();
	void imprimeMaisMenosVendido();
};

