#pragma once
#include "cliente.h"
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iomanip>

class Gerecliente
{
	private:
		bool validaEmail(string email);
		bool validaNome(string nome);
		bool validaNif(string nif);
		bool validaTelefone(string telefone);
		bool verificaNif(string nif);
		bool verificaEmail(string email);
		void guardaInformacoes();
		Cliente* pessoa;
		int contador;
		int id = 1;

	public:
		Gerecliente();
		void updateClasseCliente();
		void adicionaCliente();
		void removeCliente();
		void modificadadoCliente();
		void listaClientes();
		bool verificaCliente(int idCliente);
		string obterNomeCliente(int idCliente);
		void mostrarCliente();

};
