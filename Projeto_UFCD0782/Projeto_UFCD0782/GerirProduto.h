#pragma once
#include "Produto.h"

class GerirProduto {
    public:
        
        void adicionarProduto(int id,string nome, int stock, double precoCusto, double iva);
        void removerProduto(string nome);
        void modificarProduto(int id,int novoStock, double novoPrecoCusto, double novoIva);
        void mostrarProdutos();

    private:
        Produto item[10];
        int numItem = 0;
};