#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "onetimepad.h"

int num_valido(int *v, int n)
{
    for (int i = 0; i < NUM_CHARS; i++)
    {
        if (v[i] == n)
        {
            return 1;
        }
    }
    return 0;
}

onetimepad_t *iniciaOnetimepad()
{
    onetimepad_t *otp = malloc(sizeof(onetimepad_t));
    otp->tabela = malloc(sizeof(int) * NUM_CHARS);

    for (int i = 0; i < NUM_CHARS; i++)
        otp->tabela[i] = -1;

    srand(time(NULL));

    int random;
    for (int i = 0; i < NUM_CHARS; i++)
    {
        do
            random = (rand() % (NUM_CHARS + 1));
        while (num_valido(otp->tabela, random) != 0);
        otp->tabela[i] = random;
    }

    return otp;
}

char * cifraTexto(onetimepad_t * otp, char * texto, char * chave)
{
    int size = strlen(texto);
    char * texto_cifrado = malloc(sizeof(char) * size);

    for (int i = 0; i < 14; i++)
    {

        printf("%c:%d + %c:%d => %c:%d\n", texto[i], otp->tabela[texto[i] - INITIAL_ASCII_LETTER] ,chave[i],otp->tabela[chave[i] - INITIAL_ASCII_LETTER], otp->tabela[(texto[i] + chave[i] - INITIAL_ASCII_LETTER) % NUM_CHARS])), otp->tabela[(texto[i] + chave[i] - INITIAL_ASCII_LETTER) % NUM_CHARS]);
        printf("%d + %d = %d\n", texto[i], chave[i], (texto[i] + chave[i] - INITIAL_ASCII_LETTER) % NUM_CHARS);
        // printf("%c => %c ", texto[i], otp->tabela[texto[i] - INITIAL_ASCII_LETTER] + INITIAL_ASCII_LETTER);
        texto_cifrado[i] = otp->tabela[texto[i] - INITIAL_ASCII_LETTER] + INITIAL_ASCII_LETTER;
    }

    return texto_cifrado;
}