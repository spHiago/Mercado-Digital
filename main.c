#include <stdio.h>
#include <string.h>  // Inclui a biblioteca de manipulação de strings, como strcpy e strlen
#include <windows.h> // Só pra eu usar o sleep()

#include "models/clientes.h"  // Inclui o arquivo de cabeçalho "clientes.h" que contém a definição da estrutura "clientes"
#include "models/produtos.h"  // Inclui o arquivo de cabeçalho "produtos.h" que contém a definição da estrutura "produtos"
#include "models/carrinhos.h" // Inclui o arquivo de cabeçalho "carrinhos.h" que contém a definição da estrutura "carrinhos"

int geraCodigoCliente(double cpf); // O codigo do cliente sao os 6 primeiros digitos do cpf

void mostraMenuInicial() // Função que exibe o menu inicial do programa ("void" indica que a função não retorna nenhum valor")
{
    printf("\n===== MERCADO DIGITAL =====\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Cadastrar produto\n");
    printf("3 - Listar clientes\n");
    printf("4 - Listar produtos\n");
    printf("5 - Efetuar venda\n");
    printf("0 - Sair\n");
    printf("===========================\n");
    printf("Escolha uma opcao: ");
}

void listarClientes(struct clientes cliente[3], int qtdClientes) // Função que lista os clientes kkk
{
    int i;

    for (i = 0; i < qtdClientes; i++)
    {
        printf("\n===== CLIENTE %d =====\n", i + 1);
        printf("Nome: %s\n", cliente[i].nome);
        printf("CPF: %.0f\n", cliente[i].cpf);
        printf("Codigo: %d\n", cliente[i].codigo);
        printf("Sexo: %c\n", cliente[i].sexo);
        printf("Telefone fixo: %s\n", cliente[i].tel.fixo);
        printf("Telefone movel: %s\n", cliente[i].tel.movel);
    }
}

void listarProdutoss(struct produtos produto[10], int qtdProdutos)
{
    int i;

    for (i = 0; i < qtdProdutos; i++)
    {
        printf("\n===== PRODUTO %d =====\n", i + 1);
        printf("Marca: %s\n", produto[i].modelo.marca);
        printf("Modelo: %s\n", produto[i].modelo.modelo);
        printf("Codigo: %d\n", produto[i].codigo);
        printf("Valor: %.2lf\n", produto[i].valor);
        printf("Quantidade: %d\n", produto[i].quantidade);
    }
}

void efetuarVenda(struct clientes cliente[3], struct produtos produto[10], struct carrinhos carrinho, int qtdClientes, int qtdProdutos);

struct clientes cadastrarCliente()
{                                // só declarei uma função
    struct clientes novoCliente; // uma variável capaz de armazenar os dados do cliente

    printf("Digite o nome: ");
    scanf(" %49[^\n]", novoCliente.nome); // esse "%49[^\n]"" permite ler até 49 caracteres, incluindo espaços

    printf("Digite o CPF: ");
    scanf("%lf", &novoCliente.cpf);                          //%lf é pra double, o ideal seria &s, mas o prof quer o cpf como double
    novoCliente.codigo = geraCodigoCliente(novoCliente.cpf); // calma calabreo, expliquei abaixo.

    printf("Digite o sexo (M/F): ");
    scanf(" %c", &novoCliente.sexo); //%c para char

    printf("Digite o telefone fixo: ");
    scanf(" %14[^\n]", novoCliente.tel.fixo);

    printf("Digite o telefone móvel: ");
    scanf(" %15[^\n]", novoCliente.tel.movel);

    return novoCliente; // retorna nosso novo cliente
}

struct produtos cadastrarProduto()
{
    struct produtos novoProduto; // uma variável capaz de armazenar os dados do produto

    printf("Digite a marca do produto: ");
    scanf(" %19[^\n]", novoProduto.modelo.marca);

    printf("Digite o modelo do produto: ");
    scanf(" %19[^\n]", novoProduto.modelo.modelo);

    printf("Digite o valor do produto: ");
    scanf("%lf", &novoProduto.valor);

