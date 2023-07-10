# pkzip-cipher
A C implementation of PKWARE's traditional encryption algorithm.

## Usage
```bash
# setup
make

# usage
bin/main [-d] [-i ipath] [-o opath] password
```

## Resources
* [.ZIP File Format Specification](https://pkware.cachefly.net/webdocs/APPNOTE/APPNOTE-6.3.10.TXT) by [PKWARE Inc.](https://www.pkware.com/), 2022
* [Corkami/formats/archive/ZIP.md](https://github.com/corkami/formats/blob/master/archive/ZIP.md) by [Ange Albertini](https://github.com/angea), 2019
* [A Known Plaintext Attack on the PKZIP Stream Cipher](https://link.springer.com/chapter/10.1007/3-540-60590-8_12) by Eli Biham and Paul C. Kocher, 1994
* [Applied Cryptanalysis: Breaking Ciphers in the Real World — PKZIP PowerPoint](https://www.cs.sjsu.edu/~stamp/crypto/PowerPoint_PDF/8_PKZIP.pdf) by Mark Stamp, 2007
