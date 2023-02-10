#include <cs50.h>
#include <stdio.h>

int main(void)
{
    /* Crescimento populacional:
     * Determine o tempo que leva para uma população alcançar
     * um certo tamanho.
     */

    // TODO: Prompt for start size
    int tam_inic, tam_fin;
    do
    {
        tam_inic = get_int("Start size: ");
    }
    while (tam_inic < 9);

    // TODO: Prompt for end size
    do
    {
        tam_fin = get_int("End size: ");
    }
    while (tam_fin < 1 || tam_fin < tam_inic);


    // TODO: Calculate number of years until we reach threshold
    int popul = tam_inic;

    //Após cálculos de nascimentos e mortes, enquanto a população não alcançar o tamanho final, incremente um ano.
    int anos = 0;

    while (popul < tam_fin)
    {
        int nasc = popul / 3;
        int mort = popul / 4;

        popul = popul + nasc - mort;
        anos++;
    }


    // TODO: Print number of years
    printf("Years: %d\n", anos);
}