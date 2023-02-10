#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long x = get_long("X: ");
    long y = get_long("Y: ");

    //Não exibe pontos decimais, truncado.
    //float z = x / y;

    float z = (float) x / (float) y;

    //Imprecisão de ponto flutuante: Não consegue calcular tantos decimais!
    printf("Divisão: %.20f\n", z);
}