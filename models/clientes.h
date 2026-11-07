#ifndef CLIENTES_H
#define CLIENTES_H

struct clientes {
    int codigo;
    char nome[50];
    double cpf;
    char sexo;
    struct telefones tel;
};

struct telefones
{
    char fixo[16];
    char movel[16];
};

#endif // CLIENTES_H