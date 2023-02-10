#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

string encrypt(string txt, int key);

int main(int argc, string argv[])
{
    //Aceite apenas um argumento
    if (argc != 2)
    {
        printf("   Uso: ./caesar chave\n");
        return 1;
    }


    //verifique se cada caractere do arg é um dígito e converta
    string str_key = argv[1];

    for (int i = 0; str_key[i] != '\0'; i++)
    {
        if (!(isdigit(str_key[i])))
        {
            return 1;
        }
    }

    int key = atoi(str_key);


    //Pegue o texto e construa a função para criptografá-lo
    string plaintxt = get_string("plaintext: ");

    printf("ciphertext: %s\n", encrypt(plaintxt, key));
}


string encrypt(string txt, int key)
{
    int desloc = 0;

    for (int i = 0; txt[i] != '\0'; i++)
    {
        //Limite o escopo para apenas letras do alfabeto
        if (islower(txt[i]))
        {
            desloc = txt[i] - 'a'; //mapeia para [0,25]

            desloc = (desloc + key) % 26; //aplica a fórmula

            txt[i] = desloc + 'a'; //retorna ao mapeamento ASCII
        }
        else if (isupper(txt[i]))
        {
            desloc = txt[i] - 'A';

            desloc = (desloc + key) % 26;

            txt[i] = desloc + 'A';
        }
    }

    return txt;
}
