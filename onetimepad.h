#define NUM_CHARS 26
#define INITIAL_ASCII_LETTER 97

typedef struct onetimepad {
    int * tabela;
} onetimepad_t;

onetimepad_t * iniciaOnetimepad();

char * cifraTexto(onetimepad_t * otp, char * texto, char * chave);