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
	double valorEntrege;
	double troco;
	bool sorteio;

public:

	Venda();
	Venda(int idCliente, int idProduto, int quantidade, int idVenda, string data, double total, double valorEntrege, double troco,bool sorteio);
	void setIdCliente(int idCliente);
	void setIdProduto(int idProduto);
	void setQuantidade(int quantidade);
	void setIdVenda(int idVenda);
	void setData(string data);
	void setTotal(double total);
	void setValorEntrege(double valorEntrege);
	void setTroco(double troco);
	void setSorteio(bool sorteio);

	int getIdCliente();
	int getIdProduto();
	int getQuantidade();
	int getIdVenda();
	string getData();
	double getTotal();
	double getValorEntrege();
	double getTroco();
	bool getSorteio();
	void mostrarVendas();
};