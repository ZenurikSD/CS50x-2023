#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("Diga X: ");
    int y = get_int("Diga Y: ");

    if (x>y)
    {
        printf("X é maior que Y\n");
    }
    else if (x<y)
    {
        printf("X é menor que Y\n");
    }
    else
    {
        printf("Os dois são iguais\n");
    }
}