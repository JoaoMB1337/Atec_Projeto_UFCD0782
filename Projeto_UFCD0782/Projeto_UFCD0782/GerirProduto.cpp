#include "GerirProduto.h"

void GerirProduto::adicionarProduto(int id, string nome, int stock, double precoCusto, double iva)
{
    if (numItem < 10) {
        item[numItem] = Produto(id, nome, stock,precoCusto,iva);
        numItem++;
    }
    else {
        cout << "Array Cheio:" << endl;
    }
}

void GerirProduto::removerProduto(string nome)
{
    bool verificaProduto = false;
    for (int i = 0; i < numItem; i++) {
        if (item[i].getNome() == nome) {
            for (int j = i; j < numItem - 1; j++) {
                item[j] = item[j + 1];
            }
            numItem--;
            verificaProduto = true;
            return; 
        }
    }
    if (!verificaProduto) {
        cout << "Nao foi encontrado nenhum produto!" << endl;
    }
}

void GerirProduto::modificarProduto(int id, int novoStock, double novoPrecoCusto, double novoIva){

    bool verificaProduto = false;
    for (int i = 0; i < numItem; i++) {
        if (item[i].getId() == id) {
            item[i].setStock(novoStock);
            item[i].setPrecoCusto(novoPrecoCusto);
            item[i].setIva(novoIva);
            verificaProduto = true;
            cout << "Produto modificado com sucesso!" << endl;
            return;
        }
    }

    if (!verificaProduto) {
        cout << "Produto não encontrado!" << endl;
    }
}

void GerirProduto::mostrarProdutos()
{
    for (int  i = 0; i < numItem; i++){
        item[i].mostrarInformacoes();
    }
}
