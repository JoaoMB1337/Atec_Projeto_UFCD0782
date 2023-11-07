#pragma once
#include "GerirProduto.h"
#include "GereCliente.h"

class Venda {
private:
	int idCliente;
	int idProduto;
	int quantidade;
	int idVenda;
	string data;
	double total;
public:
	Venda();
	Venda(int idCliente, int idProduto, int quantidade, int idVenda, string data, double total);
	void setIdCliente(int idCliente);
	void setIdProduto(int idProduto);
	void setQuantidade(int quantidade);
	void setIdVenda(int idVenda);
	void setData(string data);
	void setTotal(double total);
	int getIdCliente();
	int getIdProduto();
	int getQuantidade();
	int getIdVenda();
	string getData();
	double getTotal();
	void mostrarVendas();
};