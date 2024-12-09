#include <stdio.h>
#include <string.h>
#include <time.h>
#include "aes.h"
#include "onetimepad.h"
#define BUFFER_SIZE 16

typedef enum flag_encripta
{
    decripta,
    encripta,
} flag_encripta_e;

typedef enum flag_otp
{
    sem_otp,
    com_otp,
} flag_otp_e;

int bytesPadding = 0;
int lastReadIndex = 0;

double encripta_decripta(
    FILE *arquivo_in,
    FILE *arquivo_out,
    AES_KEY aes_key,
    char *otp_key,
    void (*func)(const unsigned char *in, unsigned char *out, const AES_KEY *key, char *OTP_KEY),
    int encrypt)
{
    unsigned char text[17];
    unsigned char buffer[BUFFER_SIZE];
    unsigned char content[BUFFER_SIZE];
    size_t bytes_lidos;

    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock();
    int readIndex = 0;
    while ((bytes_lidos = fread(buffer, 1, sizeof(buffer), arquivo_in)) > 0)
    {
        readIndex++;
        for (size_t i = 0; i < bytes_lidos; i++)
            text[i] = buffer[i];

        for (size_t i = bytes_lidos; i < BUFFER_SIZE; i++) // adiciona padding
            text[i] = '@';

        if (bytes_lidos < BUFFER_SIZE && encrypt)
            bytesPadding = BUFFER_SIZE - bytes_lidos;

        if (encrypt)
            lastReadIndex = readIndex;

        func(text, content, &aes_key, otp_key);
        int bytesToWrite = !encrypt && bytesPadding && lastReadIndex == readIndex ? BUFFER_SIZE - bytesPadding : BUFFER_SIZE;
        fwrite(content, 1, bytesToWrite, arquivo_out);

        text[BUFFER_SIZE] = '\0';
    }
    fim = clock();

    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    return tempo_gasto;
}

int aes(
    const char *nome_arquivo_in,
    char *nome_arquivo_out,
    AES_KEY aes_key,
    char *otp_key,
    int otp,
    int encrypt)
{
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

    void (*func)(const unsigned char *in, unsigned char *out, const AES_KEY *key, char *OTP_KEY);

    if (otp)
    {
        if (encrypt)
            func = AES_encryptOTP;
        else
            func = AES_decryptOTP;
    }
    else
    {
        if (encrypt)
            func = AES_encrypt;
        else
            func = AES_decrypt;
    }

    double tempo_gasto = encripta_decripta(arquivo_in, arquivo_out, aes_key, otp_key, func, encrypt);

    printf("%.6fs\t\t", tempo_gasto);

    fclose(arquivo_in);
    fclose(arquivo_out);
}

int main(int argc, char const *argv[])
{
    AES_KEY encryptKey, decryptKey;

    char *otp_key = geraChave(BUFFER_SIZE);
    char *key = geraChave(BUFFER_SIZE);

    // Set encryption and decryption keys
    AES_set_encrypt_key(key, 128, &encryptKey);
    AES_set_decrypt_key(key, 128, &decryptKey);

    // printf("%s\n", argv[1]);
    printf("encript (otp)\tdecript (otp)\tencript (sbox)\tdecript (sbox)\n");
    aes(argv[1], "encriptado_otp.txt", encryptKey, otp_key, com_otp, encripta);
    aes("encriptado_otp.txt", "decriptado_otp.txt", decryptKey, otp_key, com_otp, decripta);
    aes(argv[1], "encriptado.txt", encryptKey, otp_key, sem_otp, encripta);
    aes("encriptado.txt", "decriptado.txt", decryptKey, otp_key, sem_otp, decripta);
    printf("\n-----------------------------------------------------\n\n");

    return 0;
}
