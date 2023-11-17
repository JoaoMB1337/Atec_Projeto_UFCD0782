#include "GerirVenda.h"


const string NOME_FICHEIRO = "venda.csv";
const int MAX_ID_VENDA = 100;

void GerirVenda::updatingClasses(){
	produtos.updateClasseProduto();
	clientes.updateClasseCliente();
}

int GerirVenda::converterStringToInt(string str){
	try {
		int strToInt = stoi(str);
		return strToInt;
	}
	catch (invalid_argument&) {
		return -2;
	}
}

double GerirVenda::converterStringToDouble(string str){
	try {
		double strToDouble = stod(str);
		return strToDouble;
	}
	catch (invalid_argument&) {
		return -2;
	}
}

void GerirVenda::updateClasseVenda(){
	ifstream arquivo(NOME_FICHEIRO);
	if (!arquivo.is_open()) {
		ofstream novoArquivo(NOME_FICHEIRO, ios::out); //cria o ficheiro caso nao exista
		contador = 0;
		venda = nullptr;
		return;
	}
	string linha;
	contador = 0;
	// Conta quantas linhas tem o CSV
	while (getline(arquivo, linha)) {
		contador++;
	}
	arquivo.close();
	venda = new Venda[contador];
	arquivo.open(NOME_FICHEIRO);
	contador = 0;
	while (getline(arquivo, linha)) {
		stringstream ss(linha);
		string idClienteCSV, idProdutoCSV, quantidadeCSV, idVendaCSV, dataCSV, totalCSV, valorEntregueCSV, trocoCSV, sorteioCSV;
		getline(ss, idClienteCSV, ';');
		getline(ss, idProdutoCSV, ';');
		getline(ss, quantidadeCSV, ';');
		getline(ss, idVendaCSV, ';');
		getline(ss, dataCSV, ';');
		getline(ss, totalCSV, ';');
		getline(ss, valorEntregueCSV, ';');
		getline(ss, trocoCSV, ';');
		getline(ss, sorteioCSV, ';');

		int idCliente = stoi(idClienteCSV);
		int idProduto = stoi(idProdutoCSV);
		int quantidade = stoi(quantidadeCSV);
		int idVenda = stoi(idVendaCSV);
		double total = stod(totalCSV);
		double valorEntregue = stod(valorEntregueCSV);
		double troco = stod(trocoCSV);
		bool sorteio = stoi(sorteioCSV);
		venda[contador] = Venda(idCliente, idProduto, quantidade, idVenda, dataCSV, total, valorEntregue, troco, sorteio);
		contador++;
	}
	arquivo.close();
}

string GerirVenda::obterHora() {
	time_t agora = time(0);
	struct tm dataHora;
	localtime_s(&dataHora, &agora);

	char data[20];
	strftime(data, 20, "%d/%m/%Y %H:%M:%S", &dataHora);

	return string(data);
}

bool GerirVenda::gerarSorteio(int idCompra){
	srand(time(NULL));
	int numeroSorteio = rand() % 100 + 1;
	if (numeroSorteio == idCompra) {
		cout << "\n\n Parabens! A sua compra foi sorteada.\n"
			<< " Nao precisa pagar a conta.\n\n";
			return true;
	}
	else {
		cout << "\n\n Infelizmente, a sua compra nao foi sorteada.\n"
			<< " Lembre-se de pagar a conta.\n\n";
		return false;
	}
}

int GerirVenda::obterUltimoIdVenda(){
	int ultimoIdVenda = 0;
	ifstream arquivoLeitura(NOME_FICHEIRO);

	if (arquivoLeitura.is_open()) {
		// Encontrar o �ltimo ID de venda
		string linha;
		while (getline(arquivoLeitura, linha)) {
			stringstream ss(linha);
			string idClienteCSV, idProdutoCSV, quantidadeCSV, idVendaCSV, dataCSV, totalCSV, valorEntregueCSV, trocoCSV, sorteioCSV;

			getline(ss, idClienteCSV, ';');
			getline(ss, idProdutoCSV, ';');
			getline(ss, quantidadeCSV, ';');
			getline(ss, idVendaCSV, ';');
			getline(ss, dataCSV, ';');
			getline(ss, totalCSV, ';');
			getline(ss, valorEntregueCSV, ';');
			getline(ss, trocoCSV, ';');
			getline(ss, sorteioCSV, ';');

			int idVenda = stoi(idVendaCSV);
			if (idVenda > ultimoIdVenda) {
				ultimoIdVenda = idVenda;
			}
		}
		arquivoLeitura.close();
	}
	return ultimoIdVenda;
}

int GerirVenda::encontrarClientePorIdVenda(int idcompra){
	for (int i = 0; i < contador; i++) {
		if (venda[i].getIdVenda() == idcompra) {
			 return venda[i].getIdCliente();
			break;
		}
	}
}

