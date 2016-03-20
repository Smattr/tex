#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

/**
 * @brief A TeX environment, describing font encoding and what packages are in
 *        use.
 *
 * To understand font encodings, it is recommended to refer to "LaTeX font
 * encodings" by Frank Mittelbach, Robin Fairbairns and Werner Lemberg.
 */
typedef struct {
    enum {
        UTF8TOTEX_FE_OT1 = 0, /**< OT1 (default) */
        UTF8TOTEX_FE_OT2,     /**< OT2 (Cyrillic) */
        UTF8TOTEX_FE_OT3,     /**< OT3 (UW IPA) */
        UTF8TOTEX_FE_OT4,     /**< OT4 (Polish) */
        /* OT5 is not allocated */
        UTF8TOTEX_FE_OT6,     /**< OT6 (Armenian) */
        UTF8TOTEX_FE_T1,      /**< T1 (Cork) */
        UTF8TOTEX_FE_T2A,     /**< T2A (Cyrillic) */
        UTF8TOTEX_FE_T2B,     /**< T2B (Cyrillic) */
        UTF8TOTEX_FE_T2C,     /**< T2C (Cyrillic) */
        UTF8TOTEX_FE_T3,      /**< T3 (IPA) */
        UTF8TOTEX_FE_T4,      /**< T4 (African Latin) */
        UTF8TOTEX_FE_T5,      /**< T5 (Vietnamese) */
        UTF8TOTEX_FE_TS1,     /**< TS1 (Text companion, Cork) */
        UTF8TOTEX_FE_TS3,     /**< TS3 (IPA) */
        UTF8TOTEX_FE_X2,      /**< X2 (Cyrillic container) */
        UTF8TOTEX_FE_OML,     /**< OML (Math italic) */
        UTF8TOTEX_FE_OMS,     /**< OMS (Math) */
        UTF8TOTEX_FE_OMX,     /**< OMX (Math extension) */

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

    UTF8TOTEX_EOF = EOF,
        /**< Something went wrong during output or internal resource
             allocation. */

    UTF8TOTEX_INVALID,
        /**< The given data was not a valid unicode character. */

    UTF8TOTEX_UNSUPPORTED,
        /**< The data was a valid unicode character, but there is no matching
             TeX escape sequence for it in the given environment. This may mean
             that the valid escape sequence has just not been implemented
             yet. */

    UTF8TOTEX_BAD_MODIFIER,
        /**< A modifier appeared after something which no modifier should appear
             afterwards (e.g. start of string). */

    UTF8TOTEX_BAD_LITERAL,
        /**< A non-ASCII character occurred inside a literal block or in
             something that was interpreted as a TeX macro. This error can only
             occur when fuzzy=true. */

    UTF8TOTEX_ASCII,
        /**< The given data was an ASCII character and can be output as-is.
             However, beware that if the next piece of data is a
             `UTF8TOTEX_MODIFIER`, it may change this character's meaning. */

    UTF8TOTEX_SEQUENCE,
        /**< The given data was escaped into a sequence of ASCII characters that
             are now in the `s` output buffer as a NUL-terminated string that
             can be output. */

    UTF8TOTEX_MODIFIER,
        /**< The previous character was an ASCII character and needs to be
             modified. The text to output before the character is in the `s`
             output buffer as a NUL-terminated string. The character should be
             followed by the string "}". If the previous character was not an
             ASCII character, you have malformed input. See the handling of this
             in `utf8totex_fputs`. */

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
 * @param env Target TeX environment.
 * @param error Optional output pointer for the error value if there was one.
 * @return Output string or `NULL` if the operation failed. The caller should
 *         eventually free this pointer.
 */
char *utf8totex_from_str(const char *s, bool fuzzy,
    utf8totex_environment_t env, utf8totex_char_t *error)
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
 * @param env Target TeX environment.
 * @param f File to write to.
 * @param error Optional output pointer for the error value if there was one.
 * @return `0` on success.
 */
int utf8totex_fputs(const char *s, bool fuzzy, utf8totex_environment_t env,
    FILE *f, utf8totex_char_t *error) __attribute__((nonnull(1, 4)));

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
 * @param env Target TeX environment.
 * @return See the definition of `utf8totex_char_t` for how to interpret this value.
 */
utf8totex_char_t utf8totex_from_char(const char **s, uint32_t c,
    utf8totex_environment_t env) __attribute__((nonnull));
