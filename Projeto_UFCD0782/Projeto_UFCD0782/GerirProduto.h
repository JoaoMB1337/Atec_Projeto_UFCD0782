#pragma once
#include "Produto.h"

class GerirProduto {
public:
    GerirProduto();

    #pragma region Funçoes de modicaçao da classe Produto
    void dimunirQuantidadeStock(int idProduto,int quantidade);
    void adicionarProduto(int id, string nome, int stock, double precoCusto, double iva);
    void removerProduto(string nome);
    void modificarProduto(string nome, int novoStock, double novoPrecoCusto, double novoIva);
    void mostrarProdutos();
    #pragma endregion

    #pragma region Funçoes de Acesso Exterior
    void obterNomesQuantidades(string*& nomes, int*& quantidades, int& tamanho);
    int obterQuantidadeDisponivel(int idProduto);
    double obterPrecoProduto(int idProduto);
    string obterNomeProduto(int idProduto);
    int obterIvaProduto(int idProduto);
    #pragma endregion


private:
    bool verificaNoCsv(int id, string nome);
    void guardarInformacoes();
    Produto* item;
    int numItem;
};