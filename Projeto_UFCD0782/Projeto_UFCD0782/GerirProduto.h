#pragma once
#include "Produto.h"

class GerirProduto {
public:
    GerirProduto();
    void dimunirQuantidadeStock(int idProduto,int quantidade);
    int obterQuantidadeDisponivel(int idProduto);
    void adicionarProduto(int id, string nome, int stock, double precoCusto, double iva);
    void removerProduto(string nome);
    void modificarProduto(string nome, int novoStock, double novoPrecoCusto, double novoIva);
    void mostrarProdutos();
    void obterNomesQuantidades(string*& nomes, int*& quantidades, int& tamanho);

private:
    bool verificaNoCsv(int id, string nome);
    void guardarInformacoes();
    Produto* item;
    int numItem;
};