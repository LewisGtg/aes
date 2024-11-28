#include <stdio.h>
#include <string.h>
#include "onetimepad.h"

int main()
{
    char texto[16] = "plaintextblock";
    char chave[16] = "criptografiaaa";
    onetimepad_t * otp = iniciaOnetimepad();

    char * texto_cifrado = cifraTexto(otp, texto, chave);

    printf("\n");
    printf("texto: %s\n", texto);
    printf("texto cifrado %s\n", texto_cifrado);
}