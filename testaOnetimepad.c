#include <stdio.h>
#include <string.h>
#include "onetimepad.h"

int main()
{
    char texto[13] = "UnIvErSiDaDe";

    char * chave = geraChave(13);
    char * texto_cifrado = cifraTexto(texto, chave);

    printf("\n");
    printf("texto: %s\n", texto);
    printf("texto cifrado %s\n", texto_cifrado);

    char * texto_decifrado = decifraTexto(texto_cifrado, chave);
    printf("texto decifrado %s\n", texto_decifrado);
}