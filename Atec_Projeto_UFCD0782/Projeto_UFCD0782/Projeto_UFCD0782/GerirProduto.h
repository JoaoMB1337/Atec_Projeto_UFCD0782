#pragma once
#include "Produto.h"

class GerirProduto {
    public:
        GerirProduto();
        void adicionarProduto(int id, string nome, int stock, double precoCusto, double iva);
        void removerProduto(string nome);
        void modificarProduto(string nome,int novoStock, double novoPrecoCusto, double novoIva);
        void mostrarProdutos();

    private:
        bool verificaNoCsv(int id,string nome);
        void guardarInformacoes();
        Produto* item;
        int numItem;
};