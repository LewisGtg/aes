#include <openssl/aes.h>
#include <stdio.h>
#include <string.h>
#include "onetimepad.h"

int main() {
    unsigned char text[16] = "plaintextblock";  // Plaintext block
    unsigned char encrypted[16];               // Encrypted output
    unsigned char decrypted[16];               // Decrypted output

    AES_KEY encryptKey, decryptKey;

    char * otp_key = geraChave(16);
    char * key = geraChave(16);

    // Set encryption and decryption keys
    AES_set_encrypt_key(key, 128, &encryptKey);
    AES_set_decrypt_key(key, 128, &decryptKey);

    // Encrypt the plaintext
    AES_encrypt(text, encrypted, &encryptKey, otp_key);
    printf("Encrypted text: ");
    for (int i = 0; i < 16; i++) printf("%02x", encrypted[i]);
    printf("\n");

    // Decrypt the ciphertext
    AES_decrypt(encrypted, decrypted, &decryptKey, otp_key);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
