#pragma once
#include "Produto.h"

class GerirProduto {
public:
    GerirProduto();
    void adicionarProduto();
    void removerProduto();
    void modificarProduto();
    void mostrarProdutos();
    void obterNomesQuantidades(string*& nomes, int*& quantidades, int& tamanho);
    bool validaNome(string nome);
    bool validaPreco(double preco);
    bool validaStock(int stock);
    bool validaIva(double iva);

private:
    bool verificaNoCsv(int id, string nome);
    Produto* item;
    int numItem;
    void guardaInformacoes();
};
