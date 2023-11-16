#include "GerirProduto.h"

const string NOME_FICHEIRO = "produtos.csv";

bool GerirProduto::verificaNoCsv(int id, string nome) {
    ifstream arquivo(NOME_FICHEIRO);
    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string idCSV, nomeCSV, stock, precoCusto, iva;
        getline(ss, idCSV, ',');
        getline(ss, nomeCSV, ',');
        getline(ss, stock, ',');
        getline(ss, precoCusto, ',');
        getline(ss, iva, ',');
        if (nomeCSV == nome || idCSV == to_string(id)) {
            return true;
        }
    }
    return false;
}

void GerirProduto::guardaInformacoes() {
    ofstream arquivo(NOME_FICHEIRO, ios::out);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo produtos.csv." << endl;
        return;
    }
    for (int i = 0; i < numItem; i++) {
        arquivo << item[i].getId() << "," << item[i].getNome() << "," << item[i].getStock() << "," << item[i].getPrecoCusto() << "," << item[i].getIva();
        if (i < numItem - 1) {
            arquivo << endl; // Evita uma linha em branco no final
        }
    }
    arquivo.close();
}

void GerirProduto::updateClasseProduto() {

    ifstream arquivo(NOME_FICHEIRO);
    if (!arquivo.is_open()) {
        cout << "Arquivo de produtos não encontrado." << endl;
        numItem = 0;
        item = nullptr;
        return;
    }

    string linha;
    numItem = 0;

    // Ler quantas linhas tem o csv
    while (getline(arquivo, linha)) {
        numItem++;
    }

    arquivo.close();

    item = new Produto[numItem];

    arquivo.open(NOME_FICHEIRO);
    numItem = 0;

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string idCSV, nomeCSV, stock, precoCusto, iva;
        getline(ss, idCSV, ',');
        getline(ss, nomeCSV, ',');
        getline(ss, stock, ',');
        getline(ss, precoCusto, ',');
        getline(ss, iva, ',');

        int id = stoi(idCSV);
        int stockValue = stoi(stock);
        double precoCustoValue = stod(precoCusto);
        double ivaValue = stod(iva);
        item[numItem] = Produto(id, nomeCSV, stockValue, precoCustoValue, ivaValue);
        numItem++;
    }
    arquivo.close();
    guardaInformacoes();
}

GerirProduto::GerirProduto() {
    updateClasseProduto();
}

#pragma region Validacoes


//valida nome
bool GerirProduto::validaNome(string nome){
    if (nome.length() < 3) {
        cout << "Nome invalido! O nome deve ter pelo menos 3 caracteres.\nInsira novamente: ";
        return false;
    }
    for (char c : nome)
    {
        if (isdigit(c))                                                                                     // isdigit verifica se é um digito e retorna true caso seja
        {
            cout << "Nome invalido! O nome deve conter apenas letras.\nInsira novamente: ";
            return false;
        }
    }
    //verifica se ja existe
    if (verificaNoCsv(0, nome)) {
		cout << "Nome invalido! O nome ja existe.\nInsira novamente: ";
		return false;
	}
    return true;
}

//valida stock
bool GerirProduto::validaStock(int stock){
    //verifica se tem letras
    if (cin.fail()) {                                                           // se o cin falhar
		cin.clear();                                                            // limpa o cin
		cin.ignore(1000, '\n');  											    // ignora o que estiver no buffer
		cout << "Stock invalido! O stock deve ser um numero inteiro.\nInsira novamente: ";
		return false;
	}
	if (stock < 0) {
		cout << "Stock invalido! O stock deve ser maior ou igual a 0.\nInsira novamente: ";
		return false;
	}


	return true;
}

//valida preco
bool GerirProduto::validaPreco(double precoCusto){
    if (cin.fail()) {                                                           // se o cin falhar
        cin.clear();                                                            // limpa o cin
        cin.ignore(1000, '\n');  											    // ignora o que estiver no buffer
        cout << "Preco invalido! O preco deve ser um numero.\nInsira novamente: ";
        return false;
    }
    if (precoCusto <= 0) {
		cout << "Preco invalido! O preco deve ser maior que 0.\nInsira novamente: ";
		return false;
	}
	return true;
}

