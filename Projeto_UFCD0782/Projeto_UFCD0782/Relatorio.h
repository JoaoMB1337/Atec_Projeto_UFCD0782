#pragma once
#include "GerirProduto.h"
#include "GereCliente.h"
#include "GerirProduto.h"
#include "GerirVenda.h"
#include <cctype>
#include <fstream>
#include <sstream>

class Relatorio {
private:

public:
	void imprimirNomesQuantidades(GerirProduto& gerenciadorProdutos);
	void imprimeSemStock(GerirProduto& gerenciadorProdutos);

};

