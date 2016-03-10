#pragma once

#include <stdint.h>

int get_utf8_char(uint32_t *c, const char *s) __attribute__((visibility("internal")));
