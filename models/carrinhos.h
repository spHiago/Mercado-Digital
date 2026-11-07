#include "clientes.h"
#include "produtos.h"

#ifndef CARRINHOS_H
#define CARRINHOS_H

struct carrinhos {
    struct clientes cliente;
    struct produtos produto[3];
    int quantidade[3];
    double subtotal;
    double desconto;
    double total;
};

#endif // CARRINHOS_H