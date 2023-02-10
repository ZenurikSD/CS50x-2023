#include <cs50.h>
#include <stdio.h>
#include <string.h>

//Defina uma estrutura de pessoa com nome e número
typedef struct
{
    string nome;
    string numero;
}
pessoa;

int main(void)
{
    //Instancie duas pessoas
    pessoa dupla[2];

    dupla[0].nome = "Zenurik";
    dupla[0].numero = "+55-(11)-95555-2222";

    dupla[1].nome = "David";
    dupla[1].numero = "+1-122-444-555";

    //Pergunte por um nome e faça uma busca linear para retornar o número correspondente.
    string n = get_string("Nome: ");

    for(int i = 0; i < 2; i++)
    {
        if(strcmp(dupla[i].nome, n) == 0)
        {
            printf("Número: %s\n", dupla[i].numero);
            return 0;
        }
    }

    printf("Não encontrado\n");
    return 1;
}