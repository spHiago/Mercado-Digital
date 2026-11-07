#include <stdio.h>
#include <string.h>

#include "models/clientes.h"
#include "models/produtos.h"
#include "models/carrinhos.h"

void mostraMenuInicial()
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

int main()
{

    struct clientes cliente[3];
    struct produtos produto[3];
    struct carrinhos carrinho[3];

    int opcao;

    do
    {
        mostraMenuInicial();
        scanf("%d", &opcao);

        switch (opcao)
        {

        case 1:
            printf("\n===== CADASTRO DE CLIENTE =====\n");
            break;

        case 2:
            printf("\n===== CADASTRO DE PRODUTO =====\n");
            break;

        case 3:
            printf("\n===== LISTA DE CLIENTES =====\n");
            break;

        case 4:
            printf("\n===== LISTA DE PRODUTOS =====\n");
            break;

        case 5:
            printf("\n===== EFETUAR VENDA =====\n");
            break;

        case 0:
            printf("\nSaindo do programa...\n");
            break;

        default:
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}