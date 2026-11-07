#ifndef PRODUTOS_H
#define PRODUTOS_H

struct produtos {
    int codigo;
    struct modelos modelo;
    double valor;
    int quantidade;
};

struct modelos
{
    char marca[20];
    char modelo[20];
};

#endif // PRODUTOS_H