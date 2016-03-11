#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "tex/tex.h"

/* The translation from UTF-8 to TeX escape sequences in this file is currently
 * quite incomplete. It has been written partially by various scripts and
 * optimised in some places to provide a shorter character sequence. If you
 * find a mistake or need something that isn't here, please let me know.
 * 
 * Note that it also makes some compromises, like outputting all Greek
 * characters in math mode because this can be done without including any extra
 * fonts. This is probably not ideal if you are writing a document entirely in
 * these characters. Please let me know if this bothers you and you have a
 * better suggestion for how to handle these.
 */

tex_char_t tex_from_char(char *s, uint32_t c) {
    assert(s != NULL);

    switch (c) {

#define SEQ(str) \
    do { \
        assert(sizeof(str) <= TEX_MAX_SEQUENCE_LEN); \
        strcpy(s, (str)); \
        return TEX_SEQUENCE; \
    } while (0)

#define SEQ_T1(str) \
    do { \
        assert(sizeof(str) <= TEX_MAX_SEQUENCE_LEN); \
        strcpy(s, (str)); \
        return TEX_SEQUENCE_T1; \
    } while (0)

#define SEQ_TC(str) \
    do { \
        assert(sizeof(str) <= TEX_MAX_SEQUENCE_LEN); \
        strcpy(s, (str)); \
        return TEX_SEQUENCE_TEXTCOMP; \
    } while (0)

#define ACC(str) \
    do { \
        assert(sizeof(str) <= TEX_MAX_SEQUENCE_LEN); \
        strcpy(s, (str)); \
        return TEX_MODIFIER; \
    } while (0)

        case 0x0000 ... 0x0008:    return TEX_INVALID;
        case L'\t':                return TEX_ASCII;
        case L'\n':                return TEX_ASCII;
        case 0x000b ... 0x000c:    return TEX_INVALID;
        case L'\r':                return TEX_ASCII;
        case 0x000e ... 0x001f:    return TEX_INVALID;
        case L' ' ... L'"':        return TEX_ASCII;
        case L'#':                 SEQ("{\\#}");
        case L'$':                 SEQ("{\\$}");
        case L'%':                 SEQ("{\\%}");
        case L'&':                 SEQ("{\\&}");
        case L'\'' ... L';':       return TEX_ASCII;
        case L'<':                 SEQ("{\\textless}");
        case L'=':                 return TEX_ASCII;
        case L'>':                 SEQ("{\\textgreater}");
        case L'?' ... L'[':        return TEX_ASCII;
        case L'\\':                SEQ("{\\letterbackslash}");
        case L']':                 return TEX_ASCII;
        case L'^':                 SEQ("{\\letterhat}");
        case L'_':                 SEQ("{\\letterunderscore}");
        case L'`':                 SEQ("{\\`}");
        case L'a' ... L'z':        return TEX_ASCII;
        case L'{':                 SEQ("{\\letteropenbrace}");
        case L'|':                 return TEX_ASCII;
        case L'}':                 SEQ("{\\letterclosebrace}");
        case L'~':                 SEQ("{\\lettertilde}");
        case 0x007f ... 0x009f:    return TEX_INVALID;
        case 0x00a0:               SEQ("~"); /* non-breaking space */
        case L'¡':                 SEQ("{\\textexclamdown}");
        case L'¢':                 SEQ("{\\textcent}");
        case L'£':                 SEQ("{\\pounds}");
        case L'¤':                 SEQ_TC("{\\textcurrency}");
        case L'¥':                 SEQ_TC("{\\textyen}");
        case L'¦':                 SEQ_TC("{\\textbrokenbar}");
        case L'§':                 SEQ("{\\textsection}");
        case L'¨':                 SEQ_TC("{\\textasciidieresis}");
        case L'©':                 SEQ("{\\copyright}");
        case L'ª':                 SEQ("{\\textordfeminine}");
        case L'«':                 SEQ_T1("{\\guillemotleft}");
        case L'¬':                 SEQ_TC("{\\textlnot}");
        case 0x00ad:               SEQ("\\-"); /* soft hyphen */
        case L'®':                 SEQ("{\\textregistered}");
        case L'¯':                 SEQ("{\\= }");
        case L'°':                 SEQ_TC("{\\textdegree}");
        case L'±':                 SEQ("$\\pm$");
        case L'²':                 SEQ("\\textsuperscript{2}");
        case L'³':                 SEQ("\\textsuperscript{3}");
        case L'´':                 SEQ("{\\' }");
        case L'µ':                 SEQ("$\\mu$");
        case L'¶':                 SEQ("{\\P}");
        case L'·':                 SEQ("\\textperiodcentered}");
        case L'¸':                 SEQ("{\\c }");
        case L'¹':                 SEQ("\\textsuperscript{1}");
        case L'º':                 SEQ("{\\textordmasculine}");
        case L'»':                 SEQ_T1("{\\guillemotright}");
        case L'¼':                 SEQ_TC("{\\textonequarter}");
        case L'½':                 SEQ_TC("{\\textonehalf}");
        case L'¾':                 SEQ_TC("{\\textthreequarters}");
        case L'¿':                 SEQ("{\\textquestiondown}");
        case L'À':                 SEQ("{\\`A}");
        case L'Á':                 SEQ("{\\'A}");
        case L'Â':                 SEQ("{\\^A}");
        case L'Ã':                 SEQ("{\\~A}");
        case L'Ä':                 SEQ("{\\\"A}");
        case L'Å':                 SEQ("{\\AA}");
        case L'Æ':                 SEQ("{\\AE}");
        case L'Ç':                 SEQ("{\\c C}");
        case L'È':                 SEQ("{\\`E}");
        case L'É':                 SEQ("{\\'E}");
        case L'Ê':                 SEQ("{\\^E}");
        case L'Ë':                 SEQ("{\\\"E}");
        case L'Ì':                 SEQ("{\\`I}");
        case L'Í':                 SEQ("{\\'I}");
        case L'Î':                 SEQ("{\\^I}");
        case L'Ï':                 SEQ("{\\\"I}");
        case L'Ð':                 SEQ_T1("{\\DJ}");
        case L'Ñ':                 SEQ("{\\~N}");
        case L'Ò':                 SEQ("{\\`O}");
        case L'Ó':                 SEQ("{\\'O}");
        case L'Ô':                 SEQ("{\\^O}");
        case L'Õ':                 SEQ("{\\~O}");
        case L'Ö':                 SEQ("{\\\"O}");
        case L'×':                 SEQ("$\\times$");
        case L'Ø':                 SEQ("{\\O}");
        case L'Ù':                 SEQ("{\\`U}");
        case L'Ú':                 SEQ("{\\'U}");
        case L'Û':                 SEQ("{\\^U}");
        case L'Ü':                 SEQ("{\\\"U}");
        case L'Ý':                 SEQ("{\\'Y}");
        case L'Þ':                 SEQ_T1("{\\TH}");
        case L'ß':                 SEQ("{\\ss}");
        case L'à':                 SEQ("{\\`a}");
        case L'á':                 SEQ("{\\'a}");
        case L'â':                 SEQ("{\\^a}");
        case L'ã':                 SEQ("{\\~a}");
        case L'ä':                 SEQ("{\\\"a}");
        case L'å':                 SEQ("{\\o a}");
        case L'æ':                 SEQ("{\\ae}");
        case L'ç':                 SEQ("{\\c c}");
        case L'è':                 SEQ("{\\`e}");
        case L'é':                 SEQ("{\\'e}");
        case L'ê':                 SEQ("{\\^e}");
        case L'ë':                 SEQ("{\\\"e}");
        case L'ì':                 SEQ("{\\`i}");
        case L'í':                 SEQ("{\\'i}");
        case L'î':                 SEQ("{\\^i}");
        case L'ï':                 SEQ("{\\\"i}");
        case L'ð':                 return TEX_UNSUPPORTED;
        case L'ñ':                 SEQ("{\\~n}");
        case L'ò':                 SEQ("{\\`o}");
        case L'ó':                 SEQ("{\\'o}");
        case L'ô':                 SEQ("{\\^o}");
        case L'õ':                 SEQ("{\\~o}");
        case L'ö':                 SEQ("{\\\"o}");
        case L'÷':                 SEQ("$\\div$");
        case L'ø':                 SEQ("{\\o}");
        case L'ù':                 SEQ("{\\`u}");
        case L'ú':                 SEQ("{\\'u}");
        case L'û':                 SEQ("{\\^u}");
        case L'ü':                 SEQ("{\\\"u}");
        case L'ý':                 SEQ("{\\'y}");
        case L'þ':                 SEQ_T1("{\\th}");
        case L'ÿ':                 SEQ("{\\\"y}");
        case L'Ā':                 SEQ("{\\=A}");
        case L'ā':                 SEQ("{\\=a}");
        case L'Ă':                 SEQ("{\\u A}");
        case L'ă':                 SEQ("{\\u a}");
        case L'Ą':                 SEQ("{\\k A}");
        case L'ą':                 SEQ("{\\k a}");
        case L'Ć':                 SEQ("{\\'C}");
        case L'ć':                 SEQ("{\\'c}");
        case L'Ĉ':                 SEQ("{\\^C}");
        case L'ĉ':                 SEQ("{\\^c}");
        case L'Ċ':                 SEQ("{\\.C}");
        case L'ċ':                 SEQ("{\\.c}");
        case L'Č':                 SEQ("{\\v C}");
        case L'č':                 SEQ("{\\v c}");
        case L'Ď':                 SEQ("{\\v D}");
        case L'ď':                 SEQ("{\\v d}");

        case L'Ł':                 SEQ("{\\L}");
        case L'ł':                 SEQ("{\\l}");

        case L'ˆ':                 ACC("{\\^");
        case L'ˇ':                 ACC("{\\v ");

        case L'ˉ':                 ACC("{\\=");
        case L'ˊ':                 ACC("{\\'");
        case L'ˋ':                 ACC("{\\`");

        case L'ˍ':                 ACC("{\\b ");


        case 0x0300:               ACC("{\\`");
        case 0x0301:               ACC("{\\'");
        case 0x0302:               ACC("{\\^");
        case 0x0303:               ACC("{\\~");
        case 0x0304:               ACC("{\\=");
        case 0x0305:               return TEX_UNSUPPORTED;
        case 0x0306:               ACC("{\\u ");
        case 0x0307:               ACC("{\\.");
        case 0x0308:               ACC("{\\\"");
        case 0x0309:               return TEX_UNSUPPORTED;
        case 0x030a:               ACC("{\\o ");
        case 0x030b:               ACC("{\\H ");
        case 0x030c:               ACC("{\\v ");
        /* XXX */
        case 0x0327:               ACC("{\\c ");
        /* XXX */
        case 0x0331:               ACC("{\\b ");
        /* XXX */
        case 0x0361:               ACC("{\\t ");

        /* Greek */
        case L'Α':                 SEQ("$A$");
        case L'Β':                 SEQ("$B$");
        case L'Γ':                 SEQ("$\\Gamma$");
        case L'Δ':                 SEQ("$\\Delta$");
        case L'Ε':                 SEQ("$E$");
        case L'Ζ':                 SEQ("$Z$");
        case L'Η':                 SEQ("$H$");
        case L'Θ':                 SEQ("$\\Theta$");
        case L'Ι':                 SEQ("$I$");
        case L'Κ':                 SEQ("$K$");
        case L'Λ':                 SEQ("$\\Lambda$");
        case L'Μ':                 SEQ("$M$");
        case L'Ν':                 SEQ("$N$");
        case L'Ξ':                 SEQ("$\\Xi$");
        case L'Ο':                 SEQ("$O$");
        case L'Π':                 SEQ("$\\Pi$");
        case L'Ρ':                 SEQ("$P$");
        case 0x03a2:               return TEX_INVALID;
        case L'Σ':                 SEQ("$\\Sigma$");
        case L'Τ':                 SEQ("$T$");
        case L'Υ':                 SEQ("$Y$");
        case L'Φ':                 SEQ("$\\Phi$");
        case L'Χ':                 SEQ("$X$");
        case L'Ψ':                 SEQ("$\\Psi$");
        case L'Ω':                 SEQ("$\\Omega$");
        /* XXX */
        case L'α':                 SEQ("$\\alpha$");
        case L'β':                 SEQ("$\\beta$");
        case L'γ':                 SEQ("$\\gamma$");
        case L'δ':                 SEQ("$\\delta$");
        case L'ε':                 SEQ("$\\varepsilon$");
        case L'ζ':                 SEQ("$\\zeta$");
        case L'η':                 SEQ("$\\eta$");
        case L'θ':                 SEQ("$\\theta$");
        case L'ι':                 SEQ("$\\iota$");
        case L'κ':                 SEQ("$\\kappa$");
        case L'λ':                 SEQ("$\\lambda$");
        case L'μ':                 SEQ("$\\mu$");
        case L'ν':                 SEQ("$\\nu$");
        case L'ξ':                 SEQ("$\\xi$");
        case L'ο':                 SEQ("$o$");
        case L'π':                 SEQ("$\\pi$");
        case L'ρ':                 SEQ("$\\rho$");
        case L'ς':                 SEQ("$\\varsigma$");
        case L'σ':                 SEQ("$\\sigma$");
        case L'τ':                 SEQ("$\\tau$");
        case L'υ':                 SEQ("$\\upsilon$");
        case L'φ':                 SEQ("$\\phi$");
        case L'χ':                 SEQ("$\\chi$");
        case L'ψ':                 SEQ("$\\psi$");
        case L'ω':                 SEQ("$\\omega$");

        case L'—':                 SEQ("{\\textemdash}");

        /* XXX */
        case L'⁰':                 SEQ("\\textsuperscript{0}");
        case L'ⁱ':                 SEQ("\\textsuperscript{i}");
        case 0x2072 ... 0x2073:    return TEX_INVALID;
        case L'⁴':                 SEQ("\\textsuperscript{4}");
        case L'⁵':                 SEQ("\\textsuperscript{5}");
        case L'⁶':                 SEQ("\\textsuperscript{6}");
        case L'⁷':                 SEQ("\\textsuperscript{7}");
        case L'⁸':                 SEQ("\\textsuperscript{8}");
        case L'⁹':                 SEQ("\\textsuperscript{9}");
        case L'⁺':                 SEQ("\\textsuperscript{+}");
        case L'⁻':                 SEQ("\\textsuperscript{-}");
        case L'⁼':                 SEQ("\\textsuperscript{=}");
        case L'⁽':                 SEQ("\\textsuperscript{(}");
        case L'⁾':                 SEQ("\\textsuperscript{)}");
        case L'ⁿ':                 SEQ("\\textsuperscript{n}");
        case L'₀':                 SEQ("\\textsubscript{0}");
        case L'₁':                 SEQ("\\textsubscript{1}");
        case L'₂':                 SEQ("\\textsubscript{2}");
        case L'₃':                 SEQ("\\textsubscript{3}");
        case L'₄':                 SEQ("\\textsubscript{4}");
        case L'₅':                 SEQ("\\textsubscript{5}");
        case L'₆':                 SEQ("\\textsubscript{6}");
        case L'₇':                 SEQ("\\textsubscript{7}");
        case L'₈':                 SEQ("\\textsubscript{8}");
        case L'₉':                 SEQ("\\textsubscript{9}");
        case L'₊':                 SEQ("\\textsubscript{+}");
        case L'₋':                 SEQ("\\textsubscript{-}");
        case L'₌':                 SEQ("\\textsubscript{=}");
        case L'₍':                 SEQ("\\textsubscript{(}");
        case L'₎':                 SEQ("\\textsubscript{)}");
        case 0x208f:               return TEX_INVALID;
        /* XXX */
        case 0x209d ... 0x209f:    return TEX_INVALID;

        /* UTF-8 characters are a maximum of 21 bits */
        case 1 << 21 ... UINT32_MAX:
            return TEX_INVALID;

        default:
            return TEX_UNSUPPORTED;
            
#undef SEQ
#undef SEQ_T1
#undef SEQ_TC
#undef ACC

    }
}
