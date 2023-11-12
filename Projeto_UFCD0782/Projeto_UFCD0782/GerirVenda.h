#pragma once
#include "Venda.h"
#include "Gerecliente.h"
#include "GerirProduto.h"

class GerirVenda {
	private:
		void updateClasseVenda();
		string obterHora();
		bool gerarSorteio(int idCompra);
		int contador;
		Venda* venda;
		Gerecliente clientes;
		GerirProduto produtos;
		int idVenda;

	public:

		GerirVenda();
		void adicionaVenda();
		void imprimirTalao(int idcompra);
};