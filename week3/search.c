#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //Crie um vetor estático e peça ao usuário valor
    string strings[] = {"navio", "carro", "cartola", "monóculo"};

    string s = get_string("Obj: ");

    //Percorra o vetor de forma linear, avise e termine a execução se encontrar ou não
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(strings[i], s) == 0)
        {
            printf("Encontrado\n");
            return 0;
        }
    }

    printf("Não encontrado\n");
    return 1;
}