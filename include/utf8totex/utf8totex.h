#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

/**
 * @brief A TeX environment, describing font encoding and what packages are in
 *        use.
 */
typedef struct {
    enum {
        UTF8TOTEX_FE_OT1 = 0, /**< OT1 font encoding (default) */
        UTF8TOTEX_FE_T1,      /**< T1 font encoding */
    } font_encoding;         /**< The font encoding of this environment */
    bool textcomp;           /**< \usepackage{textcomp}? */
} utf8totex_environment_t;

/**
 * @brief The default TeX environment.
 */
#define UTF8TOTEX_DEFAULT_ENVIRONMENT ((utf8totex_environment_t){ 0 })

/**
 * @brief Return type of `utf8totex_from_char` indicating what kind of data the given
 *        character was.
 */
typedef enum {

    UTF8TOTEX_EOF = EOF, /**< Something went wrong during output or internal
                              resource allocation. */

    UTF8TOTEX_INVALID, /**< The given data was not a valid unicode character. */

    UTF8TOTEX_UNSUPPORTED, /**< The data was a valid unicode character, but there is
                          no matching TeX escape sequence for it. This may mean
                          that the valid escape sequence has just not been
                          implemented yet. */

    UTF8TOTEX_BAD_MODIFIER, /**< A modifier appeared after something which no
                                 modifier should appear afterwards (e.g. start
                                 of string). */

    UTF8TOTEX_BAD_LITERAL, /**< A non-ASCII character occurred inside a literal
                                block or in something that was interpreted as a
                                LaTeX macro. This error can only occur when
                                fuzzy=true. */

    UTF8TOTEX_ASCII, /**< The given data was an ASCII character and can be output
                    as-is. However, beware that if the next piece of data is a
                    `UTF8TOTEX_MODIFIER`, it may change this character's meaning. */

    UTF8TOTEX_SEQUENCE, /**< The given data was escaped into a sequence of ASCII
                       characters that are now in the `s` output buffer as a
                       NUL-terminated string that can be output. */

    UTF8TOTEX_MODIFIER, /**< The previous character was an ASCII character and needs
                       to be modified. The text to output before the character
                       is in the `s` output buffer as a NUL-terminated string.
                       The character should be followed by the string "}". If
                       the previous character was not an ASCII character, you
                       have malformed input. See the handling of this in
                       `utf8totex_fputs`. */

    UTF8TOTEX_SEQUENCE_T1, /**< As for `UTF8TOTEX_SEQUENCE` except this sequence requires
                          an alternate font encoding like T1. */

    UTF8TOTEX_SEQUENCE_TEXTCOMP, /**< As for `UTF8TOTEX_SEQUENCE` except this sequence
                                requires the textcomp package. */

} utf8totex_char_t;

/* High level interface.
 *
 * Unless you really need to process your input character-by-character or need
 * to avoid dynamic memory allocation, this is likely all you need.
 */

/**
 * @brief Translate a UTF-8 string to an ASCII TeX string.
 *
 * @param s Input string.
 * @param fuzzy Whether to assume the input may be TeX. If this parameter is
 *              true, we assume the input string may be valid TeX and try to
 *              avoid translating things that look like macros, braced
 *              expressions or math mode expressions.
 * @param error Optional output pointer for the error value if there was one.
 * @return Output string or `NULL` if the operation failed. The caller should
 *         eventually free this pointer.
 */
char *utf8totex_from_str(const char *s, bool fuzzy, utf8totex_char_t *error)
    __attribute__((nonnull(1)));

/**
 * @brief Translate a UTF-8 string to an ASCII TeX string and write the result
 *        to the given file.
 *
 * @param s Input string.
 * @param fuzzy Whether to assume the input may be TeX. If this parameter is
 *              true, we assume the input string may be valid TeX and try to
 *              avoid translating things that look like macros, braced
 *              expressions or math mode expressions.
 * @param f File to write to.
 * @param error Optional output pointer for the error value if there was one.
 * @return `0` on success.
 */
int utf8totex_fputs(const char *s, bool fuzzy, FILE *f,
    utf8totex_char_t *error) __attribute__((nonnull(1, 3)));

/* Low level interface.
 *
 * It is unlikely you will need this unless you need to move
 * character-by-character or avoid dynamic memory allocation for some reason.
 */

/**
 * @brief Translate a single UTF-8 character into TeX output.
 *
 * See the definition of `utf8totex_char_t` for how to interpret the return value of
 * this function. Note that it is entirely the caller's responsibility to
 * pre-decode their string input into UTF-8 characters. See the implementation
 * of `utf8totex_fputs` for an example of this.
 *
 * @param s An output pointer to write TeX escape sequences into. This pointer
 *          will end up pointing at a static constant string, valid for the
 *          lifetime of the program, that should not be freed.
 * @param c The input UTF-8 character.
 * @return See the definition of `utf8totex_char_t` for how to interpret this value.
 */
utf8totex_char_t utf8totex_from_char(const char **s, uint32_t c) __attribute__((nonnull));