//valida iva
bool GerirProduto::validaIva(double iva){
    if (cin.fail()) {                                                           // se o cin falhar
        cin.clear();                                                            // limpa o cin
        cin.ignore(1000, '\n');  											    // ignora o que estiver no buffer
        cout << "Stock invalido! O stock deve ser um numero inteiro.\nInsira novamente: ";
        return false;
    }
    if (iva < 0) {
		cout << "Iva invalido! O iva deve ser maior ou igual a 0.\nInsira novamente: ";
		return false;
	}
	return true;
}

#pragma endregion

void GerirProduto::adicionarProduto() {
    int id, stock;
    double precoCusto, iva;
    string nome;

    cout << "Nome: ";
    do {
        cin >> nome;
    } while (!validaNome(nome));

    cout << "Stock: ";
    do {
        cin >> stock;
    } while (!validaStock(stock));
    
    cout << "Preco Custo: ";
    do {
        cin >> precoCusto;
    } while (!validaPreco(precoCusto));

    cout << "Iva: ";
    do {
        cin >> iva;
    } while (!validaIva(iva));


    Produto* newitem = new Produto[numItem + 1];
    for (int i = 0; i < numItem; i++) {
        newitem[i] = item[i];
    }
    //ordenar por id
    Produto aux;
    for (int i = 0; i < numItem; i++)
    {
        for (int j = i + 1; j < numItem; j++)
        {
            if (item[i].getId() > item[j].getId())
            {
                aux = item[i];
                item[i] = item[j];
                item[j] = aux;
            }
        }
    }
    //cria id unico que não pode ser alterado mesmo que o cliente seja removido
    if (numItem == 0) {
        id = 1;
    }
    else {
        id = item[numItem - 1].getId() + 1;
    }

    newitem[numItem] = Produto(id, nome, stock, precoCusto, iva);
    if (item != nullptr) {
        delete[] item;
    }
    item = newitem;

    numItem++;
   
    cout << "Produto Adicionado com sucesso!!! \n" ;
    guardaInformacoes();
    updateClasseProduto();
}

void GerirProduto::removerProduto() {
    mostrarProdutos();
    string nome;
    bool existe = false;
    cout << "\n\nIndique o nome do produto a remover: ";
    cin >> nome;
    for (int i = 0; i < numItem; i++){
        if (item[i].getNome() == nome)
        {
            item[i] = item[numItem - 1];
            numItem--;
            existe = true;
            guardaInformacoes();
            updateClasseProduto();
        }
    }
    if (existe == false){
        cout << "Produto nao existe! \n";
    }
    else {
        cout << "Produto removido com sucesso! \n";
    }
}

void GerirProduto::modificarProduto() {
    mostrarProdutos();
    string nome;
    int stock;
    double precoCusto, iva;
    bool existe = false;
    cout << "\n\nInsira o nome do produto que pretende modificar: ";
    cin >> nome;
    for (int i = 0; i < numItem; i++){
        if (item[i].getNome() == nome){
            cout << "Insira os novos dados\nNome: ";
            do {
                cin >> nome;
            } while (!validaNome(nome));

            cout << "Stock: ";
            do {
                cin >> stock;
            } while (!validaStock(stock));

            cout << "Preco Custo ";
            do {
                cin >> precoCusto;
            } while (!validaPreco(precoCusto));

            cout << "Iva: ";
            do {
                cin >> iva;
            } while (!validaIva(iva));

            item[i].setNome(nome);
            item[i].setStock(stock);
            item[i].setPrecoCusto(precoCusto);
            item[i].setIva(iva);
            existe = true;
      
           
        }
    }
    if (existe == false){
        cout << "Produto nao existe! \n";
    }
    else {
        guardaInformacoes();
        updateClasseProduto();
        cout << "Produto modificado com sucesso! \n";
    }
}

void GerirProduto::atualizarStockProduto(){
    mostrarProdutos();
    string nome;
    int stock;
    double precoCusto, iva;
    bool existe = false;
    cout << "\n\nInsira o nome do produto que pretende atulizar o stock: ";
    cin >> nome;
    for (int i = 0; i < numItem; i++){
        if (item[i].getNome() == nome){

            cout << "Stock: ";
            do {
                cin >> stock;
            } while (!validaStock(stock));
            item[i].setStock(stock);
            existe = true;
           
            
        }
    }
    if (existe == false){
        cout << "Produto nao existe! \n";
    }
    else {
        guardaInformacoes();
        updateClasseProduto();
        cout << "Produto modificado com sucesso! \n" ;
    }
}

