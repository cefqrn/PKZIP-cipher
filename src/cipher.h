#ifndef CIPHER_H
#define CIPHER_H

#include <stddef.h>  // size_t
#include <stdint.h>  // uint32_t

struct cipher_keys {
    uint32_t x, y, z;
};

struct cipher_keys create_keys(size_t passwordLength, const char password[static passwordLength]);

char encrypt_char(struct cipher_keys *keys, char byte);
char decrypt_char(struct cipher_keys *keys, char byte);

#endif