bool GerirVenda::encontrarSorteioPorIdVenda(int idcompra){
	for (int i = 0; i < contador; i++) {
		if (venda[i].getIdVenda() == idcompra) {
			if (venda[i].getSorteio()) {
				return true;
			}
		}
	}
	return false;
}

GerirVenda::GerirVenda(){
	updateClasseVenda(); // Fun�ao usada para preencher a classe venda quando o programa for atulizado
}

void GerirVenda::imprimirTalao(int idcompra) {
	int numeroCliente = encontrarClientePorIdVenda(idcompra);
	double totalSemIVA = 0,totalComIVA = 0,valorEntregue = 0,valorTroco = 0;
	int numeroLinha = 1;
	bool sorteioEncontrado = encontrarSorteioPorIdVenda(idcompra);

	cout << setw(40) << right << "Talao da Fatura - Numero: " << idcompra << "\n";
	cout << setw(40) << right << "+--------------------------------------------------------------+\n";
	cout << setw(40) << right << "Numero Cliente: " << numeroCliente << "\n";
	cout << setw(40) << right << "+--------------------------------------------------------------+\n";
	cout << setw(4) << right << "| No |" << right << "Nome Produto" << setw(15) << right << " | Quantidade |"
		<< setw(12) << right << "Preco s/IVA |" << right << "IVA |" << setw(10) << right << "Total C/IVA |\n";
	cout << setw(40) << right << "+--------------------------------------------------------------+\n";

	for (int i = 0; i < contador; i++) {
		if (venda[i].getIdVenda() == idcompra) {
			if (venda[i].getIdProduto() != -1) {
				cout << "|" << setw(3) << numeroLinha << " | " << setw(11) << produtos.obterNomeProduto(venda[i].getIdProduto())
					<< " | " << setw(10) << venda[i].getQuantidade() << " | " << setw(10) << produtos.obterPrecoSemIva(venda[i].getIdProduto())
					<< " | " << setw(5) << produtos.obterIvaProduto(venda[i].getIdProduto()) << "% | " << setw(9) << venda[i].getTotal() << " |\n";

				totalSemIVA += venda[i].getQuantidade() * produtos.obterPrecoSemIva(venda[i].getIdProduto());
				totalComIVA += venda[i].getTotal();
				numeroLinha++;
			}
			else {
				valorEntregue = venda[i].getValorEntrege();
				valorTroco = venda[i].getTroco();
			}
		}
	}

	if (!sorteioEncontrado) {
		cout << setw(40) << right << "+--------------------------------------------------------------+\n";
		cout << setw(40) << "Total s/IVA:" << setw(14) << totalSemIVA << setw(11) << "|\n";
		cout << setw(40) << "Total c/IVA:" << setw(14) << totalComIVA << setw(11) << "|\n";
		cout << setw(40) << "Valor Entregue:" << setw(14) << valorEntregue << setw(11) << "|\n";
		cout << setw(40) << "Troco:" << setw(14) << valorTroco << setw(11) << "|\n";
		cout << setw(40) << right << "+--------------------------------------------------------------+\n";
	}
	else {
		cout << setw(40) << right << "+--------------------------------------------------------------+\n";
		cout << setw(40) << "Esta venda foi sorteada!!\n";
		cout << setw(40) << right << "+--------------------------------------------------------------+\n";
	}
}

