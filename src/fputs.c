#include <assert.h>
#include "internal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "utf8totex/utf8totex.h"

int utf8totex_fputs(const char *s, FILE *f, utf8totex_char_t *error) {
    assert(s != NULL);
    assert(f != NULL);

    char _lookahead[2] = {0};
    const char* lookahead = NULL;

    uint32_t c;
    int length;
    while ((length = get_utf8_char(&c, s)) != 0) {
        assert(length <= 4);

        if (length == -1) {
            if (error != NULL)
                *error = UTF8TOTEX_INVALID;
            return EOF;
        }

        const char *t;
        utf8totex_char_t type = utf8totex_from_char(&t, c);

        switch (type) {
            case UTF8TOTEX_ASCII:
                if (lookahead != NULL) {
                    if (fputs(lookahead, f) == EOF) {
                        if (error != NULL)
                            *error = UTF8TOTEX_EOF;
                        return EOF;
                    }
                }
                _lookahead[0] = c;
                lookahead = _lookahead;
                break;

            case UTF8TOTEX_SEQUENCE:
            case UTF8TOTEX_SEQUENCE_T1:
            case UTF8TOTEX_SEQUENCE_TEXTCOMP:
                if (lookahead != NULL) {
                    if (fputs(lookahead, f) == EOF) {
                        if (error != NULL)
                            *error = UTF8TOTEX_EOF;
                        return EOF;
                    }
                }
                lookahead = t;
                break;

            case UTF8TOTEX_MODIFIER:
                if (lookahead == NULL) {
                    if (error != NULL)
                        *error = UTF8TOTEX_BAD_MODIFIER;
                    return EOF;
                }

                /* Work around older versions of LaTeX that do not know to drop
                 * overhead dot on an 'i' or 'j' when inserting an accent.
                 */
                const char *prefix = "";
                if ((lookahead[0] == 'i' || lookahead[0] == 'j') &&
                    strncmp(t, "{\\", sizeof("{\\") - 1) == 0 &&
                    (t[2] == '"' || t[2] == '\'' || t[2] == '.' ||
                     t[2] == '=' || t[2] == '^' || t[2] == '`' ||
                     t[2] == '~' || t[2] == 'H' || t[2] == 'r' ||
                     t[2] == 't' || t[2] == 'u' || t[2] == 'v'))
                    prefix = "\\";

                if (fprintf(f, "%s%s%s}", t, prefix, lookahead) < 0) {
                    if (error != NULL)
                        *error = UTF8TOTEX_EOF;
                    return EOF;
                }
                lookahead = NULL;
                break;

            case UTF8TOTEX_UNSUPPORTED:
            case UTF8TOTEX_INVALID:
                if (error != NULL)
                    *error = type;
                return EOF;

            case UTF8TOTEX_EOF:
            case UTF8TOTEX_BAD_MODIFIER:
                /* These are never returned by `utf8totex_from_char`. */
                assert(!"unreachable");
        }

        s += length;
    }

    if (lookahead != NULL) {
        if (fputs(lookahead, f) == EOF) {
            if (error != NULL)
                *error = UTF8TOTEX_EOF;
            return EOF;
        }
    }

    return 0;
}
