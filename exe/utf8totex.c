#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "utf8totex/utf8totex.h"

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
        utf8totex_char_t error;
        if (utf8totex_fputs(line, out, &error) == EOF) {
            fprintf(stderr, "failed to write line %u to output: %s\n", lineno,
                error == UTF8TOTEX_EOF ? "resource allocation failure" :
                error == UTF8TOTEX_INVALID ? "invalid UTF-8 character" :
                error == UTF8TOTEX_UNSUPPORTED ? "unsupported UTF-8 character" :
                error == UTF8TOTEX_BAD_MODIFIER ? "bad modifier character" :
                "unknown");
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
