#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void)
{
    int altura = get_int("Altura: ");
    draw(altura);
}

void draw(int n)
{
    //Utilizando recursão, a função é chamada repetidamente
    // até alcançar esse "caso base" e então "desembrulha"
    // para executar o resto do código
    if (n <= 0)
    {
        return;
    }

    draw(n-1);

    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}