#include "Venda.h"

Venda::Venda()
{
	this->idCliente = 0;
	this->idProduto = 0;
	this->quantidade = 0;
	this->idVenda = 0;
	this->data = "";
	this->total = 0.0;
}

Venda::Venda(int idCliente, int idProduto, int quantidade, int idVenda, string data, double total)
{
	this->idCliente = idCliente;
	this->idProduto = idProduto;
	this->quantidade = quantidade;
	this->idVenda = idVenda;
	this->data = data;
	this->total = total;
}

int Venda::getIdCliente()
{
	return idCliente;
}

int Venda::getIdProduto()
{
	return idProduto;
}

int Venda::getQuantidade()
{
	return quantidade;
}

int Venda::getIdVenda()
{
	return idVenda;
}

string Venda::getData()
{
	return data;
}

double Venda::getTotal()
{
	return total;
}

void Venda::setIdCliente(int idCliente)
{
	this->idCliente = idCliente;
}
void Venda::setQuantidade(int quantidade)
{
	this->quantidade = quantidade;
}

void Venda::setIdProduto(int idProduto)
{
	this->idProduto = idProduto;
}

void Venda::setIdVenda(int idVenda)
{
	this->idVenda = idVenda;
}

void Venda::setData(string data)
{
	this->data = data;
}

void Venda::setTotal(double total)
{
	this->total = total;
}

void Venda::mostrarVendas()
{
	cout << "ID Cliente: " << idCliente << endl;
	cout << "ID Produto: " << idProduto << endl;
	cout << "Quantidade: " << quantidade << endl;
	cout << "ID Venda: " << idVenda << endl;
	cout << "Data: " << data << endl;
	cout << "Total: " << total << endl;
}