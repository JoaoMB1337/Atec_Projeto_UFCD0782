#pragma once
#include "Venda.h"
#include "Gerecliente.h"
#include "GerirProduto.h"

class GerirVenda {
private:
	void guardaInformacoes();
	int contador;
	Venda* venda;
	Gerecliente clientes;
	GerirProduto produtos;
public:
	GerirVenda();
	void adicionaVenda();
	bool verificaCliente(int idCliente);
	bool verificaProduto(int idProduto);
	bool verificarStock(int stockInserido);
};