    printf("Digite a quantidade do produto: ");
    scanf("%d", &novoProduto.quantidade);

    char nomeProduto[5]; // pra gerar o codigo do produto, q sao 4 caracteres + o '\0'

    nomeProduto[0] = novoProduto.modelo.marca[0];  // C1
    nomeProduto[1] = novoProduto.modelo.marca[1];  // C2
    nomeProduto[2] = novoProduto.modelo.modelo[0]; // C3
    nomeProduto[3] = novoProduto.modelo.modelo[1]; // C4
    nomeProduto[4] = '\0';                         // Adiciona o caractere nulo para indicar o final da string

    novoProduto.codigo = geraCodigoProduto(nomeProduto); // chama a função que gera o codigo do produto

    return novoProduto;
}

struct clientes localizaCliente(int codigo, struct clientes cliente[3], int qtdClientes)
{
    int i;

    for (i = 0; i < qtdClientes; i++)
    {
        if (cliente[i].codigo == codigo)
        {
            return cliente[i];
        }
    }

    struct clientes clienteNaoEncontrado = {0}; // Retorna um cliente com código 0 para indicar que não foi encontrado
    return clienteNaoEncontrado;
};

struct produtos localizaProduto(int codigo, struct produtos produto[10], int qtdProdutos)
{
    int i;

    for (i = 0; i < qtdProdutos; i++)
    {
        if (produto[i].codigo == codigo)
        {
            return produto[i];
        }
    }

    struct produtos produtoNaoEncontrado = {0}; // Retorna um produto com código 0 para indicar que não foi encontrado
    return produtoNaoEncontrado;
}

/*o prof quer só o 6 primeiros digitos do cpf,
entao quando o usuario digitar os 11 digito do cpf, dividir por 100000,
dai a virgula vai andar 5 casas para a esquerda, e o tipo int so vai pegar os 6 digitos do cpf.*/
int geraCodigoCliente(double cpf)
{
    int codigo;

    codigo = cpf / 100000;
    return codigo;
}

/* O prof determinou uma formula pra gerar o código do produto usando os dois primeiros caracteres
da marca e os dois do primeiro modelo.

Por exemplo, DELL + PRECISION:
- C1 = D (68) //esses numeros sao os valores da tabela ASCII
- C2 = E (69)
- C3 = P (80)
- C4 = R (82)


formula hash =
68 × 31^3 + 69 × 31^2 + 80 × 31^1 + 82 × 31^0 =
68 × 29791 + 69 × 961 + 80 × 31 + 82 × 1 =
2029948 + 66209 + 2480 + 82 =
2094659 (codigo do produto)
*/
int geraCodigoProduto(char nomeProduto[30])
{
    int codigo;

    codigo = nomeProduto[0] * 29791 + nomeProduto[1] * 961 + nomeProduto[2] * 31 + nomeProduto[3] * 1;

    return codigo;
}

struct produtos localizaProduto(int codigo, struct produtos produto[50], int qtdProdutos)
{
    int i;

    for (i = 0; i < qtdProdutos; i++)
    {
        if (produto[i].codigo == codigo)
        {
            return produto[i];
        }
    }

    struct produtos produtoNaoEncontrado = {0}; // Retorna um produto com código 0 para indicar que não foi encontrado
    return produtoNaoEncontrado;
}

