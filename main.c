#include <openssl/aes.h>
#include <stdio.h>
#include <string.h>

int main() {
    unsigned char key[16] = "0123456789abcdef"; // AES key
    unsigned char text[16] = "plaintextblock";  // Plaintext block
    unsigned char encrypted[16];               // Encrypted output
    unsigned char decrypted[16];               // Decrypted output

    AES_KEY encryptKey, decryptKey;

    // Set encryption and decryption keys
    AES_set_encrypt_key(key, 128, &encryptKey);
    AES_set_decrypt_key(key, 128, &decryptKey);

    // Encrypt the plaintext
    AES_encrypt(text, encrypted, &encryptKey);
    printf("Encrypted text: ");
    for (int i = 0; i < 16; i++) printf("%02x", encrypted[i]);
    printf("\n");

    // Decrypt the ciphertext
    AES_decrypt(encrypted, decrypted, &decryptKey);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
