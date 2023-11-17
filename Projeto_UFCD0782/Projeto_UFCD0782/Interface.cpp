#include "Interface.h"


int Interface::converteStringParaInt(string opcaoString) {
	if (opcaoString.size() == 1 && isdigit(opcaoString[0])) {
		return stoi(opcaoString);
	}
	return 0;
}

void Interface::menuProduto(GerirProduto gerirProduto) {
	string opcaoString;
	int opcaoInt;
	do {
		cout << "+----------------------------+\n";
		cout << "|       MENU PRODUTOS        |\n";
		cout << "+----------------------------+\n";
		cout << "|  (1) - Adicionar           |\n";
		cout << "|                            |\n";
		cout << "|  (2) - Remover             |\n";
		cout << "|                            |\n";
		cout << "|  (3) - Modificar           |\n";
		cout << "|                            |\n";
		cout << "|  (4) - Atualizar Stock     |\n";
		cout << "|                            |\n";
		cout << "|  (5) - Listar              |\n";
		cout << "|                            |\n";
		cout << "|  (6) - Sair                |\n";
		cout << "+----------------------------+\n";
		cin >> opcaoString;
		opcaoInt = converteStringParaInt(opcaoString);
		system("CLS");
		switch (opcaoInt) {
		case 1:
			gerirProduto.adicionarProduto();
			system("pause");
			system("CLS");
			break;

		case 2:
			gerirProduto.removerProduto();
			system("pause");
			system("CLS");
			break;

		case 3:
			gerirProduto.modificarProduto();
			system("pause");
			system("CLS");
			break;

		case 4:
			gerirProduto.atualizarStockProduto();
			system("pause");
			system("cls");
			break;

		case 5:
			gerirProduto.mostrarProdutos();
			system("pause");
			system("cls");
			break;

		case 6:
			return;

		default:
			cout << "!!Opcao Invalida!! \n";
			break;
		}

	} while (true);

}

void Interface::menuCliente(Gerecliente gerirCliente) {
	string opcaoString;
	int opcaoInt;
	do {
		cout << "+----------------------------+\n";
		cout << "|       MENU CLIENTES        |\n";
		cout << "+----------------------------+\n";
		cout << "|  (1) - Adicionar           |\n";
		cout << "|                            |\n";
		cout << "|  (2) - Remover             |\n";
		cout << "|                            |\n";
		cout << "|  (3) - Modificar           |\n";
		cout << "|                            |\n";
		cout << "|  (4) - Listar              |\n";
		cout << "|                            |\n";
		cout << "|  (5) - Sair                |\n";
		cout << "+----------------------------+\n";
		cin >> opcaoString;
		opcaoInt = converteStringParaInt(opcaoString);
		system("cls");
		switch (opcaoInt) {
		case 1:
			gerirCliente.adicionaCliente();
			system("pause");
			system("cls");

			break;
		case 2:
			gerirCliente.removeCliente();
			system("pause");	
			system("cls");

			break;
		case 3:
			gerirCliente.modificadadoCliente();
			system("pause");
			system("cls");
			break;

		case 4:
			gerirCliente.listaClientes();
			system("pause");
			system("cls");
			break;

		case 5:
			return;

		default:
			cout << "!!Opcao Invalida!! \n";
			break;
		}

	} while (true);
}

void Interface::menuVenda(GerirVenda gerirVenda) {
	string opcaoString;
	int opcaoInt;
	do {
		cout << "+----------------------------+\n";
		cout << "|       MENU VENDAS          |\n";
		cout << "+----------------------------+\n";
		cout << "|  (1) - Iniciar Venda       |\n";
		cout << "|                            |\n";
		cout << "|  (2) - Sair                |\n";
		cout << "+----------------------------+\n";
		cin >> opcaoString;
		opcaoInt = converteStringParaInt(opcaoString);
		system("cls");
		switch (opcaoInt) {
		case 1:
			gerirVenda.adicionaVenda();
			system("pause");
			system("cls");
			break;

		case 2:
			return;

		default:
			cout << "!!Opção Invalida!! \n";
			break;
		}

	} while (true);
}

void Interface::menuRelatorios(Relatorio relatorio, GerirProduto gerirProduto, GerirVenda GereVenda) {
	string opcaoString;
	int opcaoInt;
	do {
		cout << "+----------------------------+\n";
		cout << "|      MENU Relatorios       |\n";
		cout << "+----------------------------+\n";
		cout << "|  (1) - Stock               |\n";
		cout << "|                            |\n";
		cout << "|  (2) - Sem Stock           |\n";
		cout << "|                            |\n";
		cout << "|  (3) - Relatorio Produto   |\n";
		cout << "|                            |\n";
		cout << "|  (4) - Relatorio Total     |\n";
		cout << "|                            |\n";
		cout << "|  (5) - Sair                |\n";
		cout << "+----------------------------+\n";
		cin >> opcaoString;
		opcaoInt = converteStringParaInt(opcaoString);
		system("cls");
		switch (opcaoInt) {
		case 1:
			relatorio.imprimirNomesQuantidades(); // Chama o método com o objeto GerirProduto
			system("pause");
			system("cls");
			break;

		case 2:
			relatorio.imprimeSemStock(); // Chama o método com o objeto GerirProduto
			system("pause");
			system("cls");
			break;

		case 3:
			GereVenda.imprimeVendaPorProduto();
			system("pause");
			system("cls");
			break;

		case 4:
			relatorio.imprimeMaisMenosVendido(); 
			system("pause");
			system("cls");
			break;

		case 5:
			return;

		default:
			cout << "!!Opcao Invalida!! \n";
			break;
		}

	} while (true);
}

Interface::Interface() {
}

void Interface::menuPrincipal() {
	string opcaoString;
	int opcaoInt;
	GerirProduto gerirProduto;
	Gerecliente gerirCliente;
	GerirVenda gerirVenda;
	Relatorio relatorio;
	do {
		cout << "+----------------------------+\n";
		cout << "|        MENU PRINCIPAL      |\n";
		cout << "+----------------------------+\n";
		cout << "|  (1) - Vender              |\n";
		cout << "|                            |\n";
		cout << "|  (2) - Produtos            |\n";
		cout << "|                            |\n";
		cout << "|  (3) - Clientes            |\n";
		cout << "|                            |\n";
		cout << "|  (4) - Relatorios          |\n";
		cout << "|                            |\n";
		cout << "|  (5) - Sair                |\n";
		cout << "+----------------------------+\n";
		cin >> opcaoString;
		opcaoInt = converteStringParaInt(opcaoString);
		system("cls");
		switch (opcaoInt) {
		case 1:
			menuVenda(gerirVenda);
			system("cls");
			break;
		case 2:
			menuProduto(gerirProduto);
			system("cls");
			break;
		case 3:
			menuCliente(gerirCliente);
			system("cls");
			break;

		case 4:
			menuRelatorios(relatorio, gerirProduto, gerirVenda);
			system("cls");
			break;

		case 5:
			return;

		default:
			cout << "!!Opcao Invalida!! \n";
			break;
		}
	} while (true);
}

