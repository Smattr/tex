#include <assert.h>
#include "internal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "tex/tex.h"

int tex_fputs(const char *s, FILE *f) {
    assert(s != NULL);
    assert(f != NULL);

    uint32_t c;
    int length;
    while ((length = get_utf8_char(&c, s)) != 0) {
        assert(length <= 4);

        if (length == -1)
            return EOF;

        const char *t = tex_from_char(c);
        if (t == NULL) {
            int l = fwrite(s, 1, length, f);
            if (l != length)
                return EOF;
        } else {
            int l = fputs(t, f);
            if (l == EOF)
                return EOF;
        }

        s += length;
    }

    return 0;
}