#pragma region Acesso Exterior da classe

void GerirProduto::mostrarProdutos() {
    cout << "+--------------------------------------------------------------------------------------+\n";
    cout << "|    Informações sobre Produtos Disponíveis                                            |\n";
    cout << "+--------------------------------------------------------------------------------------+\n";
    cout << "|  Id  |     Nome      | Quantidade  | Preço Custo | Preço Venda | IVA | Preço Sem IVA |\n";
    cout << "+--------------------------------------------------------------------------------------+\n";
    for (int i = 0; i < numItem; i++) {
        item[i].mostrarInformacoes();
    }

}

void GerirProduto::produtosComStock(){
    cout << "+------------------------------------------------+\n";;
    cout << "|    Lista de Produtos Disponíveis               |\n";
    cout << "+------------------------------------------------+\n";;
    cout << "|  Id  |     Nome      | Quantidade  |   Preço   |\n";
    cout << "+------------------------------------------------+\n";

    for (int i = 0; i < numItem; i++) {
        if (item[i].getStock() > 0) {
            cout << "| " << setw(4) << item[i].getId() << " | " << setw(14) << item[i].getNome() << " | " << setw(10) << item[i].getStock() << " | " << setw(9) << fixed << setprecision(2) << item[i].calcularPrecoVenda(item[i].getPrecoCusto(), item[i].getIva()) << " |\n";
        }
    }
    cout << "+------------------------------------------------+\n";
}

void GerirProduto::obterNomesQuantidades(string*& nomes, int*& quantidades, int& tamanho){
    tamanho = numItem;
    nomes = new string[tamanho];
    quantidades = new int[tamanho];

    for (int i = 0; i < numItem; i++) {
        nomes[i] = item[i].getNome();
        quantidades[i] = item[i].getStock();
    }

}

bool GerirProduto::verificaProduto(int idProduto){
    for (int i = 0; i < numItem; i++) {
        if (item[i].getId() == idProduto) {
            return true;
        }
    }
    return false;
}

void GerirProduto::dimunirQuantidadeStock(int idProduto,int quantidade) {
    for (int i = 0; i < numItem; i++) {
        if (item[i].getId() == idProduto) {
            int quantidadeAtual = item[i].getStock();
            if (quantidadeAtual > 0) {
                item[i].setStock(quantidadeAtual - quantidade);
                guardaInformacoes(); // Volta  a guardar informaçoes de stock na Ficheiro Produtos.csv
            }
            else {
                cout << "Produto sem stock disponível. \n";
            }
            return;
        }
    }
    cout << "Produto não encontrado. \n";
}

int GerirProduto::obterQuantidadeDisponivel(int idProduto) {
    for (int i = 0; i < numItem; i++) {
        if (item[i].getId() == idProduto) {
            return item[i].getStock();
        }
    }
    return 0;
}

double GerirProduto::obterPrecoProduto(int idProduto){
    for(int i = 0; i < numItem; i++) {
        if (item[i].getId() == idProduto) {
            return item[i].calcularPrecoVenda(item[i].getPrecoCusto(), item[i].getIva());
        }
    }
    return -1;
}

string GerirProduto::obterNomeProduto(int idProduto){
    for (int i = 0; i < numItem; i++) {
        if (item[i].getId() == idProduto) {
            return item[i].getNome();
        }
    }
    return "Nao Existe!";
}

int GerirProduto::obterIvaProduto(int idProduto){
    for (int i = 0; i < numItem; i++) {
        if (item[i].getId() == idProduto) {
            return item[i].getIva();
        }
    }
    return -1;
}

double GerirProduto::obterPrecoSemIva(int idProduto){
    for (int i = 0; i < numItem; i++) {
        if (item[i].getId() == idProduto) {
            return item[i].calcularPrecoSemIva(item[i].getPrecoCusto(), item[i].getIva());
        }
    }
    return -1;
}

#pragma endregion