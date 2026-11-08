#ifndef PRODUTOS_H
#define PRODUTOS_H

struct modelos
{
    char marca[20];
    char modelo[20];
};

struct produtos {
    int codigo;
    struct modelos modelo;
    double valor;
    int quantidade;
};

#endif // PRODUTOS_H