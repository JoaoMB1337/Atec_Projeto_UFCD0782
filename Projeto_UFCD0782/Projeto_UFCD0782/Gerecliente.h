#pragma once
#include "cliente.h"
#include <string>
class Gerecliente
{
	private:

	#pragma region Validacoes 
		bool validaEmail(string email);
		bool validaNome(string nome);
		bool validaNif(string nif);
		bool validaTelefone(string telefone);
		bool verificaNif(string nif);
		bool verificaEmail(string email);
	#pragma endregion

		void guardaInformacoes();
		Cliente* pessoa;
		int contador;
		int id = 1;

	public:

		Gerecliente();
		void adicionaCliente();
		void removeCliente();
		void modificadadoCliente();
		void listaClientes();
		bool verificaCliente(int idCliente);

};
