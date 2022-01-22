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

    while (*pat != 0 || *dom != 0) {

        if (*pat == '*')  {
            return WD_MATCH;
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
