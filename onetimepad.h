#define NUM_CHARS_ASCII 255

char * cifraTexto(char * texto, char * chave);

char * decifraTexto(char * texto_cifrado, char * chave);

char * geraChave(int size);