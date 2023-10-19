#include "Produto.h"
#include <iomanip>
Produto::Produto()
{
    id = 0;
    nome = "";
    stock = 0;
    precoCusto = 0.0;
    iva = 0.0;
    precoVenda = 0.0;
}

Produto::Produto(int id, const string nome, int stock, double precoCusto, double iva){
    this->id = id;
    this->nome = nome;
    this->stock = stock;
    this->precoCusto = precoCusto;
    this->iva = iva;
    this->precoVenda = calcularPrecoVenda(precoCusto,iva);
}

#pragma region get´s

int Produto::getId(){
    return this->id;
}

string Produto::getNome(){
    return this->nome;
}

int Produto::getStock(){
    return this->stock;
}

double Produto::getPrecoCusto(){
    return this->precoCusto;
}

int Produto::getIva(){
    return this->iva;
}
#pragma endregion

#pragma region Set´s



void Produto::setId(int id){
    this->id = id;
}

void Produto::setNome(string nome){
    this->nome = nome;
}

void Produto::setStock(int stock){
    this->stock = stock;
}

void Produto::setPrecoCusto(double precoCusto){
    this->precoCusto = precoCusto;
}

void Produto::setIva(double iva){
    this->iva = iva;
}
#pragma endregion

double Produto::calcularPrecoVenda(double PrecoVenda, double iva){
    PrecoVenda *= 1.30;
    PrecoVenda += PrecoVenda * (iva/100);
    return PrecoVenda;
}

void Produto::mostrarInformacoes(){
    cout << "ID: " << this->id << endl;
    cout << "Nome: " << this->nome << endl;
    cout << "Stock: " << this->stock << endl;
    cout << "Preco de Custo: " << fixed<<setprecision(2)<<this->precoCusto << endl;
    cout << "IVA: " << this->iva*100 << "%" << endl;
    cout << "Preco de Venda: " << this->calcularPrecoVenda(precoCusto,iva) << endl;
    cout << "------------------------------------------------------------------------ \n\n";
}
