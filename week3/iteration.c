#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void)
{
    //desenhe um triângulo equilátero de altura N
    int altura = get_int("Altura: ");

    draw(altura);
}


void draw(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}