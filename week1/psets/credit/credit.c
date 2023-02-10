#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool checksum(long num);

int main(void)
{
    //Receba um número de cartão
    long num;
    do
    {
        num = get_long("Número do cartão: ");
    }
    while (num < 1);


    if (checksum(num))
    {
        //Determine a bandeira
        //Vou dividir para trabalhar com números menores

        int band = num / pow(10, 12); //1 Trilhão, 13 dig
        // 13 dig = 1
        // 15 dig = 100
        // 16 dig = 1000

        if (band == 4 || (band >= 4000 && band < 5000)) //[4000,5000[
        {
            printf("VISA\n");
        }
        else if ((band >=  340 && band < 350) || (band >= 370 && band < 380)) //[340,350[, [370,380[
        {
            printf("AMEX\n");
        }
        else if (band >= 5100 && band < 5600) //[5100,5600[
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}


//Verifique se é um número válido
bool checksum(long num)
{
    // OK: Isolar todos os dígitos
    // OK: Fazer os cálculos e testar se o último dígito é zero.

    int num_len = floor(log10(num)) + 1; //Pega o tamanho da sequência a partir do log de base 10
    int digit;
    int d_digit;
    int soma_imp = 0;
    int mult_par = 0;

    for (int i = 1; i <= num_len; i++)
    {
        digit = num % 10;
        d_digit = digit * 2;
        num /= 10; //Divide a sequência por 10 pra excluir o último número

        if (i % 2 == 0)
        {
            //soma de (digit*2) em posições pares
            if (d_digit < 10)
            {
                mult_par += d_digit % 10;
            }
            else
            {
                mult_par += 1;
                mult_par += d_digit % 10;
            }
        }
        else
        {
            //Soma os dígitos nas posições ímpares
            soma_imp += digit;
        }
    }

    int total = mult_par + soma_imp;

    if (total % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}