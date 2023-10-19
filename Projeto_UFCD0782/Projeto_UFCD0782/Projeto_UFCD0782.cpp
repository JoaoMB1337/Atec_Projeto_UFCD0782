#include <iostream>
#include "Gerecliente.h"

int main()
{
    Gerecliente A;
    while (true) {
        cout << "\nEscolha uma opcao:" << endl;
        cout << "1. Adicionar cliente" << endl;
        cout << "2. Remover cliente" << endl;
        cout << "3. Modifica nome" << endl;
        cout << "4. Listar clientes" << endl;
        cout << "5. Sair" << endl;

        int opcao;
        cin >> opcao;

        switch (opcao) {
        case 1:
            A.adicionaCliente();
            break;
        case 2:
            A.removeCliente();
            break;
        case 3:
            A.modificanomeCliente();
            break;
        case 4:
			A.listaClientes();
			break;
        case 5:
            return 0;
        default:
            cout << "Opção inválida. Tente novamente." << endl;
        }
    }

    return 0;
}
