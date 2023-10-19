#include "GerirProduto.h"
#include <string>
using namespace std;
int main() {

    GerirProduto gestor;

    gestor.adicionarProduto(1, "Produto 1", 10, 10.0, 0.23);
    gestor.adicionarProduto(2, "Produto 2", 20, 15.0, 0.23);


    std::cout << "Lista de Produtos:" << std::endl;
    gestor.mostrarProdutos();
    cout << "\n";

    gestor.modificarProduto(1, 15, 12.0, 0.20);

    std::cout << "Lista de Produtos Apos Modificacao:" << std::endl;
    gestor.mostrarProdutos();

    gestor.removerProduto("Produto 2");
    cout << "\n";


    std::cout << "Lista de Produtos Apos Remocao:" << std::endl;
    gestor.mostrarProdutos();

    return 0;
}

