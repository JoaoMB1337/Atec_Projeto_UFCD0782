#pragma once
#include "Produto.h"

class GerirProduto {
public:
    GerirProduto();
    void adicionarProduto();
    void removerProduto();
    void modificarProduto();

    #pragma region Fun�oes de modica�ao da classe Produto
    void dimunirQuantidadeStock(int idProduto,int quantidade);
    void adicionarProduto(int id, string nome, int stock, double precoCusto, double iva);
    void removerProduto(string nome);
    void modificarProduto(string nome, int novoStock, double novoPrecoCusto, double novoIva);
    void mostrarProdutos();
    #pragma endregion

    #pragma region Fun�oes de Acesso Exterior
    void obterNomesQuantidades(string*& nomes, int*& quantidades, int& tamanho);
    bool validaNome(string nome);
    bool validaPreco(double preco);
    bool validaStock(int stock);
    bool validaIva(double iva);
    int obterQuantidadeDisponivel(int idProduto);
    double obterPrecoProduto(int idProduto);
    string obterNomeProduto(int idProduto);
    int obterIvaProduto(int idProduto);
    #pragma endregion


private:
    bool verificaNoCsv(int id, string nome);
    Produto* item;
    int numItem;
    void guardaInformacoes();
};
