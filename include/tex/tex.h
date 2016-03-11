#pragma once

#include <stdio.h>
#include <stdint.h>

typedef enum {
    TEX_INVALID,

    TEX_ASCII,
    TEX_SEQUENCE,
    TEX_MODIFIER,

    TEX_SEQUENCE_T1,
    TEX_SEQUENCE_TEXTCOMP,

    TEX_UNSUPPORTED,
} tex_char_t;

tex_char_t tex_from_char(char *s, uint32_t c);

char *tex_from_str(const char *s);

int tex_fputs(const char *s, FILE *f);

enum {
    TEX_MAX_SEQUENCE_LEN = 30,
};
