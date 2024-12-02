#include "aes.h"
#include <stdio.h>
#include <string.h>
#include "onetimepad.h"

int le_escreve_arquivo(
    const char * nome_arquivo_in,
    char * nome_arquivo_out,
    AES_KEY aes_key,
    char * otp_key,
    void (*func)(const unsigned char *in, unsigned char *out, const AES_KEY *key, char *OTP_KEY)
)
{
    unsigned char text[17]; 
    unsigned char buffer[16];
    unsigned char content[16];
    size_t bytes_lidos;

    FILE *arquivo_in;
    FILE *arquivo_out;

    arquivo_in = fopen(nome_arquivo_in, "r");
    if (arquivo_in == NULL)
    {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    arquivo_out = fopen(nome_arquivo_out, "w+");
    if (arquivo_out == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while ((bytes_lidos = fread(buffer, 1, sizeof(buffer), arquivo_in)) > 0)
    {
        // Escreve os bytes lidos diretamente como caracteres

        for (size_t i = 0; i < bytes_lidos; i++)
        {
            // Exibe o byte como caractere, ou um ponto '.' se for um caractere não imprimível
            text[i] = buffer[i];
        }

        func(text, content, &aes_key, otp_key);
        fwrite(content, 1, 16, arquivo_out);

        text[16] = '\0';
    }

    fclose(arquivo_in);
    fclose(arquivo_out);
}

int main(int argc, char const *argv[])
{
    AES_KEY encryptKey, decryptKey;

    char *otp_key = geraChave(16);
    char *key = geraChave(16);

    // Set encryption and decryption keys
    AES_set_encrypt_key(key, 128, &encryptKey);
    AES_set_decrypt_key(key, 128, &decryptKey);

    printf("ENCRIPTANDO ARQUIVO %s\n", argv[1]);
    le_escreve_arquivo(argv[1], "encriptado.txt", encryptKey, otp_key, AES_encrypt);

    printf("DECRIPTANDO ARQUIVO %s\n", argv[1]);
    le_escreve_arquivo("encriptado.txt", "decriptado.txt", decryptKey, otp_key, AES_decrypt);

    printf("SUCESSO\n");

    return 0;
}
