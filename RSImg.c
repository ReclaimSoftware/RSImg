#include <RSImg.h>
#include <stdlib.h>
#include <string.h>


int RSImgFreadPPMP6Header(FILE *file, uint32_t *width, uint32_t *height, uint32_t *headerSize) {

    const int prefixSize = 3;
    char prefix[3] = {'P', '6', '\n'};

    const int suffixSize = 4;
    char suffix[4] = {'2', '5', '5', '\n'};

    // "P6\n"
    char actualPrefix[prefixSize];
    if (fread(actualPrefix, prefixSize, 1, file) != 1) {
        return 0;
    }
    if (memcmp(actualPrefix, prefix, prefixSize) != 0) {
        return 0;
    }

    // "2880 1800\n"
    const int lineSize = 200;
    char line[lineSize];
    fgets(line, lineSize, file);
    *headerSize = 3 + strlen(line) + 4;
    char *tok = strtok(line, " ");
    *width = atol(tok);
    tok = strtok(NULL, " ");
    *height = atol(tok);

    // "255\n"
    char actualSuffix[suffixSize];
    if (fread(actualSuffix, suffixSize, 1, file) != 1) {
        return 0;
    }
    if (memcmp(actualSuffix, suffix, suffixSize) != 0) {
        return 0;
    }

    return 1;
}
