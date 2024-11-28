#include <stdio.h>
#include <string.h>
#include "onetimepad.h"

int main()
{
    char texto[13] = "UNIVERSIDADE";
    char chave[13] = "CRIPTOGRAFIA";
    onetimepad_t * otp = iniciaOnetimepad();

    char * texto_cifrado = cifraTexto(otp, texto, chave);

    printf("\n");
    printf("texto: %s\n", texto);
    printf("texto cifrado %s\n", texto_cifrado);

    char * texto_decifrado = decifraTexto(otp, texto_cifrado, chave);
    printf("texto decifrado %s\n", texto_decifrado);
}