#include "GerirProduto.h"
#include <fstream>
#include <sstream>

bool GerirProduto::verificaNoCsv(int id, string nome) {
    ifstream arquivo("produtos.csv");
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

void GerirProduto::guardarInformacoes() {
    ofstream arquivo("produtos.csv", ios::out);

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

GerirProduto::GerirProduto() {
    ifstream arquivo("produtos.csv");
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

    arquivo.open("produtos.csv");
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
}

void GerirProduto::adicionarProduto(int id, string nome, int stock, double precoCusto, double iva) {
    if (!verificaNoCsv(id, nome)) {
        Produto* newItem = new Produto[numItem + 1];

        for (int i = 0; i < numItem; i++) {
            newItem[i] = item[i];
        }

        newItem[numItem] = Produto(id, nome, stock, precoCusto, iva);

        if (item != nullptr) {
            delete[] item;
        }
        item = newItem;
        numItem++;

        guardarInformacoes();
    }
    else {
        cout << "ID ou Nome já existem!!\n";
    }
}

void GerirProduto::removerProduto(string nome) {
    bool verificaProduto = false;
    for (int i = 0; i < numItem; i++) {
        if (item[i].getNome() == nome) {
            for (int j = i; j < numItem - 1; j++) {
                item[j] = item[j + 1];
            }
            numItem--;
            verificaProduto = true;
            guardarInformacoes();
            return;
        }
    }
    if (!verificaProduto) {
        cout << "Nao foi encontrado nenhum produto!" << endl;
    }
}

void GerirProduto::modificarProduto(string nome, int novoStock, double novoPrecoCusto, double novoIva) {
    bool verificaProduto = false;
    for (int i = 0; i < numItem; i++) {
        if (item[i].getNome() == nome) {
            item[i].setStock(novoStock);
            item[i].setPrecoCusto(novoPrecoCusto);
            item[i].setIva(novoIva);
            verificaProduto = true;
            cout << "Produto modificado com sucesso!" << endl;
            guardarInformacoes();
            return;
        }
    }
    if (!verificaProduto) {
        cout << "Produto nao encontrado!" << endl;
    }
}

void GerirProduto::mostrarProdutos() {
    for (int i = 0; i < numItem; i++) {
        item[i].mostrarInformacoes();
    }
}

void GerirProduto::obterNomesQuantidades(string*& nomes, int*& quantidades, int& tamanho)
{
    tamanho = numItem;
    nomes = new string[tamanho];
    quantidades = new int[tamanho];

    for (int i = 0; i < numItem; i++) {
        nomes[i] = item[i].getNome();
        quantidades[i] = item[i].getStock();
    }
}

void GerirProduto::dimunirQuantidadeStock(int idProduto,int quantidade) {
    for (int i = 0; i < numItem; i++) {
        if (item[i].getId() == idProduto) {
            int quantidadeAtual = item[i].getStock();

            // Verificar se há stock disponível
            if (quantidadeAtual > 0) {
                // Reduzir a quantidade em 1 (podes ajustar conforme necessário)
                item[i].setStock(quantidadeAtual - quantidade);
                cout << "Quantidade de stock reduzida com sucesso." << endl;

                // Atualizar as informações no arquivo CSV
                guardarInformacoes();
            }
            else {
                cout << "Produto sem stock disponível." << endl;
            }
            return;
        }
    }
    cout << "Produto não encontrado." << endl;
}

int GerirProduto::obterQuantidadeDisponivel(int idProduto) {
    for (int i = 0; i < numItem; i++) {
        if (item[i].getId() == idProduto) {
            // Retorna a quantidade de stock disponível para o produto
            return item[i].getStock();
        }
    }
    // Se o produto não for encontrado, retorna -1 (ou outro valor que indique que o produto não existe)
    return -1;
}
