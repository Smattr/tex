#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utf8totex/utf8totex.h"
#include <wchar.h>

char *utf8totex_from_str(const char *s, bool fuzzy, utf8totex_char_t *error) {

    /* setup a dynamically growing buffer */
    char *buffer_p;
    size_t buffer_size;
    FILE *buffer = open_memstream(&buffer_p, &buffer_size);
    if (buffer == NULL)
        return NULL;

    int r = utf8totex_fputs(s, fuzzy, buffer, error);
    fclose(buffer);
    if (r != 0) {
        free(buffer_p);
        return NULL;
    }

    return buffer_p;
}
