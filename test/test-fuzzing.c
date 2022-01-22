#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "WildDomains.h"

int
main(void)
{
    unsigned itterations;

    for (itterations = 10000000; itterations --> 0;) {
#       define BUF_SIZE 50
        char pat[BUF_SIZE + 1];
        char dom[BUF_SIZE + 1];

        int x;
        int len = (rand() % BUF_SIZE) + 1;
        for (x = 0; x < len; x++) {
            pat[x] = (char)(rand() % 255);
            if (pat[x] < 32 || pat[x] > 126) { x--; }
        }
        pat[len] = 0;

        x = 0;
        len = (rand() % BUF_SIZE) + 1;
        for (x = 0; x < len; x++) {
            dom[x] = (char)(rand() % 255);
            if (dom[x] < 32 || dom[x] > 126) { x--; }
        }
        dom[len] = 0;

        if (wd_match(pat, dom) == WD_MATCH) {
            printf("'%s' matched '%s'\n", pat, dom);
        }
    }

    return 0;
}
