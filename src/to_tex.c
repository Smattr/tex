#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "tex/tex.h"

int main(int argc, char **argv) {

    setlocale(LC_ALL, NULL);

    FILE *in;
    if (argc > 1) {
        in = fopen(argv[1], "r");
        if (in == NULL) {
            fprintf(stderr, "failed to open %s for reading\n", argv[1]);
            return -1;
        }
    } else {
        in = stdin;
    }

    FILE *out;
    if (argc > 2) {
        out = fopen(argv[2], "w");
        if (out == NULL) {
            fprintf(stderr, "failed to open %s for writing\n", argv[2]);
            return -1;
        }
    } else {
        out = stdout;
    }

    char *line = NULL;
    size_t n;
    unsigned int lineno = 1;
    while (getline(&line, &n, in) != -1) {
        if (tex_fputs(line, out) == EOF) {
            fprintf(stderr, "failed to write line %u to output\n", lineno);
            fclose(out);
            fclose(in);
            return -1;
        }
        lineno++;
    }

    if (errno != 0) {
        fprintf(stderr, "failed to read line from input\n");
        fclose(out);
        fclose(in);
        return -1;
    }

    free(line);
    fclose(out);
    fclose(in);
    return 0;
}
