#include <cs50.h>
#include <stdio.h>

float somar(int x, int y);
float subtrair(int x, int y);
float multiplicar(int x, int y);
float dividir(int x, int y);

int main(){
    float a = get_float("X: ");
    float b = get_float("Y: ");
    printf("Escolha o nº da operação: [1 +], [2 -], [3 *], [4 /]\n");

    int escolha;
    do
    {
        escolha = get_int(": ");
    }
    while(escolha < 0 && escolha > 4);


    float result;
    switch (escolha){
        case: 1
            result = somar(a, b);

        case: 2
            result = subtrair(a, b);

        case: 3
            result = multiplicar(a, b);

        case: 4
            result = dividir(a, b);
    }

    printf("\n Resp: %f", result);


}



float somar(int x, int y)
{
    return x + y;
}

float subtrair(int x, int y)
{
    return x - y;
}

float multiplicar(int x, int y){
    return x * y;
}

float dividir(int x, int y){
    return x / y;
}