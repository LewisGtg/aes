#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "onetimepad.h"

char * cifraTexto(char * texto, char * chave)
{
    int size = strlen(texto);
    char * texto_cifrado = malloc(sizeof(char) * size);

    for (int i = 0; i < 12; i++)
    {
        texto_cifrado[i] = texto[i] ^ chave[i];
    }

    return texto_cifrado;
}

char * decifraTexto(char * texto_cifrado, char * chave)
{
    int size = strlen(texto_cifrado);
    char * texto_decifrado = malloc(sizeof(char) * size);

    for (int i = 0; i < 12; i++)
    {
        texto_decifrado[i] = texto_cifrado[i] ^ chave[i];
    }

    return texto_decifrado;
}

char * geraChave(int size)
{
    char * chave = malloc(sizeof(char) * size);

    srand(time(NULL));

    int random;
    for (int i = 0; i < size; i++)
    {
        random = (rand() % (NUM_CHARS_ASCII + 1));
        chave[i] = random;
    }

    return chave;
}