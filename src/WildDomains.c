#include <stdio.h>

#include "WildDomains.h"

int
wd_match(const char* pattern, const char* domain)
{
#define pat pattern
#define dom domain
    if (pat == NULL || dom == NULL) {
        return WD_NO_MATCH;
    }

    while (*pat != 0 && *dom != 0) {

        //printf("Outter: pat=%s, dom=%s\n", pat, dom);
        if (*pat == '*')  {
            if (*(++pat) == 0) { // note the increment
                return WD_MATCH;
            }

            if (*pat == '*' || *dom == '.') {
                continue;
            }

            do { // must consume at least one char
                dom++;
                //printf("Inner: pat=%s, dom=%s\n", pat, dom);
                if (*dom == 0) {
                    return WD_NO_MATCH;
                }
            } while (*pat != *dom && *dom != '.');

            continue;
        }

        if (*pat != *dom) {
            return WD_NO_MATCH;
        }
        pat++; dom++;
    }

    if (*pat == 0 && *dom == 0) {
        return WD_MATCH;
    }

    return WD_NO_MATCH;
}
