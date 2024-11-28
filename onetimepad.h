#define NUM_CHARS 26
#define INITIAL_CAPITAL_ASCII_LETTER 65
#define INITIAL_LOWERCASE_ASCII_LETTER 97

typedef struct onetimepad {
    int * tabela;
} onetimepad_t;

onetimepad_t * iniciaOnetimepad();

char * cifraTexto(onetimepad_t * otp, char * texto, char * chave);

char * decifraTexto(onetimepad_t * otp, char * texto_cifrado, char * chave);

void imprimeTabela(onetimepad_t * otp);