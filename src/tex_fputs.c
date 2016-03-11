#include <assert.h>
#include "internal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "tex/tex.h"

int tex_fputs(const char *s, FILE *f) {
    assert(s != NULL);
    assert(f != NULL);

    char lookahead = 0;

    uint32_t c;
    int length;
    while ((length = get_utf8_char(&c, s)) != 0) {
        assert(length <= 4);

        if (length == -1)
            return EOF;

        char t[TEX_MAX_SEQUENCE_LEN];
        tex_char_t type = tex_from_char(t, c);

        switch (type) {
            case TEX_INVALID:
                return EOF;

            case TEX_ASCII:
                if (lookahead != 0)
                    if (fputc(lookahead, f) == EOF)
                        return EOF;
                lookahead = c;
                break;

            case TEX_SEQUENCE:
            case TEX_SEQUENCE_T1:
            case TEX_SEQUENCE_TEXTCOMP:
                if (lookahead != 0) {
                    if (fputc(lookahead, f) == EOF)
                        return EOF;
                    lookahead = 0;
                }
                if (fputs(t, f) == EOF)
                    return EOF;
                break;

            case TEX_MODIFIER:
                if (lookahead == 0)
                    return EOF;
                if (fprintf(f, "%s%c}", t, (char)lookahead) < 0)
                    return EOF;
                lookahead = 0;
                break;

            case TEX_UNSUPPORTED:
                return EOF;
        }

        s += length;
    }

    if (lookahead != 0)
        if (fputc(lookahead, f) == EOF)
            return EOF;

    return 0;
}
