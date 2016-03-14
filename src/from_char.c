#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "utf8totex/utf8totex.h"

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

utf8totex_char_t utf8totex_from_char(const char **s, uint32_t c) {
    assert(s != NULL);

    switch (c) {

#define SEQ(str) \
    do { \
        *(s) = (str); \
        return UTF8TOTEX_SEQUENCE; \
    } while (0)

#define SEQ_T1(str) \
    do { \
        *(s) = (str); \
        return UTF8TOTEX_SEQUENCE_T1; \
    } while (0)

#define SEQ_TC(str) \
    do { \
        *(s) = (str); \
        return UTF8TOTEX_SEQUENCE_TEXTCOMP; \
    } while (0)

#define ACC(str) \
    do { \
        *(s) = (str); \
        return UTF8TOTEX_MODIFIER; \
    } while (0)

        /* Basic Latin */
        case 0x0000 ... 0x0008:    return UTF8TOTEX_INVALID;
        case L'\t':                return UTF8TOTEX_ASCII;
        case L'\n':                return UTF8TOTEX_ASCII;
        case 0x000b ... 0x000c:    return UTF8TOTEX_INVALID;
        case L'\r':                return UTF8TOTEX_ASCII;
        case 0x000e ... 0x001f:    return UTF8TOTEX_INVALID;
        case L' ' ... L'"':        return UTF8TOTEX_ASCII;
        case L'#':                 SEQ("{\\#}");
        case L'$':                 SEQ("{\\$}");
        case L'%':                 SEQ("{\\%}");
        case L'&':                 SEQ("{\\&}");
        case L'\'' ... L';':       return UTF8TOTEX_ASCII;
        case L'<':                 SEQ("{\\textless}");
        case L'=':                 return UTF8TOTEX_ASCII;
        case L'>':                 SEQ("{\\textgreater}");
        case L'?' ... L'[':        return UTF8TOTEX_ASCII;
        case L'\\':                SEQ("{\\letterbackslash}");
        case L']':                 return UTF8TOTEX_ASCII;
        case L'^':                 SEQ("{\\letterhat}");
        case L'_':                 SEQ("{\\letterunderscore}");
        case L'`':                 SEQ("{\\`}");
        case L'a' ... L'z':        return UTF8TOTEX_ASCII;
        case L'{':                 SEQ("{\\{}");
        case L'|':                 return UTF8TOTEX_ASCII;
        case L'}':                 SEQ("{\\}}");
        case L'~':                 SEQ("{\\lettertilde}");
        case 0x007f:               return UTF8TOTEX_INVALID;

        /* Latin-1 supplement */
        case 0x0080 ... 0x009f:    return UTF8TOTEX_INVALID;
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
        case L'·':                 SEQ("{\\textperiodcentered}");
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
        case L'å':                 SEQ("{\\aa}");
        case L'æ':                 SEQ("{\\ae}");
        case L'ç':                 SEQ("{\\c c}");
        case L'è':                 SEQ("{\\`e}");
        case L'é':                 SEQ("{\\'e}");
        case L'ê':                 SEQ("{\\^e}");
        case L'ë':                 SEQ("{\\\"e}");
        case L'ì':                 SEQ("{\\`\\i}");
        case L'í':                 SEQ("{\\'\\i}");
        case L'î':                 SEQ("{\\^\\i}");
        case L'ï':                 SEQ("{\\\"\\i}");
        case L'ð':                 return UTF8TOTEX_UNSUPPORTED;
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

        /* Latin Extended-A */
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
        case L'Đ':                 SEQ_T1("{\\DJ}");
        case L'đ':                 SEQ_T1("{\\dj}");
        case L'Ē':                 SEQ("{\\=E}");
        case L'ē':                 SEQ("{\\=e}");
        case L'Ĕ':                 SEQ("{\\u E}");
        case L'ĕ':                 SEQ("{\\u e}");
        case L'Ė':                 SEQ("{\\.E}");
        case L'ė':                 SEQ("{\\.e}");
        case L'Ę':                 SEQ("{\\k E}");
        case L'ę':                 SEQ("{\\k e}");
        case L'Ě':                 SEQ("{\\v E}");
        case L'ě':                 SEQ("{\\v e}");
        case L'Ĝ':                 SEQ("{\\^G}");
        case L'ĝ':                 SEQ("{\\^g}");
        case L'Ğ':                 SEQ("{\\u G}");
        case L'ğ':                 SEQ("{\\u g}");
        case L'Ġ':                 SEQ("{\\.G}");
        case L'ġ':                 SEQ("{\\.g}");
        case L'Ģ':                 SEQ("{\\c G}");
        case L'ģ':                 SEQ("{\\c g}");
        case L'Ĥ':                 SEQ("{\\^H}");
        case L'ĥ':                 SEQ("{\\^h}");
        case L'Ħ':                 return UTF8TOTEX_UNSUPPORTED; /* XXX: we could do this with T3 */
        case L'ħ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ĩ':                 SEQ("{\\~I}");
        case L'ĩ':                 SEQ("{\\~\\i}");
        case L'Ī':                 SEQ("{\\=I}");
        case L'ī':                 SEQ("{\\=\\i}");
        case L'Ĭ':                 SEQ("{\\u I}");
        case L'ĭ':                 SEQ("{\\u\\i}");
        case L'Į':                 SEQ("{\\k I}");
        case L'į':                 SEQ("{\\k i}");
        case L'İ':                 SEQ("{\\.I}");
        case L'ı':                 SEQ("{\\i}");
        case L'Ĳ':                 SEQ("IJ"); /* no native ligatures it seems */
        case L'ĳ':                 SEQ("ij");
        case L'Ĵ':                 SEQ("{\\^J}");
        case L'ĵ':                 SEQ("{\\^\\j}");
        case L'Ķ':                 SEQ("{\\c K}");
        case L'ķ':                 SEQ("{\\c k}");
        case L'ĸ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ĺ':                 SEQ("{\\'L}");
        case L'ĺ':                 SEQ("{\\'l}");
        case L'Ļ':                 SEQ("{\\c L}");
        case L'ļ':                 SEQ("{\\c l}");
        case L'Ľ':                 SEQ("{\\v L}");
        case L'ľ':                 SEQ("{\\v l}");
        case L'Ŀ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'ŀ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ł':                 SEQ("{\\L}");
        case L'ł':                 SEQ("{\\l}");
        case L'Ń':                 SEQ("{\\'N}");
        case L'ń':                 SEQ("{\\'n}");
        case L'Ņ':                 SEQ("{\\c N}");
        case L'ņ':                 SEQ("{\\c n}");
        case L'Ň':                 SEQ("{\\v N}");
        case L'ň':                 SEQ("{\\v n}");
        case L'ŉ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ŋ':                 SEQ_T1("{\\NG}");
        case L'ŋ':                 SEQ_T1("{\\ng}");
        case L'Ō':                 SEQ("{\\=O}");
        case L'ō':                 SEQ("{\\=o}");
        case L'Ŏ':                 SEQ("{\\u O}");
        case L'ŏ':                 SEQ("{\\u o}");
        case L'Ő':                 SEQ("{\\H O}");
        case L'ő':                 SEQ("{\\H o}");
        case L'Œ':                 SEQ("{\\OE}");
        case L'œ':                 SEQ("{\\oe}");
        case L'Ŕ':                 SEQ("{\\'R}");
        case L'ŕ':                 SEQ("{\\'r}");
        case L'Ŗ':                 SEQ("{\\c R}");
        case L'ŗ':                 SEQ("{\\c r}");
        case L'Ř':                 SEQ("{\\v R}");
        case L'ř':                 SEQ("{\\v r}");
        case L'Ś':                 SEQ("{\\'S}");
        case L'ś':                 SEQ("{\\'s}");
        case L'Ŝ':                 SEQ("{\\^S}");
        case L'ŝ':                 SEQ("{\\^s}");
        case L'Ş':                 SEQ("{\\c S}");
        case L'ş':                 SEQ("{\\c s}");
        case L'Š':                 SEQ("{\\v S}");
        case L'š':                 SEQ("{\\v s}");
        case L'Ţ':                 SEQ("{\\c T}");
        case L'ţ':                 SEQ("{\\c t}");
        case L'Ť':                 SEQ("{\\v T}");
        case L'ť':                 SEQ("{\\v t}");
        case L'Ŧ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'ŧ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ũ':                 SEQ("{\\~U}");
        case L'ũ':                 SEQ("{\\~u}");
        case L'Ū':                 SEQ("{\\=U}");
        case L'ū':                 SEQ("{\\=u}");
        case L'Ŭ':                 SEQ("{\\u U}");
        case L'ŭ':                 SEQ("{\\u u}");
        case L'Ů':                 SEQ("{\\r U}");
        case L'ů':                 SEQ("{\\r u}");
        case L'Ű':                 SEQ("{\\H U}");
        case L'ű':                 SEQ("{\\H u}");
        case L'Ų':                 SEQ("{\\k U}");
        case L'ų':                 SEQ("{\\k u}");
        case L'Ŵ':                 SEQ("{\\^W}");
        case L'ŵ':                 SEQ("{\\^w}");
        case L'Ŷ':                 SEQ("{\\^Y}");
        case L'ŷ':                 SEQ("{\\^y}");
        case L'Ÿ':                 SEQ("{\\\"Y}");
        case L'Ź':                 SEQ("{\\'Z}");
        case L'ź':                 SEQ("{\\'z}");
        case L'Ż':                 SEQ("{\\.Z}");
        case L'ż':                 SEQ("{\\.z}");
        case L'Ž':                 SEQ("{\\v Z}");
        case L'ž':                 SEQ("{\\v z}");
        case L'ſ':                 return UTF8TOTEX_UNSUPPORTED;

        /* Latin Extended-B */
        /* XXX */
        case L'Ǆ':                 SEQ("D{\\v Z}");
        case L'ǅ':                 SEQ("D{\\v z}");
        case L'ǆ':                 SEQ("d{\\v z}");
        case L'Ǉ':                 SEQ("LJ");
        case L'ǈ':                 SEQ("Lj");
        case L'ǉ':                 SEQ("lj");
        case L'Ǌ':                 SEQ("NJ");
        case L'ǋ':                 SEQ("Nj");
        case L'ǌ':                 SEQ("nj");
        case L'Ǎ':                 SEQ("{\\v A}");
        case L'ǎ':                 SEQ("{\\v a}");
        case L'Ǐ':                 SEQ("{\\v I}");
        case L'ǐ':                 SEQ("{\\v\\i}");
        case L'Ǒ':                 SEQ("{\\v O}");
        case L'ǒ':                 SEQ("{\\v o}");
        case L'Ǔ':                 SEQ("{\\v U}");
        case L'ǔ':                 SEQ("{\\v u}");
        case L'Ǖ' ... L'ǡ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ǣ':                 SEQ("{\\=\\AE}");
        case L'ǣ':                 SEQ("{\\=\\ae}");
        case L'Ǥ':
        case L'ǥ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ǧ':                 SEQ("{\\v G}");
        case L'ǧ':                 SEQ("{\\v g}");
        case L'Ǩ':                 SEQ("{\\v K}");
        case L'ǩ':                 SEQ("{\\v k}");
        case L'Ǫ':                 SEQ("{\\k O}");
        case L'ǫ':                 SEQ("{\\k o}");
        case L'Ǭ' ... L'ǯ':        return UTF8TOTEX_UNSUPPORTED;
        case L'ǰ':                 SEQ("{\\v\\j}");
        case L'Ǳ':                 SEQ("DZ");
        case L'ǲ':                 SEQ("Dz");
        case L'ǳ':                 SEQ("dz");
        case L'Ǵ':                 SEQ("{\\'G}");
        case L'ǵ':                 SEQ("{\\'g}");
        case L'Ƕ':
        case L'Ƿ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ǹ':                 SEQ("{\\`N}");
        case L'ǹ':                 SEQ("{\\`n}");
        case L'Ǻ':
        case L'ǻ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ǽ':                 SEQ("{\\'\\AE}");
        case L'ǽ':                 SEQ("{\\'\\ae}");
        case L'Ǿ':                 SEQ("{\\'\\O}");
        case L'ǿ':                 SEQ("{\\'\\o}");
        case L'Ȁ' ... L'ȝ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ȟ':                 SEQ("{\\v H}");
        case L'ȟ':                 SEQ("{\\v h}");
        case L'Ƞ' ... L'ȥ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ȧ':                 SEQ("{\\.A}");
        case L'ȧ':                 SEQ("{\\.a}");
        case L'Ȩ':                 SEQ("{\\c E}");
        case L'ȩ':                 SEQ("{\\c e}");
        case L'Ȫ' ... L'ȭ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ȯ':                 SEQ("{\\.O}");
        case L'ȯ':                 SEQ("{\\.o}");
        case L'Ȱ':
        case L'ȱ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ȳ':                 SEQ("{\\=Y}");
        case L'ȳ':                 SEQ("{\\=y}");
        case L'ȴ' ... L'ɏ':        return UTF8TOTEX_UNSUPPORTED;

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
        case 0x0305:               return UTF8TOTEX_UNSUPPORTED;
        case 0x0306:               ACC("{\\u ");
        case 0x0307:               ACC("{\\.");
        case 0x0308:               ACC("{\\\"");
        case 0x0309:               return UTF8TOTEX_UNSUPPORTED;
        case 0x030a:               ACC("{\\r ");
        case 0x030b:               ACC("{\\H ");
        case 0x030c:               ACC("{\\v ");
        /* XXX */
        case 0x0327:               ACC("{\\c ");
        /* XXX */
        case 0x0331:               ACC("{\\b ");
        /* XXX */
        case 0x0361:               ACC("{\\t ");

        /* Greek */
        case L';':                 SEQ("$;$");
        case L'Ϳ':                 SEQ("$J$");
        case 0x0380 ... 0x0383:    return UTF8TOTEX_INVALID;
        case L'΄' ... L'Ά':        return UTF8TOTEX_UNSUPPORTED;
        case L'·':                 SEQ("$\\textperiodcentered$");
        case L'Έ' ... L'Ί':        return UTF8TOTEX_UNSUPPORTED;
        case 0x038b:               return UTF8TOTEX_INVALID;
        case L'Ό':                 return UTF8TOTEX_UNSUPPORTED;
        case 0x038d:               return UTF8TOTEX_INVALID;
        case L'Ύ' ... L'ΐ':        return UTF8TOTEX_UNSUPPORTED;
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
        case 0x03a2:               return UTF8TOTEX_INVALID;
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

        /* Phonetic extensions */
        case L'ᴬ':                 SEQ("\\textsuperscript{A}");
        case L'ᴭ':                 SEQ("\\textsuperscript{\\AE}");
        case L'ᴮ':                 SEQ("\\textsuperscript{B}");
        case L'ᴰ':                 SEQ("\\textsuperscript{D}");
        case L'ᴱ':                 SEQ("\\textsuperscript{E}");
        case L'ᴳ':                 SEQ("\\textsuperscript{G}");
        case L'ᴴ':                 SEQ("\\textsuperscript{H}");
        case L'ᴵ':                 SEQ("\\textsuperscript{I}");
        case L'ᴶ':                 SEQ("\\textsuperscript{J}");
        case L'ᴷ':                 SEQ("\\textsuperscript{K}");
        case L'ᴸ':                 SEQ("\\textsuperscript{L}");
        case L'ᴹ':                 SEQ("\\textsuperscript{M}");
        case L'ᴺ':                 SEQ("\\textsuperscript{N}");
        case L'ᴼ':                 SEQ("\\textsuperscript{O}");
        case L'ᴾ':                 SEQ("\\textsuperscript{P}");
        case L'ᴿ':                 SEQ("\\textsuperscript{R}");
        case L'ᵀ':                 SEQ("\\textsuperscript{T}");
        case L'ᵁ':                 SEQ("\\textsuperscript{U}");
        case L'ᵂ':                 SEQ("\\textsuperscript{W}");
        case L'ᵃ':                 SEQ("\\textsuperscript{a}");
        case L'ᵇ':                 SEQ("\\textsuperscript{b}");
        case L'ᵈ':                 SEQ("\\textsuperscript{d}");
        case L'ᵉ':                 SEQ("\\textsuperscript{e}");
        case L'ᵍ':                 SEQ("\\textsuperscript{g}");
        case L'ᵏ':                 SEQ("\\textsuperscript{k}");
        case L'ᵐ':                 SEQ("\\textsuperscript{m}");
        case L'ᵒ':                 SEQ("\\textsuperscript{o}");
        case L'ᵖ':                 SEQ("\\textsuperscript{p}");
        case L'ᵗ':                 SEQ("\\textsuperscript{t}");
        case L'ᵘ':                 SEQ("\\textsuperscript{u}");
        case L'ᵛ':                 SEQ("\\textsuperscript{v}");
        case L'ᵝ':                 SEQ("\\textsuperscript{$\\beta$}");
        case L'ᵞ':                 SEQ("\\textsuperscript{$\\gamma$}");
        case L'ᵟ':                 SEQ("\\textsuperscript{$\\delta$}");
        case L'ᵠ':                 SEQ("\\textsuperscript{$\\phi$}");
        case L'ᵡ':                 SEQ("\\textsuperscript{$\\chi$}");
        case L'ᵢ':                 SEQ("\\textsubscript{i}");
        case L'ᵣ':                 SEQ("\\textsubscript{r}");
        case L'ᵤ':                 SEQ("\\textsubscript{u}");
        case L'ᵥ':                 SEQ("\\textsubscript{v}");
        case L'ᵦ':                 SEQ("\\textsubscript{$\\beta$}");
        case L'ᵧ':                 SEQ("\\textsubscript{$\\gamma$}");
        case L'ᵨ':                 SEQ("\\textsubscript{$\\rho$}");
        case L'ᵩ':                 SEQ("\\textsubscript{$\\phi$}");
        case L'ᵪ':                 SEQ("\\textsubscript{$\\chi$}");
        case L'ᶜ':                 SEQ("\\textsuperscript{c}");
        case L'ᶠ':                 SEQ("\\textsuperscript{f}");
        case L'ᶢ':                 SEQ("\\textsuperscript{g}");
        case L'ᶥ':                 SEQ("\\textsuperscript{$\\iota$}");
        case L'ᶷ':                 SEQ("\\textsuperscript{$\\upsilon$}");
        case L'ᶻ':                 SEQ("\\textsuperscript{z}");
        case L'ᶿ':                 SEQ("\\textsuperscript{$\\theta$}");


        /* Latin extended additional */
        case L'Ḁ':
        case L'ḁ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ḃ':                 SEQ("{\\.B}");
        case L'ḃ':                 SEQ("{\\.b}");
        case L'Ḅ':                 SEQ("{\\d B}");
        case L'ḅ':                 SEQ("{\\d b}");
        case L'Ḇ':                 SEQ("{\\b B}");
        case L'ḇ':                 SEQ("{\\b b}");
        case L'Ḉ':
        case L'ḉ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ḋ':                 SEQ("{\\.D}");
        case L'ḋ':                 SEQ("{\\.d}");
        case L'Ḍ':                 SEQ("{\\d D}");
        case L'ḍ':                 SEQ("{\\d d}");
        case L'Ḏ':                 SEQ("{\\b D}");
        case L'ḏ':                 SEQ("{\\b d}");
        case L'Ḑ':                 SEQ("{\\c D}");
        case L'ḑ':                 SEQ("{\\c d}");
        case L'Ḓ' ... L'ḝ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ḟ':                 SEQ("{\\.F}");
        case L'ḟ':                 SEQ("{\\.f}");
        case L'Ḡ':                 SEQ("{\\=G}");
        case L'ḡ':                 SEQ("{\\=g}");
        case L'Ḣ':                 SEQ("{\\.H}");
        case L'ḣ':                 SEQ("{\\.h}");
        case L'Ḥ':                 SEQ("{\\d H}");
        case L'ḥ':                 SEQ("{\\d h}");
        case L'Ḧ':                 SEQ("{\\\"H}");
        case L'ḧ':                 SEQ("{\\\"h}");
        case L'Ḩ':                 SEQ("{\\c H}");
        case L'ḩ':                 SEQ("{\\c h}");
        case L'Ḫ' ... L'ḯ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ḱ':                 SEQ("{\\'K}");
        case L'ḱ':                 SEQ("{\\'k}");
        case L'Ḳ':                 SEQ("{\\d K}");
        case L'ḳ':                 SEQ("{\\d k}");
        case L'Ḵ':                 SEQ("{\\b K}");
        case L'ḵ':                 SEQ("{\\b k}");
        case L'Ḷ':                 SEQ("{\\d L}");
        case L'ḷ':                 SEQ("{\\d l}");
        case L'Ḹ':
        case L'ḹ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ḻ':                 SEQ("{\\b L}");
        case L'ḻ':                 SEQ("{\\b l}");
        case L'Ḽ':
        case L'ḽ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ḿ':                 SEQ("{\\'M}");
        case L'ḿ':                 SEQ("{\\'m}");
        case L'Ṁ':                 SEQ("{\\.M}");
        case L'ṁ':                 SEQ("{\\.m}");
        case L'Ṃ':                 SEQ("{\\d M}");
        case L'ṃ':                 SEQ("{\\d m}");
        case L'Ṅ':                 SEQ("{\\.N}");
        case L'ṅ':                 SEQ("{\\.n}");
        case L'Ṇ':                 SEQ("{\\d N}");
        case L'ṇ':                 SEQ("{\\d n}");
        case L'Ṉ':                 SEQ("{\\b N}");
        case L'ṉ':                 SEQ("{\\b n}");
        case L'Ṋ' ... L'ṓ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ṕ':                 SEQ("{\\'P}");
        case L'ṕ':                 SEQ("{\\'p}");
        case L'Ṗ':                 SEQ("{\\.P}");
        case L'ṗ':                 SEQ("{\\.p}");
        case L'Ṙ':                 SEQ("{\\.R}");
        case L'ṙ':                 SEQ("{\\.r}");
        case L'Ṛ':                 SEQ("{\\d R}");
        case L'ṛ':                 SEQ("{\\d r}");
        case L'Ṝ':
        case L'ṝ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ṟ':                 SEQ("{\\b R}");
        case L'ṟ':                 SEQ("{\\b r}");
        case L'Ṡ':                 SEQ("{\\.S}");
        case L'ṡ':                 SEQ("{\\.s}");
        case L'Ṣ':                 SEQ("{\\d S}");
        case L'ṣ':                 SEQ("{\\d s}");
        case L'Ṥ' ... L'ṩ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ṫ':                 SEQ("{\\.T}");
        case L'ṫ':                 SEQ("{\\.t}");
        case L'Ṭ':                 SEQ("{\\d T}");
        case L'ṭ':                 SEQ("{\\d t}");
        case L'Ṯ':                 SEQ("{\\b T}");
        case L'ṯ':                 SEQ("{\\b t}");
        case L'Ṱ' ... L'ṻ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ṽ':                 SEQ("{\\~V}");
        case L'ṽ':                 SEQ("{\\~v}");
        case L'Ṿ':                 SEQ("{\\d V}");
        case L'ṿ':                 SEQ("{\\d v}");
        case L'Ẁ':                 SEQ("{\\`W}");
        case L'ẁ':                 SEQ("{\\`w}");
        case L'Ẃ':                 SEQ("{\\'W}");
        case L'ẃ':                 SEQ("{\\'w}");
        case L'Ẅ':                 SEQ("{\\\"W}");
        case L'ẅ':                 SEQ("{\\\"w}");
        case L'Ẇ':                 SEQ("{\\.W}");
        case L'ẇ':                 SEQ("{\\.w}");
        case L'Ẉ':                 SEQ("{\\d W}");
        case L'ẉ':                 SEQ("{\\d w}");
        case L'Ẋ':                 SEQ("{\\.X}");
        case L'ẋ':                 SEQ("{\\.x}");
        case L'Ẍ':                 SEQ("{\\\"X}");
        case L'ẍ':                 SEQ("{\\\"x}");
        case L'Ẏ':                 SEQ("{\\.Y}");
        case L'ẏ':                 SEQ("{\\.y}");
        case L'Ẑ':                 SEQ("{\\^Z}");
        case L'ẑ':                 SEQ("{\\^z}");
        case L'Ẓ':                 SEQ("{\\d Z}");
        case L'ẓ':                 SEQ("{\\d z}");
        case L'Ẕ':                 SEQ("{\\b Z}");
        case L'ẕ':                 SEQ("{\\b z}");
        case L'ẖ':                 SEQ("{\\b h}");
        case L'ẗ':                 SEQ("{\\\"t}");
        case L'ẘ':                 SEQ("{\\r w}");
        case L'ẙ':                 SEQ("{\\r y}");
        case L'ẚ' ... L'ẞ':        return UTF8TOTEX_UNSUPPORTED;
        case L'ẟ':                 SEQ("$\\delta$");
        case L'Ạ':                 SEQ("{\\d A}");
        case L'ạ':                 SEQ("{\\d a}");
        case L'Ả' ... L'ặ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ẹ':                 SEQ("{\\d E}");
        case L'ẹ':                 SEQ("{\\d e}");
        case L'Ẻ':
        case L'ẻ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'Ẽ':                 SEQ("{\\~E}");
        case L'ẽ':                 SEQ("{\\~e}");
        case L'Ế' ... L'ỉ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ị':                 SEQ("{\\d I}");
        case L'ị':                 SEQ("{\\d i}");
        case L'Ọ':                 SEQ("{\\d O}");
        case L'ọ':                 SEQ("{\\d o}");
        case L'Ỏ' ... L'ợ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ụ':                 SEQ("{\\d U}");
        case L'ụ':                 SEQ("{\\d u}");
        case L'Ủ' ... L'ự':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ỳ':                 SEQ("{\\`Y}");
        case L'ỳ':                 SEQ("{\\`y}");
        case L'Ỵ':                 SEQ("{\\d Y}");
        case L'ỵ':                 SEQ("{\\d y}");
        case L'Ỷ' ... L'ỷ':        return UTF8TOTEX_UNSUPPORTED;
        case L'Ỹ':                 SEQ("{\\~Y}");
        case L'ỹ':                 SEQ("{\\~y}");
        case L'Ỻ':                 SEQ("IL");
        case L'ỻ' ... L'ỿ':        return UTF8TOTEX_UNSUPPORTED;

        /* Letterlike symbols */
        case L'℃':                 SEQ_TC("{\\textdegree}C");
        case L'℉':                 SEQ_TC("{\\textdegree}F");
        case L'™':                 SEQ("{\\texttrademark}");

        /* General punctuation */
        case L'‐':                 SEQ("{-}");
        case L'–':                 SEQ("{--}");
        case L'—':                 SEQ("{---}");
        case L'‘':                 SEQ("{`}");
        case L'’':                 SEQ("{'}");
        case L'“':                 SEQ("{``}");
        case L'”':                 SEQ("{''}");
        case L'†':                 SEQ("{\\dag}");
        case L'‡':                 SEQ("{\\ddag}");
        case L'•':                 SEQ("{\\textbullet}");
        case L'․':                 SEQ(".");
        case L'‥':                 SEQ("..");
        case L'…':                 SEQ("{\\dots}");
        case L'‧':                 SEQ("{\\textperiodcentered}");
        case L'‰':                 SEQ("{\\textperthousand}");
        case L'‱':                 SEQ("{\\textpertenthousand}");
        case L'‹':                 SEQ_T1("{\\guilsinglleft}");
        case L'›':                 SEQ_T1("{\\guilsinglright}");
        case L'⁀':                 SEQ("{\\t  }");
        case L'⁇':                 SEQ("??");
        case L'⁈':                 SEQ("?!");
        case L'⁉':                 SEQ("!?");

        /* XXX */
        case L'⁰':                 SEQ("\\textsuperscript{0}");
        case L'ⁱ':                 SEQ("\\textsuperscript{i}");
        case 0x2072 ... 0x2073:    return UTF8TOTEX_INVALID;
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
        case 0x208f:               return UTF8TOTEX_INVALID;
        case L'ₐ':                 SEQ("\\textsubscript{a}");
        case L'ₑ':                 SEQ("\\textsubscript{e}");
        case L'ₒ':                 SEQ("\\textsubscript{o}");
        case L'ₓ':                 SEQ("\\textsubscript{x}");
        case L'ₔ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'ₕ':                 SEQ("\\textsubscript{h}");
        case L'ₖ':                 SEQ("\\textsubscript{k}");
        case L'ₗ':                 SEQ("\\textsubscript{l}");
        case L'ₘ':                 SEQ("\\textsubscript{m}");
        case L'ₙ':                 SEQ("\\textsubscript{n}");
        case L'ₚ':                 SEQ("\\textsubscript{p}");
        case L'ₛ':                 SEQ("\\textsubscript{s}");
        case L'ₜ':                 SEQ("\\textsubscript{t}");
        case 0x209d ... 0x209f:    return UTF8TOTEX_INVALID;

        case 0x20bf ... 0x20cf:    return UTF8TOTEX_INVALID;

        /* Number forms */
        case L'Ⅰ':                 SEQ("I");
        case L'Ⅱ':                 SEQ("II");
        case L'Ⅲ':                 SEQ("III");
        case L'Ⅳ':                 SEQ("IV");
        case L'Ⅴ':                 SEQ("V");
        case L'Ⅵ':                 SEQ("VI");
        case L'Ⅶ':                 SEQ("VII");
        case L'Ⅷ':                 SEQ("VIII");
        case L'Ⅸ':                 SEQ("IX");
        case L'Ⅹ':                 SEQ("X");
        case L'Ⅺ':                 SEQ("XI");
        case L'Ⅻ':                 SEQ("XII");
        case L'Ⅼ':                 SEQ("L");
        case L'Ⅽ':                 SEQ("C");
        case L'Ⅾ':                 SEQ("D");
        case L'Ⅿ':                 SEQ("M");
        case L'ⅰ':                 SEQ("i");
        case L'ⅱ':                 SEQ("ii");
        case L'ⅲ':                 SEQ("iii");
        case L'ⅳ':                 SEQ("iv");
        case L'ⅴ':                 SEQ("v");
        case L'ⅵ':                 SEQ("vi");
        case L'ⅶ':                 SEQ("vii");
        case L'ⅷ':                 SEQ("viii");
        case L'ⅸ':                 SEQ("ix");
        case L'ⅹ':                 SEQ("x");
        case L'ⅺ':                 SEQ("xi");
        case L'ⅻ':                 SEQ("xii");
        case L'ⅼ':                 SEQ("l");
        case L'ⅽ':                 SEQ("c");
        case L'ⅾ':                 SEQ("d");
        case L'ⅿ':                 SEQ("m");

        case 0x218c ... 0x218f:    return UTF8TOTEX_INVALID;

        /* Mathematical operatos */
        case L'∆':                 SEQ("$\\bigtriangleup$");
        case L'∇':                 SEQ("$\\bigtriangledown$");
        case L'∐':                 SEQ("$\\amalg$");
        case L'∑':                 SEQ("$\\Sigma$");
        case L'−':                 SEQ("$-$");
        case L'∓':                 SEQ("$\\mp$");
        case L'∕':                 SEQ("$/$");
        case L'∗':                 SEQ("$*$");
        case L'∙':                 SEQ("$\\bullet$");
        case L'∧':                 SEQ("$\\wedge$");
        case L'∨':                 SEQ("$\\vee$");
        case L'∩':                 SEQ("$\\cap$");
        case L'∪':                 SEQ("$\\cup$");
        case L'⊓':                 SEQ("$\\sqcap$");
        case L'⊔':                 SEQ("$\\sqcup$");
        case L'⊕':                 SEQ("$\\oplus$");
        case L'⊖':                 SEQ("$\\ominus$");
        case L'⊗':                 SEQ("$\\otimes$");
        case L'⊘':                 SEQ("$\\oslash$");
        case L'⊙':                 SEQ("$\\odot$");

        /* CJK compatibility */
        case L'㍱':                SEQ("hPa");
        case L'㍲':                SEQ("da");
        case L'㍳':                SEQ("AU");
        case L'㍴':                SEQ("bar");
        case L'㍵':                SEQ("oV");
        case L'㍶':                SEQ("pc");
        case L'㍷':                SEQ("dm");
        case L'㍸':                SEQ("dm\\textsuperscript{2}");
        case L'㍹':                SEQ("dm\\textsuperscript{3}");
        case L'㍺':                SEQ("IU");
        case L'㎀':                SEQ("pA");
        case L'㎁':                SEQ("nA");
        case L'㎂':                SEQ("$\\mu$A");
        case L'㎃':                SEQ("mA");
        case L'㎄':                SEQ("kA");
        case L'㎅':                SEQ("KB");
        case L'㎆':                SEQ("MB");
        case L'㎇':                SEQ("GB");
        case L'㎈':                SEQ("cal");
        case L'㎉':                SEQ("kcal");
        case L'㎊':                SEQ("pF");
        case L'㎋':                SEQ("nF");
        case L'㎌':                SEQ("$\\mu$F");
        case L'㎍':                SEQ("$\\mu$g");
        case L'㎎':                SEQ("mg");
        case L'㎏':                SEQ("kg");
        case L'㎐':                SEQ("Hz");
        case L'㎑':                SEQ("kHz");
        case L'㎒':                SEQ("MHz");
        case L'㎓':                SEQ("GHz");
        case L'㎔':                SEQ("THz");
        case L'㎙':                SEQ("fm");
        case L'㎚':                SEQ("nm");
        case L'㎛':                SEQ("$\\mu$m");
        case L'㎜':                SEQ("mm");
        case L'㎝':                SEQ("cm");
        case L'㎞':                SEQ("km");
        case L'㎟':                SEQ("mm\\textsuperscript{2}");
        case L'㎠':                SEQ("cm\\textsuperscript{2}");
        case L'㎡':                SEQ("m\\textsuperscript{2}");
        case L'㎢':                SEQ("km\\textsuperscript{2}");
        case L'㎣':                SEQ("mm\\textsuperscript{3}");
        case L'㎤':                SEQ("cm\\textsuperscript{3}");
        case L'㎥':                SEQ("m\\textsuperscript{3}");
        case L'㎦':                SEQ("km\\textsuperscript{3}");
        case L'㎩':                SEQ("Pa");
        case L'㎪':                SEQ("kPa");
        case L'㎫':                SEQ("MPa");
        case L'㎬':                SEQ("GPa");
        case L'㎭':                SEQ("rad");
        case L'㎮':                SEQ("rad/s");
        case L'㎯':                SEQ("rad/s\\textsuperscript{2}");
        case L'㎰':                SEQ("ps");
        case L'㎱':                SEQ("ns");
        case L'㎲':                SEQ("$\\mu$s");
        case L'㎳':                SEQ("ms");
        case L'㎴':                SEQ("pV");
        case L'㎵':                SEQ("nV");
        case L'㎶':                SEQ("$\\mu$V");
        case L'㎷':                SEQ("mV");
        case L'㎸':                SEQ("kV");
        case L'㎹':                SEQ("MV");
        case L'㎺':                SEQ("pW");
        case L'㎻':                SEQ("nW");
        case L'㎼':                SEQ("$\\mu$W");
        case L'㎽':                SEQ("mW");
        case L'㎾':                SEQ("kW");
        case L'㎿':                SEQ("MW");
        case L'㏀':                SEQ("k$\\Omega$");
        case L'㏁':                SEQ("M$\\Omega$");
        case L'㏂':                SEQ("a.m.");
        case L'㏃':                SEQ("Bq");
        case L'㏄':                SEQ("cc");
        case L'㏅':                SEQ("cd");
        case L'㏆':                SEQ("C/kg");
        case L'㏇':                SEQ("Co.");
        case L'㏈':                SEQ("dB");
        case L'㏉':                SEQ("Gy");
        case L'㏊':                SEQ("ha");
        case L'㏌':                SEQ("in");
        case L'㏍':                SEQ("K.K.");
        case L'㏎':                SEQ("KM");
        case L'㏏':                SEQ("kt");
        case L'㏐':                SEQ("lm");
        case L'㏑':                SEQ("ln");
        case L'㏒':                SEQ("log");
        case L'㏓':                SEQ("lx");
        case L'㏔':                SEQ("mb");
        case L'㏕':                SEQ("mil");
        case L'㏖':                SEQ("mol");
        case L'㏗':                SEQ("pH");
        case L'㏘':                SEQ("p.m.");
        case L'㏙':                SEQ("PPM");
        case L'㏚':                SEQ("PR");
        case L'㏛':                SEQ("sr");
        case L'㏜':                SEQ("Sv");
        case L'㏝':                SEQ("Wb");

        case L'ﬀ':                 SEQ("ff");
        case L'ﬁ':                 SEQ("fi");
        case L'ﬂ':                 SEQ("fl");
        case L'ﬃ':                 SEQ("ffi");
        case L'ﬄ':                 SEQ("ffl");
        case L'ﬅ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'ﬆ':                 SEQ("st");
        case 0xfb07 ... 0xfb12:    return UTF8TOTEX_INVALID;

        /* UTF-8 characters are a maximum of 21 bits */
        case 1 << 21 ... UINT32_MAX:
            return UTF8TOTEX_INVALID;

        default:
            return UTF8TOTEX_UNSUPPORTED;
            
#undef SEQ
#undef SEQ_T1
#undef SEQ_TC
#undef ACC

    }
}
