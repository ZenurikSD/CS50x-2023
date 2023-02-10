#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int compute_index(string txt);

int main(void)
{
    //Usando a fórmula do índice Coleman-Liau, determine o nível escolar (grade) apropriado para uma string

    /* index = 0.0588 * L - 0.296 * S - 15.8
     * L = avg letters per 100 words (T_letras / t_palavras * 100)
     * S = avg sentcs per 100 words
     */

    string txt;
    do
    {
        txt = get_string("Text: ");
    }
    while (txt[0] <= ' ');


    int index = compute_index(txt);

    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}

int compute_index(string txt)
{
    int L = 0;
    int W = 0;
    int S = 0;

    // Percorre o texto e incrementa as contagens de letras, palavras e frases
    for (int i = 0; txt[i] != '\0'; i++)
    {
        if (isalpha(txt[i])) //mt mais simples que testar o código ascii
        {
            L++; //incrementa as letras
        }
        else if (isspace(txt[i]))
        {
            W++;
        }
        else if (txt[i] == '!' || txt[i] == '.' || txt[i] == '?')
        {
            S++;
        }
    }
    W++; // +1 para a última palavra (termina em ponto)


    //Calcule o Grade index

    // Por quê cast pra float?
    // Divisão de inteiros -> o resultado tb é inteiro. Sai truncado.
    float avgL = ((float) L / (float) W) * 100;
    float avgS = ((float) S / (float) W) * 100; //avg sentcs/100 words

    double index = 0.0588 * avgL - 0.296 * avgS - 15.8;

    return round(index);
}