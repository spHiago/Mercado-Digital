#include "clientes.h"
#include "produtos.h"

#ifndef CARRINHOS_H //serve so como uma protecao para que o arquivo nao seja incluido mais de uma vez
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