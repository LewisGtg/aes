#include <stdio.h>
#include <stdlib.h>
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