# Sistema de Gestão de Ponto de Venda (POS)

## Descrição

Este programa em C++ foi desenvolvido para a gestão de uma pequena loja local, fornecendo funcionalidades para várias ações relacionadas a vendas, gestão de estoque, atendimento ao cliente e relatórios. O programa utiliza classes e estruturas para organizar e realizar as tarefas especificadas.

## Classes

1. **Cliente**
   - Representa informações individuais do cliente.
   - Atributos: `id`, `nome`, `numeroTelefone`, `morada`.

2. **GereCliente**
   - Gerencia operações relacionadas ao atendimento ao cliente.
   - Funções: 
     - `criarCliente`: Cria um novo cliente.
     - `eliminarCliente`: Remove um cliente (garante que não haja espaços vazios na estrutura).
     - `alterarNomeCliente`: Modifica o nome do cliente.

3. **Produto**
   - Representa informações sobre um produto em estoque.
   - Atributos: `id`, `quantidade`, `nome`, `precoCusto`.

4. **GerirProduto**
   - Gerencia operações relacionadas ao gerenciamento de produtos.
   - Funções:
     - `criarArtigo`: Cria um novo produto.
     - `adicionarStock`: Adiciona estoque a um produto existente.
     - `eliminarProduto`: Exclui um produto.

5. **Venda**
   - Representa informações sobre uma venda..

6. **GerirVenda**
   - Gerencia operações relacionadas a vendas.
   - Funções:
     - `efetuarVenda`: Processa uma venda.
     - `criarCompraStock`: Cria uma compra para o estoque.
     - `criarRelatorioStock`: Gera um relatório de estoque.
     - `criarRelatorioVendasProduto`: Gera um relatório de vendas para um produto específico.
     - `criarRelatorioTotalVendas`: Gera um relatório total de vendas com:
       - Produto mais vendido.
       - Produto menos vendido.
       - Produto mais lucrativo.
       - Melhor cliente.

7. **Interface**
   - Gerencia a interface do usuário e entrada/saída.

8. **Relatorio**
   - Gerencia funcionalidades de relatórios.

## Recursos Adicionais

- Inserção automática de valores padrão.
- Inserção automática de data nos recibos.
- Validação para evitar ações impróprias (por exemplo, estoque negativo, venda de produtos fora de estoque, criação de produtos duplicados).
- O estoque é atualizado automaticamente durante transações de compra e venda.
- Periodicamente, um cliente sortudo recebe uma compra gratuita.

## Como Usar

1. Compile e execute o programa em C++.
2. Siga o menu na tela para diferentes ações.
3. Após cada ação, o programa retorna ao menu inicial.

## Licença

Este programa é distribuído sob a Licença MIT, concedendo aos usuários a liberdade de usar, modificar e distribuir o software. Contribuições são bem-vindas por meio de issues ou pull requests.

## Agradecimentos

Obrigado por considerar contribuir para o desenvolvimento deste Sistema de Gestão de Ponto de Venda. Sua colaboração é essencial para o sucesso desta aplicação.
