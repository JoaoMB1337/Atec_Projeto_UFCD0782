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

Produto::Produto(int id, const string nome, int stock, double precoCusto, double iva) {
    this->id = id;
    this->nome = nome;
    this->stock = stock;
    this->precoCusto = precoCusto;
    this->iva = iva;
    this->precoVenda = calcularPrecoVenda(precoCusto, iva);
}

#pragma region get´s

int Produto::getId() {
    return this->id;
}

string Produto::getNome() {
    return this->nome;
}

int Produto::getStock() {
    return this->stock;
}

double Produto::getPrecoCusto() {
    return this->precoCusto;
}

int Produto::getIva() {
    return this->iva;
}
#pragma endregion

#pragma region Set´s

void Produto::setId(int id) {
    if (id < 0) {
       cout<<"O ID do produto não pode ser menor que zero!\n";
    }
    this->id = id;
}

void Produto::setNome(string nome) {
    if (nome.empty()) {
        cout<<"O nome do produto não pode estar vazio!\n";
    }
    this->nome = nome;
}

void Produto::setStock(int stock) {
    if (stock < 0) {
        cout<<"O stock do produto não pode ser menor que zero!";
    }
    this->stock = stock;
}

void Produto::setPrecoCusto(double precoCusto) {
    if (precoCusto < 0) {
        cout<<"O preço de custo do produto não pode ser menor que zero!";
    }
    this->precoCusto = precoCusto;
}

void Produto::setIva(double iva) {
    if (iva < 0) {
       cout<<"O IVA do produto não pode ser menor que zero!";
    }
    this->iva = iva;
}
#pragma endregion

double Produto::calcularPrecoVenda(double PrecoVenda, double iva) {
    PrecoVenda *= 1.30;
    PrecoVenda += PrecoVenda * (iva / 100);
    return PrecoVenda;
}

void Produto::mostrarInformacoes() {

    cout << "ID: " << this->id <<"\n";
    cout << "Nome: " << this->nome <<"\n";
    cout << "Stock: " << this->stock << "\n";
    cout << "Preco de Custo: " << fixed << setprecision(2) << this->precoCusto << "\n";
    cout << "IVA: " << this->iva << "%" <<"\n";
    cout << "Preco de Venda: " << this->calcularPrecoVenda(precoCusto, iva) << "\n";
    cout << "+------------------------------------+ \n";
}
