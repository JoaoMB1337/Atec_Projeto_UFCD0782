#pragma once
#include "GerirProduto.h"
#include "GereCliente.h"
#include "Venda.h"

class GerirVenda {
private:
	void guardaInformacoes();
	int contador;
	Venda* venda;
public:
	GerirVenda();
	void adicionaVenda();

};