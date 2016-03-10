#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include "tex/tex.h"

const char *tex_from_char(uint32_t c) {

    switch (c) {

        /* Standard LaTeX special characters */
        case L'\\': return "\\letterbackslash{}";
        case L'&':  return "\\&";
        case L'%':  return "\\%";
        case L'$':  return "\\$";
        case L'#':  return "\\#";
        case L'_':  return "\\letterunderscore{}";
        case L'{':  return "\\letteropenbrace{}";
        case L'}':  return "\\letterclosebrace{}";
        case L'~':  return "\\lettertilde{}";
        case L'^':  return "\\letterhat{}";

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
        case L'<':  return "\\textless{}";
        case L'>':  return "\\textgreater{}";

        /* Superscript and subscript */
        case L'⁰':  return "\\textsuperscript{0}";
        case L'¹':  return "\\textsuperscript{1}";
        case L'²':  return "\\textsuperscript{2}";
        case L'³':  return "\\textsuperscript{3}";
        case L'⁴':  return "\\textsuperscript{4}";
        case L'⁵':  return "\\textsuperscript{5}";
        case L'⁶':  return "\\textsuperscript{6}";
        case L'⁷':  return "\\textsuperscript{7}";
        case L'⁸':  return "\\textsuperscript{8}";
        case L'⁹':  return "\\textsuperscript{9}";
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
        case L'τ':  return "$\\tau{}$";
        /* XXX: the rest of Greek */

        /* Greek superscripts */
        case L'ᵝ':  return "\\textsuperscript{$\\beta{}$}"; 
        /*ᵞ   ᵟ   ᵋ           ᶿ   ᶥ                                           ᶹ   ᵠ   ᵡ       
        Subscript minuscule     ᵦ   ᵧ                                                       ᵨ               ᵩ   ᵪ   
        ᶛ ᶜ ᶝ ᶞ ᶟ ᶠ ᶡ ᶢ ᶣ ᶤ ᶥ ᶦ ᶧ ᶨ ᶩ ᶪ ᶫ ᶬ ᶭ ᶮ ᶯ ᶰ ᶱ ᶲ ᶳ ᶴ ᶵ ᶶ ᶷ ᶸ ᶹ ᶺ ᶻ ᶼ ᶽ ᶾ ᶿ.*/

        /* German */
        case L'ß':  return "{\\ss}";

        /* Other misc symbols */
        case L'§':  return "\\S{}";
        case L'—':  return "\\textemdash";

    }

    assert(c <= 127 && "unhandled extended character");

    return NULL;
}