void efetuarVenda(struct clientes cliente[3], struct produtos produto[10], struct carrinhos carrinho, int qtdClientes, int qtdProdutos)
{
    int codigoCliente;
    carrinho.subtotal = calculaSubtotal(carrinho);
    carrinho.total = calculaTotal(carrinho.subtotal, carrinho.desconto);
    carrinho.desconto = 0;
    struct produtos produtoEncontrado;

    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigoCliente);

    struct clientes clienteEncontrado;
    clienteEncontrado = localizaCliente(codigoCliente, cliente, qtdClientes);

    if (clienteEncontrado.codigo == 0)
    {
        printf("Cliente nao encontrado!\n");
        return;
    }

    printf("Cliente encontrado: %s\n", clienteEncontrado.nome);

    int qtdItens = 0;
    int codigoProduto;
    int quantidade;

    while (qtdItens < 3)
    {
        printf("Digite o codigo do produto (ou 0 para finalizar): ");
        scanf("%d", &codigoProduto);

        if (codigoProduto == 0)
            break;

        produtoEncontrado = localizaProduto(codigoProduto, produto, qtdProdutos);

        if (produtoEncontrado.codigo == 0)
        {
            printf("Produto nao encontrado!\n");
            continue;
        }

        printf("Produto: %s %s\n",
               produtoEncontrado.modelo.marca,
               produtoEncontrado.modelo.modelo);
        printf("Quantidade desejada: ");
        scanf("%d", &quantidade);

        if (quantidade <= 0 || quantidade > produtoEncontrado.quantidade)
        {
            printf("Quantidade indisponivel! Estoque atual: %d\n", produtoEncontrado.quantidade);
            continue;
        }

        carrinho.cliente = clienteEncontrado;           // começamos a mexer no carrinho, adicionando nosso cliente
        carrinho.produto[qtdItens] = produtoEncontrado; // adicionando o produto no carrinho
        carrinho.quantidade[qtdItens] = quantidade;     // adicionando a quantidade do produto no carrinho

        qtdItens++;
    }
}

double calculaSubtotal(struct carrinhos carrinho) // funçao q calcula o valor do carrinho
{
    double subtotal = 0;

    for (int i = 0; i < 3; i++)
        subtotal += carrinho.produto[i].valor * carrinho.quantidade[i];

    return subtotal;
}

double calculaTotal(double subtotal, double desconto) //calcula o total com desconto
{
    double valorDesconto = subtotal * desconto / 100;
    double total = subtotal - valorDesconto;

    return total;
}

int main()
{

    struct clientes cliente[3];         // iniciando a estrutura de clientes com um array de 3 elementos
    struct produtos produto[10];        // iniciando a estrutura de produtos com um array de 10 elementos
    struct carrinhos carrinho;          // iniciando a estrutura de carrinhos
    struct produtos cadastrarProduto(); // só declarei uma função

    int opcao;
    int qtdClientes = 0;
    int qtdProdutos = 0;

    do
    {
        mostraMenuInicial(); // chama a função que exibe o menu inicial
        scanf("%d", &opcao);

        switch (opcao)
        {

        case 1: // Cadastro de cliente
            printf("\n===== CADASTRO DE CLIENTE =====\n");
            if (qtdClientes < 3)
            {
                cliente[qtdClientes] = cadastrarCliente();
                qtdClientes++;
            }
            else
                printf("Limite de clientes atingido!\n");
            break;

        case 2: // Cadastro de produto
            printf("\n===== CADASTRO DE PRODUTO =====\n");
            if (qtdProdutos < 10)
            {
                produto[qtdProdutos] = cadastrarProduto();
                qtdProdutos++;
            }
            else
                printf("Limite de produtos atingido!\n");
            break;

        case 3: // Listagem de clientes
            printf("\n===== LISTA DE CLIENTES =====\n");
            listarClientes(cliente, qtdClientes); // a função que criamos la em cima, prof que pediu pra chamar função
            printf("\nPressione ENTER para continuar...");
            getchar();  // Limpa o buffer do teclado (aquele /n que fica sobrando do scanf)
            getchar();  // Pra esperar o usuário apertar ENTER antes de voltar ao menu
            Sleep(500); // Pausa de 0.5 segundos antes de voltar ao menu
            break;

        case 4: // Listagem de produtos
            printf("\n===== LISTA DE PRODUTOS =====\n");
            listarProdutoss(produto, qtdProdutos); // a função que criamos la em cima
            printf("\nPressione ENTER para continuar...");
            getchar();
            getchar();
            Sleep(500);
            break;

        case 5: // Efetuar venda
            printf("\n===== EFETUAR VENDA =====\n");
            efetuarVenda(cliente, produto, carrinho, qtdClientes, qtdProdutos);
            break;

        case 0: // Sair do programa
            printf("\nSaindo do programa...\n");
            break;

        default: // Opção inválida
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}