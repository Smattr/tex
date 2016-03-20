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
 *
 * Some general guidance if you're modifying this file:
 *
 *   * "{\\'a}" > "\\'{a}" because it will sort correctly in bibliographies and
 *     whatnot.
 *   * "{\\aa}" > "{\\r a}" because it is fewer characters. In a large document
 *     these optimisations can have an impact.
 */

utf8totex_char_t utf8totex_from_char(const char **s, uint32_t c,
        utf8totex_environment_t env) {
    assert(s != NULL);

    switch (c) {

#define SEQ(x, str) \
    case x: do { \
                *(s) = (str); \
                return UTF8TOTEX_SEQUENCE; \
            } while (0)

#define SEQ_T1(x, str) \
    case x: do { \
                if (env.font_encoding == UTF8TOTEX_FE_T1 || \
                    env.font_encoding == UTF8TOTEX_FE_T2A || \
                    env.font_encoding == UTF8TOTEX_FE_T2B || \
                    env.font_encoding == UTF8TOTEX_FE_T2C || \
                    env.font_encoding == UTF8TOTEX_FE_X2) { \
                    *(s) = (str); \
                    return UTF8TOTEX_SEQUENCE; \
                } \
                return UTF8TOTEX_UNSUPPORTED; \
            } while (0)

#define SEQ_TC(x, str) \
    case x: do { \
                if (env.textcomp) { \
                    *(s) = (str); \
                    return UTF8TOTEX_SEQUENCE; \
                } \
                return UTF8TOTEX_UNSUPPORTED; \
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
        SEQ(L'#', "{\\#}");
        SEQ(L'$', "{\\$}");
        SEQ(L'%', "{\\%}");
        SEQ(L'&', "{\\&}");
        case L'\'' ... L';':       return UTF8TOTEX_ASCII;
        SEQ(L'<', "{\\textless}");
        case L'=':                 return UTF8TOTEX_ASCII;
        SEQ(L'>', "{\\textgreater}");
        case L'?' ... L'[':        return UTF8TOTEX_ASCII;
        SEQ(L'\\', "{\\letterbackslash}");
        case L']':                 return UTF8TOTEX_ASCII;
        SEQ(L'^', "{\\letterhat}");
        SEQ(L'_', "{\\letterunderscore}");
        SEQ(L'`', "{\\`}");
        case L'a' ... L'z':        return UTF8TOTEX_ASCII;
        SEQ(L'{', "{\\{}");
        case L'|':                 return UTF8TOTEX_ASCII;
        SEQ(L'}', "{\\}}");
        SEQ(L'~', "{\\lettertilde}");
        case 0x007f:               return UTF8TOTEX_INVALID;

        /* Latin-1 supplement */
        case 0x0080 ... 0x009f:    return UTF8TOTEX_INVALID;
        SEQ(0x00a0, "~"); /* non-breaking space */
        SEQ(L'¡', "{\\textexclamdown}");
        SEQ(L'¢', "{\\textcent}");
        SEQ(L'£', "{\\pounds}");
        SEQ_TC(L'¤', "{\\textcurrency}");
        SEQ_TC(L'¥', "{\\textyen}");
        SEQ_TC(L'¦', "{\\textbrokenbar}");
        SEQ(L'§', "{\\textsection}");
        SEQ_TC(L'¨', "{\\textasciidieresis}");
        SEQ(L'©', "{\\copyright}");
        SEQ(L'ª', "{\\textordfeminine}");
        SEQ_T1(L'«', "{\\guillemotleft}");
        SEQ_TC(L'¬', "{\\textlnot}");
        SEQ(0x00ad, "\\-"); /* soft hyphen */
        SEQ(L'®', "{\\textregistered}");
        SEQ(L'¯', "{\\= }");
        SEQ_TC(L'°', "{\\textdegree}");
        SEQ(L'±', "$\\pm$");
        SEQ(L'²', "\\textsuperscript{2}");
        SEQ(L'³', "\\textsuperscript{3}");
        SEQ(L'´', "{\\' }");
        SEQ(L'µ', "$\\mu$");
        SEQ(L'¶', "{\\P}");
        SEQ(L'·', "{\\textperiodcentered}");
        SEQ(L'¸', "{\\c }");
        SEQ(L'¹', "\\textsuperscript{1}");
        SEQ(L'º', "{\\textordmasculine}");
        SEQ_T1(L'»', "{\\guillemotright}");
        SEQ_TC(L'¼', "{\\textonequarter}");
        SEQ_TC(L'½', "{\\textonehalf}");
        SEQ_TC(L'¾', "{\\textthreequarters}");
        SEQ(L'¿', "{\\textquestiondown}");
        SEQ(L'À', "{\\`A}");
        SEQ(L'Á', "{\\'A}");
        SEQ(L'Â', "{\\^A}");
        SEQ(L'Ã', "{\\~A}");
        SEQ(L'Ä', "{\\\"A}");
        SEQ(L'Å', "{\\AA}");
        SEQ(L'Æ', "{\\AE}");
        SEQ(L'Ç', "{\\c C}");
        SEQ(L'È', "{\\`E}");
        SEQ(L'É', "{\\'E}");
        SEQ(L'Ê', "{\\^E}");
        SEQ(L'Ë', "{\\\"E}");
        SEQ(L'Ì', "{\\`I}");
        SEQ(L'Í', "{\\'I}");
        SEQ(L'Î', "{\\^I}");
        SEQ(L'Ï', "{\\\"I}");
        SEQ_T1(L'Ð', "{\\DJ}");
        SEQ(L'Ñ', "{\\~N}");
        SEQ(L'Ò', "{\\`O}");
        SEQ(L'Ó', "{\\'O}");
        SEQ(L'Ô', "{\\^O}");
        SEQ(L'Õ', "{\\~O}");
        SEQ(L'Ö', "{\\\"O}");
        SEQ(L'×', "$\\times$");
        SEQ(L'Ø', "{\\O}");
        SEQ(L'Ù', "{\\`U}");
        SEQ(L'Ú', "{\\'U}");
        SEQ(L'Û', "{\\^U}");
        SEQ(L'Ü', "{\\\"U}");
        SEQ(L'Ý', "{\\'Y}");
        SEQ_T1(L'Þ', "{\\TH}");
        SEQ(L'ß', "{\\ss}");
        SEQ(L'à', "{\\`a}");
        SEQ(L'á', "{\\'a}");
        SEQ(L'â', "{\\^a}");
        SEQ(L'ã', "{\\~a}");
        SEQ(L'ä', "{\\\"a}");
        SEQ(L'å', "{\\aa}");
        SEQ(L'æ', "{\\ae}");
        SEQ(L'ç', "{\\c c}");
        SEQ(L'è', "{\\`e}");
        SEQ(L'é', "{\\'e}");
        SEQ(L'ê', "{\\^e}");
        SEQ(L'ë', "{\\\"e}");
        SEQ(L'ì', "{\\`\\i}");
        SEQ(L'í', "{\\'\\i}");
        SEQ(L'î', "{\\^\\i}");
        SEQ(L'ï', "{\\\"\\i}");
        case L'ð':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'ñ', "{\\~n}");
        SEQ(L'ò', "{\\`o}");
        SEQ(L'ó', "{\\'o}");
        SEQ(L'ô', "{\\^o}");
        SEQ(L'õ', "{\\~o}");
        SEQ(L'ö', "{\\\"o}");
        SEQ(L'÷', "$\\div$");
        SEQ(L'ø', "{\\o}");
        SEQ(L'ù', "{\\`u}");
        SEQ(L'ú', "{\\'u}");
        SEQ(L'û', "{\\^u}");
        SEQ(L'ü', "{\\\"u}");
        SEQ(L'ý', "{\\'y}");
        SEQ_T1(L'þ', "{\\th}");
        SEQ(L'ÿ', "{\\\"y}");

        /* Latin Extended-A */
        SEQ(L'Ā', "{\\=A}");
        SEQ(L'ā', "{\\=a}");
        SEQ(L'Ă', "{\\u A}");
        SEQ(L'ă', "{\\u a}");
        SEQ_T1(L'Ą', "{\\k A}");
        SEQ_T1(L'ą', "{\\k a}");
        SEQ(L'Ć', "{\\'C}");
        SEQ(L'ć', "{\\'c}");
        SEQ(L'Ĉ', "{\\^C}");
        SEQ(L'ĉ', "{\\^c}");
        SEQ(L'Ċ', "{\\.C}");
        SEQ(L'ċ', "{\\.c}");
        SEQ(L'Č', "{\\v C}");
        SEQ(L'č', "{\\v c}");
        SEQ(L'Ď', "{\\v D}");
        SEQ(L'ď', "{\\v d}");
        SEQ_T1(L'Đ', "{\\DJ}");
        SEQ_T1(L'đ', "{\\dj}");
        SEQ(L'Ē', "{\\=E}");
        SEQ(L'ē', "{\\=e}");
        SEQ(L'Ĕ', "{\\u E}");
        SEQ(L'ĕ', "{\\u e}");
        SEQ(L'Ė', "{\\.E}");
        SEQ(L'ė', "{\\.e}");
        SEQ_T1(L'Ę', "{\\k E}");
        SEQ_T1(L'ę', "{\\k e}");
        SEQ(L'Ě', "{\\v E}");
        SEQ(L'ě', "{\\v e}");
        SEQ(L'Ĝ', "{\\^G}");
        SEQ(L'ĝ', "{\\^g}");
        SEQ(L'Ğ', "{\\u G}");
        SEQ(L'ğ', "{\\u g}");
        SEQ(L'Ġ', "{\\.G}");
        SEQ(L'ġ', "{\\.g}");
        SEQ(L'Ģ', "{\\c G}");
        SEQ(L'ģ', "{\\c g}");
        SEQ(L'Ĥ', "{\\^H}");
        SEQ(L'ĥ', "{\\^h}");
        case L'Ħ':                 return UTF8TOTEX_UNSUPPORTED; /* XXX: we could do this with T3 */
        case L'ħ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ĩ', "{\\~I}");
        SEQ(L'ĩ', "{\\~\\i}");
        SEQ(L'Ī', "{\\=I}");
        SEQ(L'ī', "{\\=\\i}");
        SEQ(L'Ĭ', "{\\u I}");
        SEQ(L'ĭ', "{\\u\\i}");
        SEQ_T1(L'Į', "{\\k I}");
        SEQ_T1(L'į', "{\\k i}");
        SEQ(L'İ', "{\\.I}");
        SEQ(L'ı', "{\\i}");
        SEQ(L'Ĳ', "IJ"); /* no native ligatures it seems */
        SEQ(L'ĳ', "ij");
        SEQ(L'Ĵ', "{\\^J}");
        SEQ(L'ĵ', "{\\^\\j}");
        SEQ(L'Ķ', "{\\c K}");
        SEQ(L'ķ', "{\\c k}");
        case L'ĸ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ĺ', "{\\'L}");
        SEQ(L'ĺ', "{\\'l}");
        SEQ(L'Ļ', "{\\c L}");
        SEQ(L'ļ', "{\\c l}");
        SEQ(L'Ľ', "{\\v L}");
        SEQ(L'ľ', "{\\v l}");
        case L'Ŀ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'ŀ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ł', "{\\L}");
        SEQ(L'ł', "{\\l}");
        SEQ(L'Ń', "{\\'N}");
        SEQ(L'ń', "{\\'n}");
        SEQ(L'Ņ', "{\\c N}");
        SEQ(L'ņ', "{\\c n}");
        SEQ(L'Ň', "{\\v N}");
        SEQ(L'ň', "{\\v n}");
        case L'ŉ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ_T1(L'Ŋ', "{\\NG}");
        SEQ_T1(L'ŋ', "{\\ng}");
        SEQ(L'Ō', "{\\=O}");
        SEQ(L'ō', "{\\=o}");
        SEQ(L'Ŏ', "{\\u O}");
        SEQ(L'ŏ', "{\\u o}");
        SEQ(L'Ő', "{\\H O}");
        SEQ(L'ő', "{\\H o}");
        SEQ(L'Œ', "{\\OE}");
        SEQ(L'œ', "{\\oe}");
        SEQ(L'Ŕ', "{\\'R}");
        SEQ(L'ŕ', "{\\'r}");
        SEQ(L'Ŗ', "{\\c R}");
        SEQ(L'ŗ', "{\\c r}");
        SEQ(L'Ř', "{\\v R}");
        SEQ(L'ř', "{\\v r}");
        SEQ(L'Ś', "{\\'S}");
        SEQ(L'ś', "{\\'s}");
        SEQ(L'Ŝ', "{\\^S}");
        SEQ(L'ŝ', "{\\^s}");
        SEQ(L'Ş', "{\\c S}");
        SEQ(L'ş', "{\\c s}");
        SEQ(L'Š', "{\\v S}");
        SEQ(L'š', "{\\v s}");
        SEQ(L'Ţ', "{\\c T}");
        SEQ(L'ţ', "{\\c t}");
        SEQ(L'Ť', "{\\v T}");
        SEQ(L'ť', "{\\v t}");
        case L'Ŧ':                 return UTF8TOTEX_UNSUPPORTED;
        case L'ŧ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ũ', "{\\~U}");
        SEQ(L'ũ', "{\\~u}");
        SEQ(L'Ū', "{\\=U}");
        SEQ(L'ū', "{\\=u}");
        SEQ(L'Ŭ', "{\\u U}");
        SEQ(L'ŭ', "{\\u u}");
        SEQ(L'Ů', "{\\r U}");
        SEQ(L'ů', "{\\r u}");
        SEQ(L'Ű', "{\\H U}");
        SEQ(L'ű', "{\\H u}");
        SEQ_T1(L'Ų', "{\\k U}");
        SEQ_T1(L'ų', "{\\k u}");
        SEQ(L'Ŵ', "{\\^W}");
        SEQ(L'ŵ', "{\\^w}");
        SEQ(L'Ŷ', "{\\^Y}");
        SEQ(L'ŷ', "{\\^y}");
        SEQ(L'Ÿ', "{\\\"Y}");
        SEQ(L'Ź', "{\\'Z}");
        SEQ(L'ź', "{\\'z}");
        SEQ(L'Ż', "{\\.Z}");
        SEQ(L'ż', "{\\.z}");
        SEQ(L'Ž', "{\\v Z}");
        SEQ(L'ž', "{\\v z}");
        case L'ſ':                 return UTF8TOTEX_UNSUPPORTED;

        /* Latin Extended-B */
        /* XXX */
        SEQ(L'Ɩ', "$\\Iota$");
        SEQ(L'Ɵ', "$\\theta$");
        SEQ(L'ǃ', "!");
        SEQ(L'Ǆ', "D{\\v Z}");
        SEQ(L'ǅ', "D{\\v z}");
        SEQ(L'ǆ', "d{\\v z}");
        SEQ(L'Ǉ', "LJ");
        SEQ(L'ǈ', "Lj");
        SEQ(L'ǉ', "lj");
        SEQ(L'Ǌ', "NJ");
        SEQ(L'ǋ', "Nj");
        SEQ(L'ǌ', "nj");
        SEQ(L'Ǎ', "{\\v A}");
        SEQ(L'ǎ', "{\\v a}");
        SEQ(L'Ǐ', "{\\v I}");
        SEQ(L'ǐ', "{\\v\\i}");
        SEQ(L'Ǒ', "{\\v O}");
        SEQ(L'ǒ', "{\\v o}");
        SEQ(L'Ǔ', "{\\v U}");
        SEQ(L'ǔ', "{\\v u}");
        case L'Ǖ' ... L'ǡ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ǣ', "{\\=\\AE}");
        SEQ(L'ǣ', "{\\=\\ae}");
        case L'Ǥ':
        case L'ǥ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ǧ', "{\\v G}");
        SEQ(L'ǧ', "{\\v g}");
        SEQ(L'Ǩ', "{\\v K}");
        SEQ(L'ǩ', "{\\v k}");
        SEQ_T1(L'Ǫ', "{\\k O}");
        SEQ_T1(L'ǫ', "{\\k o}");
        SEQ_T1(L'Ǭ', "{\\k{\\=O}}");
        SEQ_T1(L'ǭ', "{\\k{\\=o}}");
        case L'Ǯ':
        case L'ǯ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'ǰ', "{\\v\\j}");
        SEQ(L'Ǳ', "DZ");
        SEQ(L'ǲ', "Dz");
        SEQ(L'ǳ', "dz");
        SEQ(L'Ǵ', "{\\'G}");
        SEQ(L'ǵ', "{\\'g}");
        case L'Ƕ':
        case L'Ƿ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ǹ', "{\\`N}");
        SEQ(L'ǹ', "{\\`n}");
        case L'Ǻ':
        case L'ǻ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ǽ', "{\\'\\AE}");
        SEQ(L'ǽ', "{\\'\\ae}");
        SEQ(L'Ǿ', "{\\'\\O}");
        SEQ(L'ǿ', "{\\'\\o}");
        case L'Ȁ' ... L'ȝ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ȟ', "{\\v H}");
        SEQ(L'ȟ', "{\\v h}");
        case L'Ƞ' ... L'ȥ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ȧ', "{\\.A}");
        SEQ(L'ȧ', "{\\.a}");
        SEQ(L'Ȩ', "{\\c E}");
        SEQ(L'ȩ', "{\\c e}");
        case L'Ȫ' ... L'ȭ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ȯ', "{\\.O}");
        SEQ(L'ȯ', "{\\.o}");
        case L'Ȱ':
        case L'ȱ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ȳ', "{\\=Y}");
        SEQ(L'ȳ', "{\\=y}");
        case L'ȴ' ... L'ɏ':        return UTF8TOTEX_UNSUPPORTED;
        
        case L'ɐ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'ɑ', "{\\small$\\alpha$}");
        case L'ɒ' ... L'ɠ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'ɡ', "{\\small g}");
        SEQ(L'ɢ', "{\\small G}");
        SEQ(L'ɣ', "{\\small$\\gamma$}");
        SEQ(L'ɩ', "{\\small$\\iota$}");
        SEQ(L'ɪ', "{\\small I}");
        SEQ(L'ɴ', "{\\small N}");
        SEQ(L'ɶ', "{\\small\\OE}");
        SEQ(L'ɸ', "{\\small$\\phi$}");
        SEQ(L'ʀ', "{\\small R}");
        SEQ(L'ʊ', "{\\small$\\upsilon}");
        SEQ(L'ʏ', "{\\small Y}");
        SEQ(L'ʙ', "{\\small B}");
        SEQ(L'ʜ', "{\\small H}");
        SEQ(L'ʟ', "{\\small L}");
        SEQ(L'ʣ', "{\\small dz}");
        SEQ(L'ʦ', "{\\small ts}");
        SEQ(L'ʪ', "{\\small ls}");
        SEQ(L'ʫ', "{\\small lz}");

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
        SEQ(L';', "$;$");
        SEQ(L'Ϳ', "$J$");
        case 0x0380 ... 0x0383:    return UTF8TOTEX_INVALID;
        case L'΄' ... L'Ά':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'·', "$\\textperiodcentered$");
        case L'Έ' ... L'Ί':        return UTF8TOTEX_UNSUPPORTED;
        case 0x038b:               return UTF8TOTEX_INVALID;
        case L'Ό':                 return UTF8TOTEX_UNSUPPORTED;
        case 0x038d:               return UTF8TOTEX_INVALID;
        case L'Ύ' ... L'ΐ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Α', "$A$");
        SEQ(L'Β', "$B$");
        SEQ(L'Γ', "$\\Gamma$");
        SEQ(L'Δ', "$\\Delta$");
        SEQ(L'Ε', "$E$");
        SEQ(L'Ζ', "$Z$");
        SEQ(L'Η', "$H$");
        SEQ(L'Θ', "$\\Theta$");
        SEQ(L'Ι', "$I$");
        SEQ(L'Κ', "$K$");
        SEQ(L'Λ', "$\\Lambda$");
        SEQ(L'Μ', "$M$");
        SEQ(L'Ν', "$N$");
        SEQ(L'Ξ', "$\\Xi$");
        SEQ(L'Ο', "$O$");
        SEQ(L'Π', "$\\Pi$");
        SEQ(L'Ρ', "$P$");
        case 0x03a2:               return UTF8TOTEX_INVALID;
        SEQ(L'Σ', "$\\Sigma$");
        SEQ(L'Τ', "$T$");
        SEQ(L'Υ', "$Y$");
        SEQ(L'Φ', "$\\Phi$");
        SEQ(L'Χ', "$X$");
        SEQ(L'Ψ', "$\\Psi$");
        SEQ(L'Ω', "$\\Omega$");
        /* XXX */
        SEQ(L'α', "$\\alpha$");
        SEQ(L'β', "$\\beta$");
        SEQ(L'γ', "$\\gamma$");
        SEQ(L'δ', "$\\delta$");
        SEQ(L'ε', "$\\varepsilon$");
        SEQ(L'ζ', "$\\zeta$");
        SEQ(L'η', "$\\eta$");
        SEQ(L'θ', "$\\theta$");
        SEQ(L'ι', "$\\iota$");
        SEQ(L'κ', "$\\kappa$");
        SEQ(L'λ', "$\\lambda$");
        SEQ(L'μ', "$\\mu$");
        SEQ(L'ν', "$\\nu$");
        SEQ(L'ξ', "$\\xi$");
        SEQ(L'ο', "$o$");
        SEQ(L'π', "$\\pi$");
        SEQ(L'ρ', "$\\rho$");
        SEQ(L'ς', "$\\varsigma$");
        SEQ(L'σ', "$\\sigma$");
        SEQ(L'τ', "$\\tau$");
        SEQ(L'υ', "$\\upsilon$");
        SEQ(L'φ', "$\\phi$");
        SEQ(L'χ', "$\\chi$");
        SEQ(L'ψ', "$\\psi$");
        SEQ(L'ω', "$\\omega$");

        /* Phonetic extensions */
        SEQ(L'ᴬ', "\\textsuperscript{A}");
        SEQ(L'ᴭ', "\\textsuperscript{\\AE}");
        SEQ(L'ᴮ', "\\textsuperscript{B}");
        SEQ(L'ᴰ', "\\textsuperscript{D}");
        SEQ(L'ᴱ', "\\textsuperscript{E}");
        SEQ(L'ᴳ', "\\textsuperscript{G}");
        SEQ(L'ᴴ', "\\textsuperscript{H}");
        SEQ(L'ᴵ', "\\textsuperscript{I}");
        SEQ(L'ᴶ', "\\textsuperscript{J}");
        SEQ(L'ᴷ', "\\textsuperscript{K}");
        SEQ(L'ᴸ', "\\textsuperscript{L}");
        SEQ(L'ᴹ', "\\textsuperscript{M}");
        SEQ(L'ᴺ', "\\textsuperscript{N}");
        SEQ(L'ᴼ', "\\textsuperscript{O}");
        SEQ(L'ᴾ', "\\textsuperscript{P}");
        SEQ(L'ᴿ', "\\textsuperscript{R}");
        SEQ(L'ᵀ', "\\textsuperscript{T}");
        SEQ(L'ᵁ', "\\textsuperscript{U}");
        SEQ(L'ᵂ', "\\textsuperscript{W}");
        SEQ(L'ᵃ', "\\textsuperscript{a}");
        SEQ(L'ᵇ', "\\textsuperscript{b}");
        SEQ(L'ᵈ', "\\textsuperscript{d}");
        SEQ(L'ᵉ', "\\textsuperscript{e}");
        SEQ(L'ᵍ', "\\textsuperscript{g}");
        SEQ(L'ᵏ', "\\textsuperscript{k}");
        SEQ(L'ᵐ', "\\textsuperscript{m}");
        SEQ(L'ᵒ', "\\textsuperscript{o}");
        SEQ(L'ᵖ', "\\textsuperscript{p}");
        SEQ(L'ᵗ', "\\textsuperscript{t}");
        SEQ(L'ᵘ', "\\textsuperscript{u}");
        SEQ(L'ᵛ', "\\textsuperscript{v}");
        SEQ(L'ᵝ', "\\textsuperscript{$\\beta$}");
        SEQ(L'ᵞ', "\\textsuperscript{$\\gamma$}");
        SEQ(L'ᵟ', "\\textsuperscript{$\\delta$}");
        SEQ(L'ᵠ', "\\textsuperscript{$\\phi$}");
        SEQ(L'ᵡ', "\\textsuperscript{$\\chi$}");
        SEQ(L'ᵢ', "\\textsubscript{i}");
        SEQ(L'ᵣ', "\\textsubscript{r}");
        SEQ(L'ᵤ', "\\textsubscript{u}");
        SEQ(L'ᵥ', "\\textsubscript{v}");
        SEQ(L'ᵦ', "\\textsubscript{$\\beta$}");
        SEQ(L'ᵧ', "\\textsubscript{$\\gamma$}");
        SEQ(L'ᵨ', "\\textsubscript{$\\rho$}");
        SEQ(L'ᵩ', "\\textsubscript{$\\phi$}");
        SEQ(L'ᵪ', "\\textsubscript{$\\chi$}");
        SEQ(L'ᶜ', "\\textsuperscript{c}");
        SEQ(L'ᶠ', "\\textsuperscript{f}");
        SEQ(L'ᶢ', "\\textsuperscript{g}");
        SEQ(L'ᶥ', "\\textsuperscript{$\\iota$}");
        SEQ(L'ᶷ', "\\textsuperscript{$\\upsilon$}");
        SEQ(L'ᶻ', "\\textsuperscript{z}");
        SEQ(L'ᶿ', "\\textsuperscript{$\\theta$}");


        /* Latin extended additional */
        case L'Ḁ':
        case L'ḁ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ḃ', "{\\.B}");
        SEQ(L'ḃ', "{\\.b}");
        SEQ(L'Ḅ', "{\\d B}");
        SEQ(L'ḅ', "{\\d b}");
        SEQ(L'Ḇ', "{\\b B}");
        SEQ(L'ḇ', "{\\b b}");
        case L'Ḉ':
        case L'ḉ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ḋ', "{\\.D}");
        SEQ(L'ḋ', "{\\.d}");
        SEQ(L'Ḍ', "{\\d D}");
        SEQ(L'ḍ', "{\\d d}");
        SEQ(L'Ḏ', "{\\b D}");
        SEQ(L'ḏ', "{\\b d}");
        SEQ(L'Ḑ', "{\\c D}");
        SEQ(L'ḑ', "{\\c d}");
        case L'Ḓ' ... L'ḝ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ḟ', "{\\.F}");
        SEQ(L'ḟ', "{\\.f}");
        SEQ(L'Ḡ', "{\\=G}");
        SEQ(L'ḡ', "{\\=g}");
        SEQ(L'Ḣ', "{\\.H}");
        SEQ(L'ḣ', "{\\.h}");
        SEQ(L'Ḥ', "{\\d H}");
        SEQ(L'ḥ', "{\\d h}");
        SEQ(L'Ḧ', "{\\\"H}");
        SEQ(L'ḧ', "{\\\"h}");
        SEQ(L'Ḩ', "{\\c H}");
        SEQ(L'ḩ', "{\\c h}");
        case L'Ḫ' ... L'ḯ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ḱ', "{\\'K}");
        SEQ(L'ḱ', "{\\'k}");
        SEQ(L'Ḳ', "{\\d K}");
        SEQ(L'ḳ', "{\\d k}");
        SEQ(L'Ḵ', "{\\b K}");
        SEQ(L'ḵ', "{\\b k}");
        SEQ(L'Ḷ', "{\\d L}");
        SEQ(L'ḷ', "{\\d l}");
        case L'Ḹ':
        case L'ḹ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ḻ', "{\\b L}");
        SEQ(L'ḻ', "{\\b l}");
        case L'Ḽ':
        case L'ḽ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ḿ', "{\\'M}");
        SEQ(L'ḿ', "{\\'m}");
        SEQ(L'Ṁ', "{\\.M}");
        SEQ(L'ṁ', "{\\.m}");
        SEQ(L'Ṃ', "{\\d M}");
        SEQ(L'ṃ', "{\\d m}");
        SEQ(L'Ṅ', "{\\.N}");
        SEQ(L'ṅ', "{\\.n}");
        SEQ(L'Ṇ', "{\\d N}");
        SEQ(L'ṇ', "{\\d n}");
        SEQ(L'Ṉ', "{\\b N}");
        SEQ(L'ṉ', "{\\b n}");
        case L'Ṋ' ... L'ṓ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ṕ', "{\\'P}");
        SEQ(L'ṕ', "{\\'p}");
        SEQ(L'Ṗ', "{\\.P}");
        SEQ(L'ṗ', "{\\.p}");
        SEQ(L'Ṙ', "{\\.R}");
        SEQ(L'ṙ', "{\\.r}");
        SEQ(L'Ṛ', "{\\d R}");
        SEQ(L'ṛ', "{\\d r}");
        case L'Ṝ':
        case L'ṝ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ṟ', "{\\b R}");
        SEQ(L'ṟ', "{\\b r}");
        SEQ(L'Ṡ', "{\\.S}");
        SEQ(L'ṡ', "{\\.s}");
        SEQ(L'Ṣ', "{\\d S}");
        SEQ(L'ṣ', "{\\d s}");
        case L'Ṥ' ... L'ṩ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ṫ', "{\\.T}");
        SEQ(L'ṫ', "{\\.t}");
        SEQ(L'Ṭ', "{\\d T}");
        SEQ(L'ṭ', "{\\d t}");
        SEQ(L'Ṯ', "{\\b T}");
        SEQ(L'ṯ', "{\\b t}");
        case L'Ṱ' ... L'ṻ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ṽ', "{\\~V}");
        SEQ(L'ṽ', "{\\~v}");
        SEQ(L'Ṿ', "{\\d V}");
        SEQ(L'ṿ', "{\\d v}");
        SEQ(L'Ẁ', "{\\`W}");
        SEQ(L'ẁ', "{\\`w}");
        SEQ(L'Ẃ', "{\\'W}");
        SEQ(L'ẃ', "{\\'w}");
        SEQ(L'Ẅ', "{\\\"W}");
        SEQ(L'ẅ', "{\\\"w}");
        SEQ(L'Ẇ', "{\\.W}");
        SEQ(L'ẇ', "{\\.w}");
        SEQ(L'Ẉ', "{\\d W}");
        SEQ(L'ẉ', "{\\d w}");
        SEQ(L'Ẋ', "{\\.X}");
        SEQ(L'ẋ', "{\\.x}");
        SEQ(L'Ẍ', "{\\\"X}");
        SEQ(L'ẍ', "{\\\"x}");
        SEQ(L'Ẏ', "{\\.Y}");
        SEQ(L'ẏ', "{\\.y}");
        SEQ(L'Ẑ', "{\\^Z}");
        SEQ(L'ẑ', "{\\^z}");
        SEQ(L'Ẓ', "{\\d Z}");
        SEQ(L'ẓ', "{\\d z}");
        SEQ(L'Ẕ', "{\\b Z}");
        SEQ(L'ẕ', "{\\b z}");
        SEQ(L'ẖ', "{\\b h}");
        SEQ(L'ẗ', "{\\\"t}");
        SEQ(L'ẘ', "{\\r w}");
        SEQ(L'ẙ', "{\\r y}");
        case L'ẚ' ... L'ẞ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'ẟ', "$\\delta$");
        SEQ(L'Ạ', "{\\d A}");
        SEQ(L'ạ', "{\\d a}");
        case L'Ả' ... L'ặ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ẹ', "{\\d E}");
        SEQ(L'ẹ', "{\\d e}");
        case L'Ẻ':
        case L'ẻ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ẽ', "{\\~E}");
        SEQ(L'ẽ', "{\\~e}");
        case L'Ế' ... L'ỉ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ị', "{\\d I}");
        SEQ(L'ị', "{\\d i}");
        SEQ(L'Ọ', "{\\d O}");
        SEQ(L'ọ', "{\\d o}");
        case L'Ỏ' ... L'ợ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ụ', "{\\d U}");
        SEQ(L'ụ', "{\\d u}");
        case L'Ủ' ... L'ự':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ỳ', "{\\`Y}");
        SEQ(L'ỳ', "{\\`y}");
        SEQ(L'Ỵ', "{\\d Y}");
        SEQ(L'ỵ', "{\\d y}");
        case L'Ỷ' ... L'ỷ':        return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'Ỹ', "{\\~Y}");
        SEQ(L'ỹ', "{\\~y}");
        SEQ(L'Ỻ', "IL");
        case L'ỻ' ... L'ỿ':        return UTF8TOTEX_UNSUPPORTED;

        /* Greek extended */
        SEQ(L'Ῐ', "{\\u I}");
        SEQ(L'Ῑ', "{\\=I}");
        case 0x1fdc:               return UTF8TOTEX_INVALID;
        SEQ(L'Ῠ', "{\\u Y}");
        SEQ(L'Ῡ', "{\\=Y}");
        case 0x1ff0 ... 0x1ff1:    return UTF8TOTEX_INVALID;
        case 0x1ff5:               return UTF8TOTEX_INVALID;
        case 0x1fff:               return UTF8TOTEX_INVALID;

        /* Letterlike symbols */
        SEQ_TC(L'℃', "{\\textdegree}C");
        SEQ_TC(L'℉', "{\\textdegree}F");
        SEQ(L'™', "{\\texttrademark}");

        /* General punctuation */
        SEQ(L'‐', "{-}");
        SEQ(L'–', "{--}");
        SEQ(L'—', "{---}");
        SEQ(L'‘', "{`}");
        SEQ(L'’', "{'}");
        SEQ(L'“', "{``}");
        SEQ(L'”', "{''}");
        SEQ(L'†', "{\\dag}");
        SEQ(L'‡', "{\\ddag}");
        SEQ(L'•', "{\\textbullet}");
        SEQ(L'․', ".");
        SEQ(L'‥', "..");
        SEQ(L'…', "{\\dots}");
        SEQ(L'‧', "{\\textperiodcentered}");
        SEQ(L'‰', "{\\textperthousand}");
        SEQ(L'‱', "{\\textpertenthousand}");
        SEQ_T1(L'‹', "{\\guilsinglleft}");
        SEQ_T1(L'›', "{\\guilsinglright}");
        SEQ(L'⁀', "{\\t  }");
        SEQ(L'⁇', "??");
        SEQ(L'⁈', "?!");
        SEQ(L'⁉', "!?");

        /* XXX */
        SEQ(L'⁰', "\\textsuperscript{0}");
        SEQ(L'ⁱ', "\\textsuperscript{i}");
        case 0x2072 ... 0x2073:    return UTF8TOTEX_INVALID;
        SEQ(L'⁴', "\\textsuperscript{4}");
        SEQ(L'⁵', "\\textsuperscript{5}");
        SEQ(L'⁶', "\\textsuperscript{6}");
        SEQ(L'⁷', "\\textsuperscript{7}");
        SEQ(L'⁸', "\\textsuperscript{8}");
        SEQ(L'⁹', "\\textsuperscript{9}");
        SEQ(L'⁺', "\\textsuperscript{+}");
        SEQ(L'⁻', "\\textsuperscript{-}");
        SEQ(L'⁼', "\\textsuperscript{=}");
        SEQ(L'⁽', "\\textsuperscript{(}");
        SEQ(L'⁾', "\\textsuperscript{)}");
        SEQ(L'ⁿ', "\\textsuperscript{n}");
        SEQ(L'₀', "\\textsubscript{0}");
        SEQ(L'₁', "\\textsubscript{1}");
        SEQ(L'₂', "\\textsubscript{2}");
        SEQ(L'₃', "\\textsubscript{3}");
        SEQ(L'₄', "\\textsubscript{4}");
        SEQ(L'₅', "\\textsubscript{5}");
        SEQ(L'₆', "\\textsubscript{6}");
        SEQ(L'₇', "\\textsubscript{7}");
        SEQ(L'₈', "\\textsubscript{8}");
        SEQ(L'₉', "\\textsubscript{9}");
        SEQ(L'₊', "\\textsubscript{+}");
        SEQ(L'₋', "\\textsubscript{-}");
        SEQ(L'₌', "\\textsubscript{=}");
        SEQ(L'₍', "\\textsubscript{(}");
        SEQ(L'₎', "\\textsubscript{)}");
        case 0x208f:               return UTF8TOTEX_INVALID;
        SEQ(L'ₐ', "\\textsubscript{a}");
        SEQ(L'ₑ', "\\textsubscript{e}");
        SEQ(L'ₒ', "\\textsubscript{o}");
        SEQ(L'ₓ', "\\textsubscript{x}");
        case L'ₔ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'ₕ', "\\textsubscript{h}");
        SEQ(L'ₖ', "\\textsubscript{k}");
        SEQ(L'ₗ', "\\textsubscript{l}");
        SEQ(L'ₘ', "\\textsubscript{m}");
        SEQ(L'ₙ', "\\textsubscript{n}");
        SEQ(L'ₚ', "\\textsubscript{p}");
        SEQ(L'ₛ', "\\textsubscript{s}");
        SEQ(L'ₜ', "\\textsubscript{t}");
        case 0x209d ... 0x209f:    return UTF8TOTEX_INVALID;

        case 0x20bf ... 0x20cf:    return UTF8TOTEX_INVALID;

        /* Number forms */
        SEQ(L'Ⅰ', "I");
        SEQ(L'Ⅱ', "II");
        SEQ(L'Ⅲ', "III");
        SEQ(L'Ⅳ', "IV");
        SEQ(L'Ⅴ', "V");
        SEQ(L'Ⅵ', "VI");
        SEQ(L'Ⅶ', "VII");
        SEQ(L'Ⅷ', "VIII");
        SEQ(L'Ⅸ', "IX");
        SEQ(L'Ⅹ', "X");
        SEQ(L'Ⅺ', "XI");
        SEQ(L'Ⅻ', "XII");
        SEQ(L'Ⅼ', "L");
        SEQ(L'Ⅽ', "C");
        SEQ(L'Ⅾ', "D");
        SEQ(L'Ⅿ', "M");
        SEQ(L'ⅰ', "i");
        SEQ(L'ⅱ', "ii");
        SEQ(L'ⅲ', "iii");
        SEQ(L'ⅳ', "iv");
        SEQ(L'ⅴ', "v");
        SEQ(L'ⅵ', "vi");
        SEQ(L'ⅶ', "vii");
        SEQ(L'ⅷ', "viii");
        SEQ(L'ⅸ', "ix");
        SEQ(L'ⅹ', "x");
        SEQ(L'ⅺ', "xi");
        SEQ(L'ⅻ', "xii");
        SEQ(L'ⅼ', "l");
        SEQ(L'ⅽ', "c");
        SEQ(L'ⅾ', "d");
        SEQ(L'ⅿ', "m");

        case 0x218c ... 0x218f:    return UTF8TOTEX_INVALID;

        /* Mathematical operatos */
        SEQ(L'∆', "$\\bigtriangleup$");
        SEQ(L'∇', "$\\bigtriangledown$");
        SEQ(L'∐', "$\\amalg$");
        SEQ(L'∑', "$\\Sigma$");
        SEQ(L'−', "$-$");
        SEQ(L'∓', "$\\mp$");
        SEQ(L'∕', "$/$");
        SEQ(L'∗', "$*$");
        SEQ(L'∙', "$\\bullet$");
        SEQ(L'∧', "$\\wedge$");
        SEQ(L'∨', "$\\vee$");
        SEQ(L'∩', "$\\cap$");
        SEQ(L'∪', "$\\cup$");
        SEQ(L'⊓', "$\\sqcap$");
        SEQ(L'⊔', "$\\sqcup$");
        SEQ(L'⊕', "$\\oplus$");
        SEQ(L'⊖', "$\\ominus$");
        SEQ(L'⊗', "$\\otimes$");
        SEQ(L'⊘', "$\\oslash$");
        SEQ(L'⊙', "$\\odot$");

        /* Enclosed alphanumerics */
        SEQ(L'⑴', "(1)");
        SEQ(L'⑵', "(2)");
        SEQ(L'⑶', "(3)");
        SEQ(L'⑷', "(4)");
        SEQ(L'⑸', "(5)");
        SEQ(L'⑹', "(6)");
        SEQ(L'⑺', "(7)");
        SEQ(L'⑻', "(8)");
        SEQ(L'⑼', "(9)");
        SEQ(L'⑽', "(10)");
        SEQ(L'⑾', "(11)");
        SEQ(L'⑿', "(12)");
        SEQ(L'⒀', "(13)");
        SEQ(L'⒁', "(14)");
        SEQ(L'⒂', "(15)");
        SEQ(L'⒃', "(16)");
        SEQ(L'⒄', "(17)");
        SEQ(L'⒅', "(18)");
        SEQ(L'⒆', "(19)");
        SEQ(L'⒇', "(20)");
        SEQ(L'⒈', "1.");
        SEQ(L'⒉', "2.");
        SEQ(L'⒊', "3.");
        SEQ(L'⒋', "4.");
        SEQ(L'⒌', "5.");
        SEQ(L'⒍', "6.");
        SEQ(L'⒎', "7.");
        SEQ(L'⒏', "8.");
        SEQ(L'⒐', "9.");
        SEQ(L'⒑', "10.");
        SEQ(L'⒒', "11.");
        SEQ(L'⒓', "12.");
        SEQ(L'⒔', "13.");
        SEQ(L'⒕', "14.");
        SEQ(L'⒖', "15.");
        SEQ(L'⒗', "16.");
        SEQ(L'⒘', "17.");
        SEQ(L'⒙', "18.");
        SEQ(L'⒚', "19.");
        SEQ(L'⒛', "20.");
        SEQ(L'⒜', "(a)");
        SEQ(L'⒝', "(b)");
        SEQ(L'⒞', "(c)");
        SEQ(L'⒟', "(d)");
        SEQ(L'⒠', "(e)");
        SEQ(L'⒡', "(f)");
        SEQ(L'⒢', "(g)");
        SEQ(L'⒣', "(h)");
        SEQ(L'⒤', "(i)");
        SEQ(L'⒥', "(j)");
        SEQ(L'⒦', "(k)");
        SEQ(L'⒧', "(l)");
        SEQ(L'⒨', "(m)");
        SEQ(L'⒩', "(n)");
        SEQ(L'⒪', "(o)");
        SEQ(L'⒫', "(p)");
        SEQ(L'⒬', "(q)");
        SEQ(L'⒭', "(r)");
        SEQ(L'⒮', "(s)");
        SEQ(L'⒯', "(t)");
        SEQ(L'⒰', "(u)");
        SEQ(L'⒱', "(v)");
        SEQ(L'⒲', "(w)");
        SEQ(L'⒳', "(x)");
        SEQ(L'⒴', "(y)");
        SEQ(L'⒵', "(z)");

        /* Supplemental maths */
        SEQ(L'⨣', "${\\hat+}$");
        SEQ(L'⨤', "${\\tilde+}$");
        SEQ(L'⨰', "${\\dot\\times}$");
        SEQ(L'⩑', "${\\dot\\wedge}$");
        SEQ(L'⩒', "${\\dot\\vee}$");

        /* CJK compatibility */
        SEQ(L'㍱', "hPa");
        SEQ(L'㍲', "da");
        SEQ(L'㍳', "AU");
        SEQ(L'㍴', "bar");
        SEQ(L'㍵', "oV");
        SEQ(L'㍶', "pc");
        SEQ(L'㍷', "dm");
        SEQ(L'㍸', "dm\\textsuperscript{2}");
        SEQ(L'㍹', "dm\\textsuperscript{3}");
        SEQ(L'㍺', "IU");
        SEQ(L'㎀', "pA");
        SEQ(L'㎁', "nA");
        SEQ(L'㎂', "$\\mu$A");
        SEQ(L'㎃', "mA");
        SEQ(L'㎄', "kA");
        SEQ(L'㎅', "KB");
        SEQ(L'㎆', "MB");
        SEQ(L'㎇', "GB");
        SEQ(L'㎈', "cal");
        SEQ(L'㎉', "kcal");
        SEQ(L'㎊', "pF");
        SEQ(L'㎋', "nF");
        SEQ(L'㎌', "$\\mu$F");
        SEQ(L'㎍', "$\\mu$g");
        SEQ(L'㎎', "mg");
        SEQ(L'㎏', "kg");
        SEQ(L'㎐', "Hz");
        SEQ(L'㎑', "kHz");
        SEQ(L'㎒', "MHz");
        SEQ(L'㎓', "GHz");
        SEQ(L'㎔', "THz");
        SEQ(L'㎙', "fm");
        SEQ(L'㎚', "nm");
        SEQ(L'㎛', "$\\mu$m");
        SEQ(L'㎜', "mm");
        SEQ(L'㎝', "cm");
        SEQ(L'㎞', "km");
        SEQ(L'㎟', "mm\\textsuperscript{2}");
        SEQ(L'㎠', "cm\\textsuperscript{2}");
        SEQ(L'㎡', "m\\textsuperscript{2}");
        SEQ(L'㎢', "km\\textsuperscript{2}");
        SEQ(L'㎣', "mm\\textsuperscript{3}");
        SEQ(L'㎤', "cm\\textsuperscript{3}");
        SEQ(L'㎥', "m\\textsuperscript{3}");
        SEQ(L'㎦', "km\\textsuperscript{3}");
        SEQ(L'㎩', "Pa");
        SEQ(L'㎪', "kPa");
        SEQ(L'㎫', "MPa");
        SEQ(L'㎬', "GPa");
        SEQ(L'㎭', "rad");
        SEQ(L'㎮', "rad/s");
        SEQ(L'㎯', "rad/s\\textsuperscript{2}");
        SEQ(L'㎰', "ps");
        SEQ(L'㎱', "ns");
        SEQ(L'㎲', "$\\mu$s");
        SEQ(L'㎳', "ms");
        SEQ(L'㎴', "pV");
        SEQ(L'㎵', "nV");
        SEQ(L'㎶', "$\\mu$V");
        SEQ(L'㎷', "mV");
        SEQ(L'㎸', "kV");
        SEQ(L'㎹', "MV");
        SEQ(L'㎺', "pW");
        SEQ(L'㎻', "nW");
        SEQ(L'㎼', "$\\mu$W");
        SEQ(L'㎽', "mW");
        SEQ(L'㎾', "kW");
        SEQ(L'㎿', "MW");
        SEQ(L'㏀', "k$\\Omega$");
        SEQ(L'㏁', "M$\\Omega$");
        SEQ(L'㏂', "a.m.");
        SEQ(L'㏃', "Bq");
        SEQ(L'㏄', "cc");
        SEQ(L'㏅', "cd");
        SEQ(L'㏆', "C/kg");
        SEQ(L'㏇', "Co.");
        SEQ(L'㏈', "dB");
        SEQ(L'㏉', "Gy");
        SEQ(L'㏊', "ha");
        SEQ(L'㏌', "in");
        SEQ(L'㏍', "K.K.");
        SEQ(L'㏎', "KM");
        SEQ(L'㏏', "kt");
        SEQ(L'㏐', "lm");
        SEQ(L'㏑', "ln");
        SEQ(L'㏒', "log");
        SEQ(L'㏓', "lx");
        SEQ(L'㏔', "mb");
        SEQ(L'㏕', "mil");
        SEQ(L'㏖', "mol");
        SEQ(L'㏗', "pH");
        SEQ(L'㏘', "p.m.");
        SEQ(L'㏙', "PPM");
        SEQ(L'㏚', "PR");
        SEQ(L'㏛', "sr");
        SEQ(L'㏜', "Sv");
        SEQ(L'㏝', "Wb");

        /* Private use area */
        case 0xe000 ... 0xf8ff:    return UTF8TOTEX_INVALID;

        /* CJK compatibility ideographs */
        case 0xfada ... 0xfaff:    return UTF8TOTEX_INVALID;

        SEQ(L'ﬀ', "ff");
        SEQ(L'ﬁ', "fi");
        SEQ(L'ﬂ', "fl");
        SEQ(L'ﬃ', "ffi");
        SEQ(L'ﬄ', "ffl");
        case L'ﬅ':                 return UTF8TOTEX_UNSUPPORTED;
        SEQ(L'ﬆ', "st");
        case 0xfb07 ... 0xfb12:    return UTF8TOTEX_INVALID;

        /* Small font variants */
        case 0xfe6c ... 0xfe6f:    return UTF8TOTEX_INVALID;

        /* Halfwidth and fullwidth forms */
        case 0xff00:               return UTF8TOTEX_INVALID;
        SEQ(L'！', "!");
        SEQ(L'＂', "\"");
        SEQ(L'＃', "{\\#}");
        SEQ(L'＄', "{\\$}");
        SEQ(L'％', "{\\%}");
        SEQ(L'＆', "{\\&}");
        SEQ(L'＇', "'");
        SEQ(L'（', "(");
        SEQ(L'）', ")");
        SEQ(L'＊', "*");
        SEQ(L'＋', "+");
        SEQ(L'，', ",");
        SEQ(L'－', "-");
        SEQ(L'．', ".");
        SEQ(L'／', ".");
        SEQ(L'０', "0");
        SEQ(L'１', "1");
        SEQ(L'２', "2");
        SEQ(L'３', "3");
        SEQ(L'４', "4");
        SEQ(L'５', "5");
        SEQ(L'６', "6");
        SEQ(L'７', "7");
        SEQ(L'８', "8");
        SEQ(L'９', "9");
        SEQ(L'：', ":");
        SEQ(L'；', ";");
        SEQ(L'＜', "{\\textless}");
        SEQ(L'＝', "=");
        SEQ(L'＞', "{\\textgreater}");
        SEQ(L'？', "?");
        SEQ(L'＠', "@");
        SEQ(L'Ａ', "A");
        SEQ(L'Ｂ', "B");
        SEQ(L'Ｃ', "C");
        SEQ(L'Ｄ', "D");
        SEQ(L'Ｅ', "E");
        SEQ(L'Ｆ', "F");
        SEQ(L'Ｇ', "G");
        SEQ(L'Ｈ', "H");
        SEQ(L'Ｉ', "I");
        SEQ(L'Ｊ', "J");
        SEQ(L'Ｋ', "K");
        SEQ(L'Ｌ', "L");
        SEQ(L'Ｍ', "M");
        SEQ(L'Ｎ', "N");
        SEQ(L'Ｏ', "O");
        SEQ(L'Ｐ', "P");
        SEQ(L'Ｑ', "Q");
        SEQ(L'Ｒ', "R");
        SEQ(L'Ｓ', "S");
        SEQ(L'Ｔ', "T");
        SEQ(L'Ｕ', "U");
        SEQ(L'Ｖ', "V");
        SEQ(L'Ｗ', "W");
        SEQ(L'Ｘ', "X");
        SEQ(L'Ｙ', "Y");
        SEQ(L'Ｚ', "Z");
        SEQ(L'［', "[");
        SEQ(L'＼', "{\\letterbackslash}");
        SEQ(L'］', "]");
        SEQ(L'＾', "{\\letterhat}");
        SEQ(L'＿', "{\\letterunderscore}");
        SEQ(L'｀', "{\\`}");
        SEQ(L'ａ', "a");
        SEQ(L'ｂ', "b");
        SEQ(L'ｃ', "c");
        SEQ(L'ｄ', "d");
        SEQ(L'ｅ', "e");
        SEQ(L'ｆ', "f");
        SEQ(L'ｇ', "g");
        SEQ(L'ｈ', "h");
        SEQ(L'ｉ', "i");
        SEQ(L'ｊ', "j");
        SEQ(L'ｋ', "k");
        SEQ(L'ｌ', "l");
        SEQ(L'ｍ', "m");
        SEQ(L'ｎ', "n");
        SEQ(L'ｏ', "o");
        SEQ(L'ｐ', "p");
        SEQ(L'ｑ', "q");
        SEQ(L'ｒ', "r");
        SEQ(L'ｓ', "s");
        SEQ(L'ｔ', "t");
        SEQ(L'ｕ', "u");
        SEQ(L'ｖ', "v");
        SEQ(L'ｗ', "w");
        SEQ(L'ｘ', "x");
        SEQ(L'ｙ', "y");
        SEQ(L'ｚ', "z");
        SEQ(L'｛', "{\\{}");
        SEQ(L'｜', "|");
        SEQ(L'｝', "{\\}}");
        SEQ(L'～', "{\\lettertilde}");
        SEQ(L'｟', "((");
        SEQ(L'｠', "))");
        case 0xffc0 ... 0xffc1:    return UTF8TOTEX_INVALID;
        case 0xffc8 ... 0xffc9:    return UTF8TOTEX_INVALID;
        case 0xffd0 ... 0xffd1:    return UTF8TOTEX_INVALID;
        case 0xffd8 ... 0xffd9:    return UTF8TOTEX_INVALID;
        case 0xffdd ... 0xffdf:    return UTF8TOTEX_INVALID;
        SEQ(L'￠', "{\\textcent}");
        SEQ(L'￡', "{\\pounds}");
        SEQ_TC(L'￢', "{\\textlnot}");
        SEQ(L'￣', "{\\= }");

        case 0xffe7:               return UTF8TOTEX_INVALID;

        case 0xffef ... 0xfff8:    return UTF8TOTEX_INVALID;

        case 0xfffc:               return UTF8TOTEX_INVALID;

        /* They actually created two characters called "Not a character." We
         * have reached full inception.
         */
        case 0xfffe ... 0xffff:    return UTF8TOTEX_INVALID;

        case 0x1000c:              return UTF8TOTEX_INVALID;

        case 0x10027:              return UTF8TOTEX_INVALID;

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
