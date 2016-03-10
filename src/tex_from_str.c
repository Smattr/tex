#include <stdio.h>
#include <stdlib.h>
#include "tex/tex.h"
#include <wchar.h>

char *tex_from_str(const char *s) {

    /* setup a dynamically growing buffer */
    char *buffer_p;
    size_t buffer_size;
    FILE *buffer = open_memstream(&buffer_p, &buffer_size);
    if (buffer == NULL)
        return NULL;

    int r = tex_fputs(s, buffer);
    fclose(buffer);
    if (r == EOF) {
        free(buffer_p);
        return NULL;
    }

    return buffer_p;
}
