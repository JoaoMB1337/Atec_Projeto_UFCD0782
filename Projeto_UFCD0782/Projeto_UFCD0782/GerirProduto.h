#pragma once
#include "Produto.h"

class GerirProduto {
    public:
        GerirProduto();

        #pragma region Funcoes de modicacao da classe Produto
        void adicionarProduto();
        void removerProduto();
        void modificarProduto();
        void dimunirQuantidadeStock(int idProduto,int quantidade);
        void mostrarProdutos();
        #pragma endregion

        #pragma region Funcoes de Acesso Exterior
        void obterNomesQuantidades(string*& nomes, int*& quantidades, int& tamanho);
        bool verificaProduto(int idProduto);
        int obterQuantidadeDisponivel(int idProduto);
        double obterPrecoProduto(int idProduto);
        string obterNomeProduto(int idProduto);
        int obterIvaProduto(int idProduto);
        double obterPrecoSemIva(int idProduto);
        #pragma endregion

    private:
    
        bool validaNome(string nome);
        bool validaPreco(double preco);
        bool validaStock(int stock);
        bool validaIva(double iva);
        bool verificaNoCsv(int id, string nome);

        Produto* item;
        int numItem;
        void guardaInformacoes();
};
