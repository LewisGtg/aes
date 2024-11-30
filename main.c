#include <openssl/aes.h>
#include <stdio.h>
#include <string.h>
#include "onetimepad.h"

int main(int argc, char const *argv[])
{
    unsigned char text[17];      // Plaintext block
    unsigned char encrypted[16]; // Encrypted output
    unsigned char decrypted[16];
    unsigned char buffer[16]; // Buffer para armazenar 16 bytes
    size_t bytes_lidos;

    AES_KEY encryptKey, decryptKey;

    char *otp_key = geraChave(16);
    char *key = geraChave(16);

    // Set encryption and decryption keys
    AES_set_encrypt_key(key, 128, &encryptKey);
    AES_set_decrypt_key(key, 128, &decryptKey);

    printf("argv: %s\n", argv[1]);

    FILE *arquivo;
    FILE *arquivo_encriptado;
    FILE *arquivo_decriptado;
    char linha[256];
    // Abre o arquivo em modo de leitura ("r")
    arquivo = fopen(argv[1], "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    arquivo_encriptado = fopen("encriptado.txt", "w+");
    if (arquivo_encriptado == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê cada linha do arquivo e imprime na tela
    while ((bytes_lidos = fread(buffer, 1, sizeof(buffer), arquivo)) > 0)
    {
        // Escreve os bytes lidos diretamente como caracteres

        for (size_t i = 0; i < bytes_lidos; i++)
        {
            // Exibe o byte como caractere, ou um ponto '.' se for um caractere não imprimível
            text[i] = buffer[i];
        }

        AES_encrypt(text, encrypted, &encryptKey, otp_key);
        fwrite(encrypted, 1, 16, arquivo_encriptado);

        text[16] = '\0';
    }
    // Fecha o arquivo
    fclose(arquivo);
    fclose(arquivo_encriptado);

    arquivo_encriptado = fopen("encriptado.txt", "r");
    if (arquivo_encriptado == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    arquivo_decriptado = fopen("decriptado.txt", "w+");
    if (arquivo_decriptado == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while ((bytes_lidos = fread(buffer, 1, sizeof(buffer), arquivo_encriptado)) > 0)
    {
        // Escreve os bytes lidos diretamente como caracteres
        for (size_t i = 0; i < bytes_lidos; i++)
        {
            // Exibe o byte como caractere, ou um ponto '.' se for um caractere não imprimível
            text[i] = buffer[i];
        }

        AES_decrypt(text, decrypted, &decryptKey, otp_key);
        fwrite(decrypted, 1, 16, arquivo_decriptado);

        text[16] = '\0';
    }

    printf("SUCESSO\n");

    return 0;
}
