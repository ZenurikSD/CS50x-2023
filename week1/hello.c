#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Hello and, again, welcome to the Aperture Science computer-aided enrichment center.\n");

    //Exclusivo CS50.H! NÃO É TÃO FÁCIL ASSIM
    string resp = get_string("SUBJECT_NAME_HERE: ");
    printf("hello, %s\n", resp);
}