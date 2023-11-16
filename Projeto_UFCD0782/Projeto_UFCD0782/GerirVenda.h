#pragma once
#include "Venda.h"
#include "Gerecliente.h"
#include "GerirProduto.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <map>
#include <ctime>

class GerirVenda {
	private:
		int converterStringToInt(string str);
		double converterStringToDouble(string str);
		void updateClasseVenda();
		string obterHora();
		bool gerarSorteio(int idCompra);
		int obterUltimoIdVenda();
		int encontrarClientePorIdVenda(int idcompra);
		bool encontrarSorteioPorIdVenda(int idcompra);
		int contador;
		Venda* venda;
		Gerecliente clientes;
		GerirProduto produtos;
		int idVenda;

	public:
		GerirVenda();
		void updatingClasses();
		void adicionaVenda();
		void imprimirTalao(int idcompra);
		void imprimeVendaPorProduto();
		int produtoComMaiorLucro();
};