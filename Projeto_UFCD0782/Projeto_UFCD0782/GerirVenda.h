#pragma once
#include "Venda.h"
#include "Gerecliente.h"
#include "GerirProduto.h"

class GerirVenda {
	private:
		string obterHora();
		void guardaInformacoes();
		int contador;
		Venda* venda;
		Gerecliente clientes;
		GerirProduto produtos;
		int idVenda;
	public:

		GerirVenda();
		void adicionaVenda();
		void imprimirTalao(int idcompra);
		void imprimeVendaPorProduto(GerirProduto& gerenciadorProdutos, GerirVenda& gerenciadorVendas);
};