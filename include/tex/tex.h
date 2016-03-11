#pragma once

#include <stdio.h>
#include <stdint.h>

/* High level interface.
 *
 * Unless you really need to process your input character-by-character or need
 * to avoid dynamic memory allocation, this is likely all you need.
 */

/**
 * @brief Translate a UTF-8 string to an ASCII TeX string.
 *
 * @param s Input string.
 * @return Output string or `NULL` if the operation failed. The caller should
 *         eventually free this pointer.
 */
char *tex_from_str(const char *s) __attribute__((nonnull));

/**
 * @brief Translate a UTF-8 string to an ASCII TeX string and write the result
 *        to the given file.
 *
 * @param s Input string.
 * @param f File to write to.
 * @return `0` on success.
 */
int tex_fputs(const char *s, FILE *f) __attribute__((nonnull));

/* Low level interface.
 *
 * It is unlikely you will need this unless you need to move
 * character-by-character or avoid dynamic memory allocation for some reason.
 */

/**
 * @brief Return type of `tex_from_char` indicating what kind of data the given
 *        character was.
 */
typedef enum {

    TEX_INVALID, /**< The given data was not a valid unicode character. */

    TEX_ASCII, /**< The given data was an ASCII character and can be output
                    as-is. However, beware that if the next piece of data is a
                    `TEX_MODIFIER`, it may change this character's meaning. */

    TEX_SEQUENCE, /**< The given data was escaped into a sequence of ASCII
                       characters that are now in the `s` output buffer as a
                       NUL-terminated string that can be output. */

    TEX_MODIFIER, /**< The previous character was an ASCII character and needs
                       to be modified. The text to output before the character
                       is in the `s` output buffer as a NUL-terminated string.
                       The character should be followed by the string "}". If
                       the previous character was not an ASCII character, you
                       have malformed input. See the handling of this in
                       `tex_fputs`. */

    TEX_SEQUENCE_T1, /**< As for `TEX_SEQUENCE` except this sequence requires
                          an alternate font encoding like T1. */

    TEX_SEQUENCE_TEXTCOMP, /**< As for `TEX_SEQUENCE` except this sequence
                                requires the textcomp package. */

    TEX_UNSUPPORTED, /**< The data was a valid unicode character, but there is
                          no matching TeX escape sequence for it. This may mean
                          that the valid escape sequence has just not been
                          implemented yet. */

} tex_char_t;

/**
 * @brief Translate a single UTF-8 character into TeX output.
 *
 * See the definition of `tex_char_t` for how to interpret the return value of
 * this function. Note that it is entirely the caller's responsibility to
 * pre-decode their string input into UTF-8 characters. See the implementation
 * of `tex_fputs` for an example of this.
 *
 * @param s An output buffer to write TeX escape sequences into. This buffer
 *          must be at least `TEX_MAX_SEQUENCE_LEN` bytes large.
 * @param c The input UTF-8 character.
 * @return See the definition of `tex_char_t` for how to interpret this value.
 */
tex_char_t tex_from_char(char *s, uint32_t c) __attribute__((nonnull));

enum {
    TEX_MAX_SEQUENCE_LEN = 30, /**< The maximum length of any sequence returned
                                    by `tex_from_char`. */
};
