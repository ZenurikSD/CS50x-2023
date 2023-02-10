#include <cs50.h>
#include <stdio.h>

int fatorial(int n);

int main(void)
{
    long result = fatorial(get_int("Número :"));

    printf("Resultado %li\n", result);
}

int fatorial(int n)
{
    // int x = 1;

    // if (n <= 0)
    // {
    //     return x;
    // }

    // x = fatorial(n-1);

    // return x * n;


    //Implementação do curso
    if (n == 1)
        return 1;
    else
        return n * fatorial(n-1);
}