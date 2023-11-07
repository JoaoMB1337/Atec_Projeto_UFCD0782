#include <iostream>
using namespace std;

void exibirMenu() {
    cout << "=== Menu Inicial ===" << endl;
    cout << "1. Vender" << endl;
    cout << "2. Comprar" << endl;
    cout << "3. Relatorios" << endl;
    cout << "4. Gestao de Clientes" << endl;
    cout << "5. Sair" << endl;
}

int main() {
    int opcao;
    while (true) {
        exibirMenu();
        cout << endl << "Selecione uma opcao (1-5): ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            cout << "===Vender===" << endl;
            // 
            break;
        case 2:
            cout << "==Comprar==" << endl;
            // 
            break;
        case 3:
            cout << "===Relatorios===" << endl;
            // 
            break;
        case 4:
            cout << "===Gestao de Clientes===" << endl;
            // 
            break;
        case 5:
            break;
        default:
            cout << "Opçao invalida. Por favor, selecione uma opcao valida." << endl;
            break;
        }
    }
    return 0;
}