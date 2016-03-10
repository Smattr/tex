/* UTF-8 decoder.
 *
 * FIXME: It seems vaguely ridiculous to implement one of these inline, but I
 * can't find any standard library support for doing this and it seems overkill
 * to link against something like ICU just for this. Maybe I'm just too tired.
 */

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

static unsigned char mask_low(unsigned char value, unsigned int bits) {
    assert(bits <= CHAR_BIT);
    return value & ((1 << bits) - 1);
}

static unsigned char mask_high(unsigned char value, unsigned int bits) {
    assert(bits <= CHAR_BIT);
    return value & (~(mask_low(value, CHAR_BIT - bits)));
}

static uint32_t shift_accumulate(uint32_t accumulator, unsigned char operand, unsigned int bits) {
    assert(bits <= CHAR_BIT);
    return (accumulator << bits) | mask_low(operand, bits);
}

int get_utf8_char(uint32_t *c, const char *s) {
    assert(c != NULL);
    assert(s != NULL);

    if (*s == 0) {
        *c = 0;
        return 0;
    }

    unsigned char leader = (unsigned char)(*s);

    if (mask_high(leader, 1) == 0b00000000) {
        /* 1 byte */
        *c = leader;
        return 1;

    } else if (mask_high(leader, 3) == 0b11000000) {
        /* 2 bytes */
        unsigned char byte2 = (unsigned char)(*++s);
        if (mask_high(byte2, 2) != 0b10000000)
            return -1;
        *c = shift_accumulate(mask_low(leader, 5), byte2, 6);
        return 2;

    } else if (mask_high(leader, 4) == 0b11100000) {
        /* 3 bytes */
        unsigned char byte2 = (unsigned char)(*++s);
        if (mask_high(byte2, 2) != 0b10000000)
            return -1;
        unsigned char byte3 = (unsigned char)(*++s);
        if (mask_high(byte3, 2) != 0b10000000)
            return -1;
        *c = shift_accumulate(
              shift_accumulate(
               mask_low(leader, 4), byte2, 6),
                                   byte3, 6);
        return 3;

    } else if (mask_high(leader, 5) == 0b11110000) {
        /* 4 bytes */
        unsigned char byte2 = (unsigned char)(*++s);
        if (mask_high(byte2, 2) != 0b10000000)
            return -1;
        unsigned char byte3 = (unsigned char)(*++s);
        if (mask_high(byte3, 2) != 0b10000000)
            return -1;
        unsigned char byte4 = (unsigned char)(*++s);
        if (mask_high(byte4, 2) != 0b10000000)
            return -1;
        *c = shift_accumulate(
              shift_accumulate(
               shift_accumulate(mask_low(leader, 3), byte2, 6),
                                                    byte3, 6),
                                                   byte4, 6);
        return 4;

    }

    return -1;
}
