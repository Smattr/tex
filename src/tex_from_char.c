#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "tex/tex.h"

#if 0
tex_char_t tex_from_char(const char **s, uint32_t c) {
    assert(s != NULL);

    switch (c) {

        /* Standard LaTeX special characters */
        case L'\\':
            *s = "{\\letterbackslash}";
            return TEX_SEQUENCE;
        case L'&':  return "{\\&}";
        case L'%':  return "{\\%}";
        case L'$':  return "{\\$}";
        case L'#':  return "{\\#}";
        case L'_':  return "{\\letterunderscore}";
        case L'{':  return "{\\letteropenbrace}";
        case L'}':  return "{\\letterclosebrace}";
        case L'~':  return "{\\lettertilde}";
        case L'^':  return "{\\letterhat}";

        /* https://en.wikibooks.org/wiki/LaTeX/Special_Characters:
         *
         * > Less than < and greater than >[edit]
         * >   The two symbols '<' and '>' are actually ASCII characters, but
         * >   you may have noticed that they will print '¡' and '¿'
         * >   respectively. This is a font encoding issue. If you want them to
         * >   print their real symbol, you will have to use another font
         * >   encoding such as T1, loaded with the fontenc package. See Fonts
         * >   for more details on font encoding.
         * >
         * >   Alternatively, they can be printed with dedicated commands:
         * >
         * >     \textless
         * >     \textgreater
         *
         */
        case L'<':  return "{\\textless}";
        case L'>':  return "{\\textgreater}";

        /* Accented letters */
        case L'à':  return "{\\`a}";   /* grave */
        case L'á':  return "{\\'a}";   /* acute */
        case L'â':  return "{\\^a}";   /* circumflex */
        case L'ä':  return "{\\\"a}";  /* umlaut */
        case L'a̋':  return "{\\H a}";  /* double acute */
        case L'ã':  return "{\\~a}";   /* tilde */
        case L'a̧':  return "{\\c a}";  /* cedilla */
        case L'ā':  return "{\\=a}";   /* macron */
        case L'a̱':  return "{\\b a}";  /* macron below */
        case L'ȧ':  return "{\\.a}";   /* overdot */
        case L'ă':  return "{\\u a}";  /* breve */
        case L'ǎ':  return "{\\v a}";  /* caron */
        case L'a͡':  return "{\\t a}";  /* tie */
        case L'ạ':  return "{\\d a}";  /* underdot */
        case L'å':  return "{\\r a}";  /* overring */
        case L'ą':  return "{\\k a}";  /* ogonek */
        case L'é':  return "{\\'e}";
        case L'ő':  return "{\\H o}";
        case L'ο̩':  return "{\\b o}";
        case L'ş':  return "{\\c s}";

        /* Superscript and subscript */
        case L'₀':  return "\\textsubscript{0}";
        case L'₁':  return "\\textsubscript{1}";
        case L'₂':  return "\\textsubscript{2}";
        case L'₃':  return "\\textsubscript{3}";
        case L'₄':  return "\\textsubscript{4}";
        case L'₅':  return "\\textsubscript{5}";
        case L'₆':  return "\\textsubscript{6}";
        case L'₇':  return "\\textsubscript{7}";
        case L'₈':  return "\\textsubscript{8}";
        case L'₉':  return "\\textsubscript{9}";
        case L'ᴬ':  return "\\textsuperscript{A}";
        case L'ᴮ':  return "\\textsuperscript{B}";
        case L'ᴰ':  return "\\textsuperscript{D}";
        case L'ᴱ':  return "\\textsuperscript{E}";
        case L'ᴳ':  return "\\textsuperscript{G}";
        case L'ᴴ':  return "\\textsuperscript{H}";
        case L'ᴵ':  return "\\textsuperscript{I}";
        case L'ᴶ':  return "\\textsuperscript{J}";
        case L'ᴷ':  return "\\textsuperscript{K}";
        case L'ᴸ':  return "\\textsuperscript{L}";
        case L'ᴹ':  return "\\textsuperscript{M}";
        case L'ᴺ':  return "\\textsuperscript{N}";
        case L'ᴼ':  return "\\textsuperscript{O}";
        case L'ᴾ':  return "\\textsuperscript{P}";
        case L'ᴿ':  return "\\textsuperscript{R}";
        case L'ᵀ':  return "\\textsuperscript{T}";
        case L'ᵁ':  return "\\textsuperscript{U}";
        case L'ⱽ':  return "\\textsuperscript{V}";
        case L'ᵂ':  return "\\textsuperscript{W}";
#if 0
        /* small caps; what even are they? */
        case L'ᶦ':  ???
        case L'ᶫ':  ???
        case L'ᶰ':  ???
        case L'ᶸ':  ???                   
#endif
        case L'ᵃ':  return "\\textsuperscript{a}";
        case L'ᵇ':  return "\\textsuperscript{b}";
        case L'ᶜ':  return "\\textsuperscript{c}";
        case L'ᵈ':  return "\\textsuperscript{d}";
        case L'ᵉ':  return "\\textsuperscript{e}";
        case L'ᶠ':  return "\\textsuperscript{f}";
        case L'ᵍ':  return "\\textsuperscript{g}";
        case L'ʰ':  return "\\textsuperscript{h}";
        case L'ⁱ':  return "\\textsuperscript{i}";
        case L'ʲ':  return "\\textsuperscript{j}";
        case L'ᵏ':  return "\\textsuperscript{k}";
        case L'ˡ':  return "\\textsuperscript{l}";
        case L'ᵐ':  return "\\textsuperscript{m}";
        case L'ⁿ':  return "\\textsuperscript{n}";
        case L'ᵒ':  return "\\textsuperscript{o}";
        case L'ᵖ':  return "\\textsuperscript{p}";
        case L'ʳ':  return "\\textsuperscript{r}";
        case L'ˢ':  return "\\textsuperscript{s}";
        case L'ᵗ':  return "\\textsuperscript{t}";
        case L'ᵘ':  return "\\textsuperscript{u}";
        case L'ᵛ':  return "\\textsuperscript{v}";
        case L'ʷ':  return "\\textsuperscript{w}";
        case L'ˣ':  return "\\textsuperscript{x}";
        case L'ʸ':  return "\\textsuperscript{y}";
        case L'ᶻ':  return "\\textsuperscript{z}";
        case L'ₐ':  return "\\textsubscript{a}";
        case L'ₑ':  return "\\textsubscript{e}";
        case L'ₕ':  return "\\textsubscript{h}";
        case L'ᵢ':  return "\\textsubscript{i}";
        case L'ⱼ':  return "\\textsubscript{j}";
        case L'ₖ':  return "\\textsubscript{k}";
        case L'ₗ':  return "\\textsubscript{l}";
        case L'ₘ':  return "\\textsubscript{m}";
        case L'ₙ':  return "\\textsubscript{n}";
        case L'ₒ':  return "\\textsubscript{o}";
        case L'ₚ':  return "\\textsubscript{p}";
        case L'ᵣ':  return "\\textsubscript{r}";
        case L'ₛ':  return "\\textsubscript{s}";
        case L'ₜ':  return "\\textsubscript{t}";
        case L'ᵤ':  return "\\textsubscript{u}";
        case L'ᵥ':  return "\\textsubscript{v}";
        case L'ₓ':  return "\\textsubscript{x}";

        /* Greek */
        case L'τ':  return "$\\tau$";
        /* XXX: the rest of Greek */

        /* Greek superscripts */
        case L'ᵝ':  return "\\textsuperscript{$\\beta$}"; 
        /*ᵞ   ᵟ   ᵋ           ᶿ   ᶥ                                           ᶹ   ᵠ   ᵡ       
        Subscript minuscule     ᵦ   ᵧ                                                       ᵨ               ᵩ   ᵪ   
        ᶛ ᶜ ᶝ ᶞ ᶟ ᶠ ᶡ ᶢ ᶣ ᶤ ᶥ ᶦ ᶧ ᶨ ᶩ ᶪ ᶫ ᶬ ᶭ ᶮ ᶯ ᶰ ᶱ ᶲ ᶳ ᶴ ᶵ ᶶ ᶷ ᶸ ᶹ ᶺ ᶻ ᶼ ᶽ ᶾ ᶿ.*/

        /* German, Scandinavian */
        case L'ß':  return "{\\ss}";
        case L'æ':  return "{\\ae}";
        case L'Æ':  return "{\\AE}";
        case L'ł':  return "{\\l}";
        case L'ø':  return "{\\o}";

        /* Other misc symbols */
        case L'§':  return "{\\S}";
        case L'—':  return "{\\textemdash}";
        case L'¶':  return "{\\P}";

    }

    assert(c <= 127 && "unhandled extended character");

    return NULL;
}
#endif

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
        case L'¯':                 return TEX_UNSUPPORTED;
        case L'°':                 SEQ_TC("{\\textdegree}");
        case L'±':                 SEQ("$\\pm$");
        case L'²':                 SEQ("\\textsuperscript{2}");
        case L'³':                 SEQ("\\textsuperscript{3}");
        case L'´':                 return TEX_UNSUPPORTED;
        case L'µ':                 SEQ("$\\mu$");
        case L'¶':                 SEQ("{\\P}");
        case L'·':                 SEQ("\\textperiodcentered}");
        case L'¸':                 return TEX_UNSUPPORTED;
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
        case L'⁰':                 SEQ("\\textsuperscript{0}");
        case L'ⁱ':                 SEQ("\\textsuperscript{i}");
        case 0x2072 ... 0x2073:    return TEX_INVALID;
        case L'⁴':                 SEQ("\\textsuperscript{4}");
        case L'⁵':                 SEQ("\\textsuperscript{5}");
        case L'⁶':                 SEQ("\\textsuperscript{6}");
        case L'⁷':                 SEQ("\\textsuperscript{7}");
        case L'⁸':                 SEQ("\\textsuperscript{8}");
        case L'⁹':                 SEQ("\\textsuperscript{9}");
        /* XXX */
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

#undef SEQ
#undef SEQ_T1
#undef SEQ_TC
#undef ACC

    }

    return TEX_UNSUPPORTED;
}
