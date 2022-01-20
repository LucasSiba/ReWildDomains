#include <stdio.h>

#include "ReWildDomains.h"

int
rwd_match(const char* pattern, const char* domain)
{
#define pat pattern
#define dom domain
    if (pat == NULL || dom == NULL) {
        return RWD_NO_MATCH;
    }

    while (*pat != 0 || *dom != 0) {

        if (*pat == '*')  {
            return RWD_MATCH;
        }
        if (*pat != *dom) {
            return RWD_NO_MATCH;
        }

        pat++; dom++;
    }

    if (*pat == 0 && *dom == 0) {
        return RWD_MATCH;
    } else {
        return RWD_NO_MATCH;
    }
}