void GerirVenda::adicionaVenda() {
	updatingClasses();
	string IdClienteString, idProdutoString, quantidadeString, quantiaEntregueString;
	int idCliente, idProduto, quantidade = 0;
	string dataCSV = obterHora();
	double totalQuantia = 0, totalCompra = 0, quantiaEntregue = 0, troco = 0;
	int ultimoIdVenda = obterUltimoIdVenda();
	bool resultadoSorteio = false;

	if (ultimoIdVenda >= MAX_ID_VENDA) {
		cout << "Limite de vendas atingido. O conteudo do arquivo sera apagado.\n";
		ofstream arquivo(NOME_FICHEIRO, ios::trunc);
		arquivo.close();
		contador = 0;
		return;
	}

	// Verifica se idCliente é igual ao id de algum cliente guardado na classe
	clientes.mostrarCliente();
	do {
		cout << "ID Cliente: ";
		cin >> IdClienteString;
		idCliente = converterStringToInt(IdClienteString);
	} while (!clientes.verificaCliente(idCliente));

	ofstream arquivo(NOME_FICHEIRO, ios::app);
	if (!arquivo.is_open()) {
		cout << "Erro ao abrir o arquivo venda.csv." << endl;
		return;
	}

	resultadoSorteio = gerarSorteio(ultimoIdVenda);
	produtos.produtosComStock();

	// Loop para adicionar produtos à venda
	do {
		cout << "ID Produto (insira 0 para encerrar a compra): ";

		cin >> idProdutoString;
		idProduto = converterStringToInt(idProdutoString);
		if (idProduto != 0 || !produtos.verificaProduto(idProduto) ) {
			// Verifica se idProduto é igual ao id do produto Produtos.csv
			if (!produtos.verificaProduto(idProduto)) {
				cout << "ID Produto invalido. Tente novamente.\n";
				continue;
			}

			if (produtos.obterQuantidadeDisponivel(idProduto) == 0){
				cout << "Produto inserido sem stock!!\n";
				continue;
			}

			cout << "Quantidade: ";
			cin >> quantidadeString;
			quantidade=converterStringToInt(quantidadeString);
			while (quantidade > produtos.obterQuantidadeDisponivel(idProduto)) {
				cout << "Quantidade Indisponivel. Tente Novamente!!\n";
				cout << "Quantidade: ";
				cin >> quantidade;
			}

			if (quantidade > 0) {
				produtos.dimunirQuantidadeStock(idProduto, quantidade);
				totalQuantia = (produtos.obterPrecoProduto(idProduto) * quantidade);
				totalCompra = totalCompra + totalQuantia;
				// Adiciona o produto à venda no arquivo CSV
				arquivo << idCliente << ";" << idProduto << ";" << quantidade << ";" << ultimoIdVenda + 1 << ";"
					<< dataCSV << ";" << totalQuantia << ";" << quantiaEntregue << ";" << troco << ";" << resultadoSorteio << endl;
			}
			contador++; // Incrementa o contador
		}
	} while (idProduto != 0);

	if (totalCompra > 0 && !resultadoSorteio) {
		cout << "Total da Compra: " << totalCompra << "\n";

		do {
			cout << "Valor entregue: ";
			cin >> quantiaEntregueString;

			while (!converterStringToDouble(quantiaEntregueString) > totalCompra) {
				cout << "Valor invalido. Insira um valor igual ou superior ao total da compra: ";
				cin >> quantiaEntregueString;
			}

			quantiaEntregue = stod(quantiaEntregueString);
			troco = quantiaEntregue - totalCompra;
			if (troco < 0) {
				troco = 0;
			}
			arquivo << idCliente << ";" << -1 << ";" << -1 << ";" << ultimoIdVenda + 1 << ";"
				<< dataCSV << ";" << totalCompra << ";" << quantiaEntregue << ";" << troco << ";" << resultadoSorteio << endl;
		} while (quantiaEntregue < totalCompra);
	}

	arquivo.close();
	ultimoIdVenda++;
	system("cls");
	updateClasseVenda();
	imprimirTalao(ultimoIdVenda);
	arquivo.close();
}

void GerirVenda::imprimeVendaPorProduto() {
	string nomeProduto;
	bool encontrou = false;
	cout << "Insira o nome do produto: ";
	cin >> nomeProduto;

	cout << "+-----------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                                              Relatorio de Vendas por Produto                                    |\n";
	cout << "+-----------------------------------------------------------------------------------------------------------------+\n";
	cout << "| ID Cliente | ID Produto | Quantidade | ID Venda | Data               | Total         | Valor Entrege  | Troco   |\n";
	cout << "+-----------------------------------------------------------------------------------------------------------------+\n";

	for (int i = 0; i < contador; ++i) {
		if (nomeProduto == produtos.obterNomeProduto(venda[i].getIdProduto())) {
			venda[i].mostrarVendas();
			cout << "+-----------------------------------------------------------------------------------------------------------------+\n";
			encontrou = true;
		}
	}
	if (!encontrou) {
		cout << "Nenhuma venda encontrada para o produto: " << nomeProduto << endl;
	}
}

int GerirVenda::produtoComMaiorLucro(){
	if (contador == 0) {
		cout << "Nenhuma venda realizada ainda. \n";
		return -1;
	}

	double maiorLucro = -1;
	int idProdutoMaiorLucro = -1;

	for (int i = 0; i < contador; ++i) {
		int idProduto = venda[i].getIdProduto();
		int quantidade = venda[i].getQuantidade();

		if (idProduto != -1) {
			double precoVenda = produtos.obterPrecoProduto(idProduto);
			double precoCusto = produtos.obterPrecoSemIva(idProduto);
			double lucro = venda[i].calcularLucro(precoVenda, precoCusto, quantidade);

			if (lucro > maiorLucro) {
				maiorLucro = lucro;
				idProdutoMaiorLucro = idProduto;
			}
		}
	}

	if (idProdutoMaiorLucro != -1) {
		return idProdutoMaiorLucro;
	}
	else {
		cout << "Nenhum produto encontrado. \n" ;
		return -1;
	}
}
