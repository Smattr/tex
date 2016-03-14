#include <assert.h>
#include "internal.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "utf8totex/utf8totex.h"

int utf8totex_fputs(const char *s, bool bibtex, FILE *f, utf8totex_char_t *error) {
    assert(s != NULL);
    assert(f != NULL);

#define ERR(code) \
    do { \
        if (error != NULL) { \
            *error = UTF8TOTEX_ ## code; \
        } \
        return EOF; \
    } while (0)

    char _lookahead[2] = {0};
    const char* lookahead = NULL;
#define FLUSH_LOOKAHEAD() \
    do { \
        if (lookahead != NULL) { \
            if (fputs(lookahead, f) == EOF) { \
                ERR(INVALID); \
            } \
            lookahead = NULL; \
        } \
    } while (0)

    unsigned brace_depth = 0;

    uint32_t c;
    int length;
    while ((length = get_utf8_char(&c, s)) != 0) {
        assert(length <= 4);

        if (length == -1)
            ERR(INVALID);

        if (bibtex) {
            if (c == L'{' || brace_depth > 0) {
                if (length != 1)
                    ERR(INVALID); /* XXX */
                FLUSH_LOOKAHEAD();
                if (fputc(c, f) == EOF)
                    ERR(EOF);
                if (c == L'{') {
                    brace_depth++;
                } else if (c == '}') {
                    assert(brace_depth > 0);
                    brace_depth--;
                }
                s++;
                continue;
            }
        }

        const char *t;
        utf8totex_char_t type = utf8totex_from_char(&t, c);

        switch (type) {
            case UTF8TOTEX_ASCII:
                FLUSH_LOOKAHEAD();
                _lookahead[0] = c;
                lookahead = _lookahead;
                break;

            case UTF8TOTEX_SEQUENCE:
            case UTF8TOTEX_SEQUENCE_T1:
            case UTF8TOTEX_SEQUENCE_TEXTCOMP:
                FLUSH_LOOKAHEAD();
                lookahead = t;
                break;

            case UTF8TOTEX_MODIFIER:
                if (lookahead == NULL)
                    ERR(BAD_MODIFIER);

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

                if (fprintf(f, "%s%s", t, prefix) < 0)
                    ERR(EOF);
                FLUSH_LOOKAHEAD();
                if (fputc('}', f) == EOF)
                    ERR(EOF);
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

    FLUSH_LOOKAHEAD();

#undef FLUSH_LOOKAHEAD

#undef ERR

    return 0;
}
