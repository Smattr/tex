#include <errno.h>
#include <getopt.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utf8totex/utf8totex.h"

int main(int argc, char **argv) {

    setlocale(LC_ALL, NULL);

    FILE *in = NULL;
    FILE *out = NULL;

    int _fuzzy = 0;
    int _encoding = UTF8TOTEX_FE_OT1;
    int _textcomp = 0;
    while (true) {
        struct option options[] = {
            {"input", required_argument, 0, 'i'},
            {"output", required_argument, 0, 'o'},
            {"ot1", no_argument, &_encoding, (int)UTF8TOTEX_FE_OT1},
            {"ot2", no_argument, &_encoding, (int)UTF8TOTEX_FE_OT2},
            {"ot3", no_argument, &_encoding, (int)UTF8TOTEX_FE_OT3},
            {"ot4", no_argument, &_encoding, (int)UTF8TOTEX_FE_OT4},
            {"ot6", no_argument, &_encoding, (int)UTF8TOTEX_FE_OT6},
            {"t1", no_argument, &_encoding, (int)UTF8TOTEX_FE_T1},
            {"t2a", no_argument, &_encoding, (int)UTF8TOTEX_FE_T2A},
            {"t2b", no_argument, &_encoding, (int)UTF8TOTEX_FE_T2B},
            {"t2c", no_argument, &_encoding, (int)UTF8TOTEX_FE_T2C},
            {"t3", no_argument, &_encoding, (int)UTF8TOTEX_FE_T3},
            {"t4", no_argument, &_encoding, (int)UTF8TOTEX_FE_T4},
            {"t5", no_argument, &_encoding, (int)UTF8TOTEX_FE_T5},
            {"ts1", no_argument, &_encoding, (int)UTF8TOTEX_FE_TS1},
            {"ts3", no_argument, &_encoding, (int)UTF8TOTEX_FE_TS3},
            {"x2", no_argument, &_encoding, (int)UTF8TOTEX_FE_X2},
            {"oml", no_argument, &_encoding, (int)UTF8TOTEX_FE_OML},
            {"oms", no_argument, &_encoding, (int)UTF8TOTEX_FE_OMS},
            {"omx", no_argument, &_encoding, (int)UTF8TOTEX_FE_OMX},
            {"textcomp", no_argument, &_textcomp, 1},
            {"fuzzy", no_argument, &_fuzzy, 1},
            {"no-fuzzy", no_argument, &_fuzzy, 0},
            {0},
        };

        int index;
        int c = getopt_long(argc, argv, "i:o:", options, &index);

        if (c == -1)
            break;

        switch (c) {

            case 0:
                break;

            case 'i':
                if (in != NULL)
                    fclose(in);
                in = fopen(optarg, "r");
                if (in == NULL) {
                    fprintf(stderr, "failed to open %s for reading\n", optarg);
                    return EXIT_FAILURE;
                }
                break;

            case 'o':
                if (out != NULL)
                    fclose(out);
                out = fopen(optarg, "w");
                if (out == NULL) {
                    fprintf(stderr, "failed to open %s for writing\n", optarg);
                    return EXIT_FAILURE;
                }
                break;

            case '?':
                fprintf(stderr, "Usage: %s options...\n"
                                " --input FILE\n"
                                " -i FILE         Read from FILE instead of stdin\n"
                                " --output FILE\n"
                                " -o FILE         Write to FILE instead of stdout\n"
                                " --textcomp      Assume \\usepackage{textcomp}\n"
                                " --fuzzy         Enable fuzzy mode\n"
                                " --no-fuzzy      Disable fuzzy mode\n"
                                " --ot1\n"
                                " --ot2\n"
                                " --ot3\n"
                                " --ot4\n"
                                " --ot6\n"
                                " --t1\n"
                                " --t2a\n"
                                " --t2b\n"
                                " --t2c\n"
                                " --t3\n"
                                " --t4\n"
                                " --t5\n"
                                " --ts1\n"
                                " --ts3\n"
                                " --x2\n"
                                " --oml\n"
                                " --oms\n"
                                " --omx           Assume a particular font encoding\n"
                                , argv[0]);
                return EXIT_FAILURE;

            default:
                return EXIT_FAILURE;
        }
    }

    utf8totex_environment_t env = UTF8TOTEX_DEFAULT_ENVIRONMENT;
    env.font_encoding = _encoding;
    if (_textcomp)
        env.textcomp = true;
    bool fuzzy = !!_fuzzy;

    if (in == NULL)
        in = stdin;

    if (out == NULL)
        out = stdout;

    char *line = NULL;
    size_t n;
    unsigned int lineno = 1;
    while (getline(&line, &n, in) != -1) {
        utf8totex_char_t error;
        if (utf8totex_fputs(line, fuzzy, env, out, &error) == EOF) {
            fprintf(stderr, "failed to write line %u to output: %s\n", lineno,
                error == UTF8TOTEX_EOF ? "resource allocation failure" :
                error == UTF8TOTEX_INVALID ? "invalid UTF-8 character" :
                error == UTF8TOTEX_UNSUPPORTED ? "unsupported UTF-8 character" :
                error == UTF8TOTEX_BAD_MODIFIER ? "bad modifier character" :
                "unknown");
            fclose(out);
            fclose(in);
            return EXIT_FAILURE;
        }
        lineno++;
    }

    if (errno != 0) {
        fprintf(stderr, "failed to read line from input\n");
        fclose(out);
        fclose(in);
        return EXIT_FAILURE;
    }

    free(line);
    fclose(out);
    fclose(in);
    return EXIT_SUCCESS;
}
