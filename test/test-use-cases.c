#include <stdio.h>

#include "ReWildDomains.h"

int
main(void)
{
    if (rwd_match("*.google.com", "www.google.com") != 0) {
        return 1;
    }

    return 0;
}
