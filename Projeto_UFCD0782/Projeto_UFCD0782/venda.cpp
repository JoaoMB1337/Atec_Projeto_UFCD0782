#include "Venda.h"

Venda::Venda(){
	this->idCliente = 0;
	this->idProduto = 0;
	this->quantidade = 0;
	this->idVenda = 0;
	this->data = "";
	this->total = 0.0;
	this->valorEntrege = 0.0;
	this->troco = 0.0;
	this->sorteio = false;
}

Venda::Venda(int idCliente, int idProduto, int quantidade, int idVenda, string data, double total, double valorEntrege, double troco, bool sorteio)
{
	this->idCliente = idCliente;
	this->idProduto = idProduto;
	this->quantidade = quantidade;
	this->idVenda = idVenda;
	this->data = data;
	this->total = total;
	this->valorEntrege = valorEntrege;
	this->troco = troco;
	this->sorteio = sorteio;
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

double Venda::getValorEntrege()
{
	return valorEntrege;
}

double Venda::getTroco()
{
	return troco;
}

bool Venda::getSorteio()
{
	return sorteio;
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

void Venda::setValorEntrege(double valorEntrege){
	this->valorEntrege = valorEntrege;
}

void Venda::setTroco(double troco){
	this->troco = troco;

}

void Venda::setSorteio(bool sorteio){
	this->sorteio = sorteio;
}


void Venda::mostrarVendas(){
	cout << "| " << setw(11) << left << idCliente << "| " << setw(11) << left << idProduto << "| " << setw(11) << left << quantidade << "| " 
		<< setw(9) << left << idVenda << "| " << setw(15) << left << data << "| " << setw(14) << left << total << "| " << setw(15) << left 
		<< valorEntrege << "| " << setw(8) << left << troco << "|\n";
}

double Venda::calcularLucro(double precoVenda, double precoCusto, int quantidade) {
	return (precoVenda - precoCusto) * quantidade;
}
	
