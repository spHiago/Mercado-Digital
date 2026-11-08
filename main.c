#include <stdio.h>
#include <string.h> // Inclui a biblioteca de manipulação de strings, como strcpy e strlen

#include "models/clientes.h"  // Inclui o arquivo de cabeçalho "clientes.h" que contém a definição da estrutura "clientes"
#include "models/produtos.h"  // Inclui o arquivo de cabeçalho "produtos.h" que contém a definição da estrutura "produtos"
#include "models/carrinhos.h" // Inclui o arquivo de cabeçalho "carrinhos.h" que contém a definição da estrutura "carrinhos"

int geraCodigoCliente(double cpf); //O codigo do cliente sao os 6 primeiros digitos do cpf

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
struct clientes cadastrarCliente()
{                                // só declarei uma função
    struct clientes novoCliente; // uma variável capaz de armazenar os dados do cliente

    printf("Digite o nome: ");
    scanf(" %49[^\n]", novoCliente.nome); // esse "%49[^\n]"" permite ler até 49 caracteres, incluindo espaços

    printf("Digite o CPF: ");
    scanf("%lf", &novoCliente.cpf);  //%lf é pra double, o ideal seria &s, mas o prof quer o cpf como double
    novoCliente.codigo = geraCodigoCliente(novoCliente.cpf); // calma calabreo, expliquei abaixo.

    printf("Digite o sexo (M/F): ");
    scanf(" %c", &novoCliente.sexo); //%c para char

    printf("Digite o telefone fixo: ");
    scanf(" %14[^\n]", novoCliente.tel.fixo);

    printf("Digite o telefone móvel: ");
    scanf(" %15[^\n]", novoCliente.tel.movel);

    return novoCliente; // retorna nosso novo cliente
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

int main()
{

    struct clientes cliente[3];   // iniciando a estrutura de clientes com um array de 3 elementos
    struct produtos produto[10];   // iniciando a estrutura de produtos com um array de 10 elementos
    struct carrinhos carrinho; // iniciando a estrutura de carrinhos

    int opcao;
    int qtdClientes = 0;

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
            break;

        case 3: // Listagem de clientes
            printf("\n===== LISTA DE CLIENTES =====\n");
            listarClientes(cliente, qtdClientes); //a função que criamos la em cima, prof que pediu pra chamar função
            break;

        case 4: // Listagem de produtos
            printf("\n===== LISTA DE PRODUTOS =====\n");
            break;

        case 5: // Efetuar venda
            printf("\n===== EFETUAR VENDA =====\n");
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