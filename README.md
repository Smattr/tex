# Library for translating UTF-8 into ASCII TeX

This library provides basic functionality for translating UTF-8 data into ASCII
TeX, safe for consumption by `pdflatex` and other tools. It maps unicode
characters to their equivalent LaTeX escape sequences, trying to use the
shortest safe escape sequence where possible.

## But... why?

Because apparently even in the 21st century there are still some LaTeX
environments that don't fully support UTF-8.

## Legal

All code in this repository is in the public domain. Use it in whatever way you
see fit. However, if you're forking this code to make some modifications
because it doesn't suit your needs, perhaps consider asking me about your use
case first. If I'm in a good mood, I might implement the feature you want.
