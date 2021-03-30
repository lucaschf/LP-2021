#include "Imposto.h"

const float Imposto::TAXA_IR_15 = 15;
const float Imposto::TAXA_IR_17_5 = 17.5;
const float Imposto::TAXA_IR_20 = 20;
const float Imposto::TAXA_IR_22_5 = 22.5;

Imposto::Imposto()
{
    setImposto(0);
}

Imposto::Imposto(float valor)
{
    setImposto(valor);
}

Imposto& Imposto::setImposto(float valor)
{
    this->valor = valor;
    return *this;
}

float Imposto::getImposto()
{
    return this->valor;
}
