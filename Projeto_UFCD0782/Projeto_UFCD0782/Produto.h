#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Produto {

public:
    Produto();
    Produto(int id, string nome, int stock, double precoCusto, double iva);
    double calcularPrecoVenda(double precoCusto, double iva);
    double calcularPrecoSemIva(double precoVenda, double iva);
    void mostrarInformacoes();

    // Métodos "GET"
    int getId();
    string getNome();
    int getStock();
    double getPrecoCusto();
    int getIva();

    // Métodos SET
    void setId(int id);
    void setNome(string nome);
    void setStock(int stock);
    void setPrecoCusto(double precoCusto);
    void setIva(double iva);

private:
    int id;
    string nome;
    int stock;
    double precoCusto;
    double iva;
    double precoVenda; // +30% + iva
    Produto* item;
};