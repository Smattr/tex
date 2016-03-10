#pragma once

#include <stdio.h>
#include <stdint.h>

const char *tex_from_char(uint32_t c);

char *tex_from_str(const char *s);

int tex_fputs(const char *s, FILE *f);
