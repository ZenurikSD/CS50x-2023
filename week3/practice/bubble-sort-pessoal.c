#include <stdio.h>

int main(void)
{
    int size = 10;
    int desordenados[] = {8, 7, 6, 6, 5, 4, 9, 3, 2, 1};


    //Algoritmo -------------------------------
    int unsorted_count = size;
    int aux = 0;

    //só faz sentido testar até esse ponto para otimizar o for
    while (unsorted_count > 1)
    {
        for (int i = 0; i < unsorted_count - 1; i++)
        {
            if (desordenados[i] > desordenados[i+1])
            {
                aux = desordenados[i+1];
                desordenados[i+1] = desordenados[i];
                desordenados[i] = aux;
            }
        }
        unsorted_count --;
    }


    // Saída -------------------------------------
    printf("Crescente? \n");

    for (int i = 0; i < size; i++)
    {
        printf("%i ", desordenados[i]);
    }

    printf("\n");
}


