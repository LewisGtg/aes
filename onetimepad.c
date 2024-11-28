#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
        // do
        //     random = (rand() % (NUM_CHARS + 1));
        // while (num_valido(otp->tabela, random) != 0);
        otp->tabela[i] = i;
    }

    return otp;
}

char * cifraTexto(onetimepad_t * otp, char * texto, char * chave)
{
    int deslocamento_texto;
    int deslocamento_chave;
    int indexTexto;
    int indexChave;
    int size = strlen(texto);
    char * texto_cifrado = malloc(sizeof(char) * size);

    imprimeTabela(otp);

    for (int i = 0; i < 12; i++)
    {
        deslocamento_texto = texto[i] < 97 ? INITIAL_CAPITAL_ASCII_LETTER : INITIAL_LOWERCASE_ASCII_LETTER;
        deslocamento_chave = chave[i] < 97 ? INITIAL_CAPITAL_ASCII_LETTER : INITIAL_LOWERCASE_ASCII_LETTER;
        indexTexto = texto[i] - deslocamento_texto;
        indexChave = chave[i] - deslocamento_chave;

        // printf("%c:%d:%d + %c:%d:%d => %c:%d:%d\n", 
        //     texto[i],
        //     indexTexto,
        //     otp->tabela[texto[i] - deslocamento_texto],

        //     chave[i],
        //     indexChave,
        //     otp->tabela[chave[i] - deslocamento_chave],

        //     otp->tabela[(otp->tabela[indexTexto] + otp->tabela[indexChave]) % NUM_CHARS] + deslocamento_texto,
        //     (otp->tabela[indexTexto] + otp->tabela[indexChave]) % NUM_CHARS,
        //     otp->tabela[(otp->tabela[indexTexto] + otp->tabela[indexChave]) % NUM_CHARS] 
        // );


        // printf("%d + %d = %d\n", texto[i], chave[i], (texto[i] + chave[i] - INITIAL_ASCII_LETTER) % NUM_CHARS);
        // printf("%c => %c ", texto[i], otp->tabela[texto[i] - INITIAL_ASCII_LETTER] + INITIAL_ASCII_LETTER);
        texto_cifrado[i] = otp->tabela[(otp->tabela[indexTexto] + otp->tabela[indexChave]) % NUM_CHARS] + deslocamento_texto;
    }

    return texto_cifrado;
}

char * decifraTexto(onetimepad_t * otp, char * texto_cifrado, char * chave)
{
    int deslocamento_texto_cifrado; 
    int deslocamento_chave; 
    int indexTexto;
    int indexChave;
    int size = strlen(texto_cifrado);
    char * texto_decifrado = malloc(sizeof(char) * size);

    for (int i = 0; i < 12; i++)
    {
        deslocamento_texto_cifrado = texto_cifrado[i] < 97 ? INITIAL_CAPITAL_ASCII_LETTER : INITIAL_LOWERCASE_ASCII_LETTER;
        deslocamento_chave = chave[i] < 97 ? INITIAL_CAPITAL_ASCII_LETTER : INITIAL_LOWERCASE_ASCII_LETTER;

        indexTexto = texto_cifrado[i] - deslocamento_texto_cifrado;
        indexChave = chave[i] - deslocamento_chave;

        printf("%c:%d:%d + %c:%d:%d => %c:%d:%d\n", 
            texto_cifrado[i],
            indexTexto,
            otp->tabela[texto_cifrado[i] - deslocamento_texto_cifrado],

            chave[i],
            indexChave,
            otp->tabela[chave[i] - deslocamento_chave],

            otp->tabela[abs(otp->tabela[indexTexto] - otp->tabela[indexChave]) % NUM_CHARS] + deslocamento_texto_cifrado,
            abs(otp->tabela[indexTexto] - otp->tabela[indexChave]) % NUM_CHARS,
            otp->tabela[abs(otp->tabela[indexTexto] - otp->tabela[indexChave]) % NUM_CHARS] 
        );


        // printf("%d + %d = %d\n", texto[i], chave[i], (texto[i] + chave[i] - INITIAL_ASCII_LETTER) % NUM_CHARS);
        // printf("%c => %c ", texto[i], otp->tabela[texto[i] - INITIAL_ASCII_LETTER] + INITIAL_ASCII_LETTER);
        texto_decifrado[i] = otp->tabela[abs(otp->tabela[indexTexto] - otp->tabela[indexChave]) % NUM_CHARS] + deslocamento_texto_cifrado;
    }

    return texto_decifrado;
}

void imprimeTabela(onetimepad_t * otp)
{
    for (int i = 0; i < NUM_CHARS; i++) printf("%2d ", i);
    printf("\n");
    for (int i = 0; i < NUM_CHARS; i++) printf("%2d ", otp->tabela[i]);
    printf("\n\n");
}