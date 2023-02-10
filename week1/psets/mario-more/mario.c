#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    //Pergunte quantas linhas as pirâmides devem ter ( 0 > n < 9 )
    do{
        height = get_int("Tamanho: ");
    }
    while (height<1 || height>8);


    //Tente criar as pirâmides
    for(int lin=0; lin<height; lin++)
    {
        //Loop invertido para o lado esquerdo? Adiciona espaços regressivamente
        for(int colA=height-1; colA>lin; colA--)
        {
            printf(" ");
        }

        //... E por fim cria os blocos sucessivamente
        for(int hash=0; hash<=lin; hash++)
        {
            printf("#");
        }

        printf("  ");
        //O segredo tá nessa condição
        for(int colB=0; colB<=lin; colB++)
        {
            printf("#");
        }
        printf("\n");
    }

}