#ifndef CLIENTES_H
#define CLIENTES_H


struct telefones
{
    char fixo[15];
    char movel[16];
};

struct clientes {
    int codigo;
    char nome[50];
    double cpf;
    char sexo;
    struct telefones tel;
};

#endif // CLIENTES_H