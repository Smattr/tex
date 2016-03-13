#include <assert.h>
#include "internal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "utf8totex/utf8totex.h"

int utf8totex_fputs(const char *s, FILE *f) {
    assert(s != NULL);
    assert(f != NULL);

    char lookahead = 0;

    uint32_t c;
    int length;
    while ((length = get_utf8_char(&c, s)) != 0) {
        assert(length <= 4);

        if (length == -1)
            return EOF;

        char t[UTF8TOTEX_MAX_SEQUENCE_LEN];
        utf8totex_char_t type = utf8totex_from_char(t, c);

        switch (type) {
            case UTF8TOTEX_INVALID:
                return EOF;

            case UTF8TOTEX_ASCII:
                if (lookahead != 0)
                    if (fputc(lookahead, f) == EOF)
                        return EOF;
                lookahead = c;
                break;

            case UTF8TOTEX_SEQUENCE:
            case UTF8TOTEX_SEQUENCE_T1:
            case UTF8TOTEX_SEQUENCE_TEXTCOMP:
                if (lookahead != 0) {
                    if (fputc(lookahead, f) == EOF)
                        return EOF;
                    lookahead = 0;
                }
                if (fputs(t, f) == EOF)
                    return EOF;
                break;

            case UTF8TOTEX_MODIFIER:
                if (lookahead == 0)
                    return EOF;

                /* Work around older versions of LaTeX that do not know to drop
                 * overhead dot on an 'i' or 'j' when inserting an accent.
                 */
                const char *prefix = "";
                if ((lookahead == 'i' || lookahead == 'j') &&
                    strncmp(t, "{\\", sizeof("{\\") - 1) == 0 &&
                    (t[2] == '"' || t[2] == '\'' || t[2] == '.' ||
                     t[2] == '=' || t[2] == '^' || t[2] == '`' ||
                     t[2] == '~' || t[2] == 'H' || t[2] == 'r' ||
                     t[2] == 't' || t[2] == 'u' || t[2] == 'v'))
                    prefix = "\\";

                if (fprintf(f, "%s%s%c}", t, prefix, (char)lookahead) < 0)
                    return EOF;
                lookahead = 0;
                break;

            case UTF8TOTEX_UNSUPPORTED:
                return EOF;
        }

        s += length;
    }

    if (lookahead != 0)
        if (fputc(lookahead, f) == EOF)
            return EOF;

    return 0;
}
