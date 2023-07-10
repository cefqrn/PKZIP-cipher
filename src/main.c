#include "cipher.h"

#include <stdbool.h>  // bool, false
#include <stdlib.h>   // srand, rand
#include <string.h>   // strerror
#include <unistd.h>   // getopt
#include <errno.h>    // errno
#include <stdio.h>    // printf, etc.
#include <time.h>     // time

#define PUTCHAR_OR_ERROR(c, ofile) if (putc(c, ofile) == EOF) goto OUTPUT_ERROR
#define FCLOSE_IF_OPEN(file) if (file != NULL) fclose(file)

int main(int argc, char *argv[]) {
    bool decoding = false;
    char *password = NULL;
    FILE *ifile = stdin;
    FILE *ofile = stdout;
    {  // parse arguments
        int c;
        while ((c = getopt(argc, argv, "hdi:o:")) != -1) {
            switch (c) {
                case 'h':
                printf("Usage: %s [-d] [-i ipath] [-o opath] password\n", argv[0]);
                printf("  -d  decode\n  -i  input file path\n  -o  output file path\n");
                return 0;
                case 'd':
                decoding = true;
                break;
                case 'i':
                ifile = fopen(optarg, "r");
                if (ifile == NULL) goto INPUT_ERROR;
                break;
                case 'o':
                ofile = fopen(optarg, "w");
                if (ofile == NULL) goto OUTPUT_ERROR;
            }
        }

        if (argc - optind != 1) {
            fprintf(stderr, "Usage: %s [-d] [-i ipath] [-o opath] password\n", argv[0]);
            return 1;
        }

        password = argv[optind];
    }

    struct cipher_keys keys = create_keys(strlen(password), password);
    if (decoding) {
        for (int i = 0; i < 12; ++i) {
            // initialize keys using the 12 initial random bytes
            int c = getc(ifile);
            if (c == EOF)
                goto INPUT_ERROR;

            decrypt_char(&keys, c);
        }

        for (int c = getc(ifile); c != EOF; c = getc(ifile))
            PUTCHAR_OR_ERROR(decrypt_char(&keys, c), ofile);
    } else {
        // prepend 12 random bytes
        srand(time(NULL));
        for (int i = 0; i < 12; ++i)
            PUTCHAR_OR_ERROR(encrypt_char(&keys, (char)rand()), ofile);

        for (int c = getc(ifile); c != EOF; c = getc(ifile))
            PUTCHAR_OR_ERROR(encrypt_char(&keys, c), ofile);
    }

    if (ferror(ifile))
        goto INPUT_ERROR;

    // success
    fclose(ifile);
    fclose(ofile);

    return 0;

    // possible failures
    INPUT_ERROR:
    FCLOSE_IF_OPEN(ifile);
    FCLOSE_IF_OPEN(ofile);

    fprintf(stderr, "Error while reading from input: %s\n", strerror(errno));
    return 1;

    OUTPUT_ERROR:
    FCLOSE_IF_OPEN(ifile);
    FCLOSE_IF_OPEN(ofile);

    fprintf(stderr, "Error while writing to output: %s\n", strerror(errno));
    return 1;
}
