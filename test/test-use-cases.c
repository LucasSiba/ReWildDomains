#include <stdio.h>

#include "ReWildDomains.h"

int return_code = 0;

const char* match_to_str(int match);
void        rwd_match_test(const char *pattern, const char *domain, int expecation);

const char*
match_to_str(int match) { return match ? "NO-MATCH" : "MATCH"; }

void
rwd_match_test(const char *pattern, const char *domain, int expecation)
{
    if (rwd_match(pattern, domain) != expecation) {
        printf("\033[31m" "FAIL: Expected pattern '%s' to %s with domain '%s'\n",
               pattern, match_to_str(expecation), domain);
        return_code = 1;
    } else {
        printf("\033[0m" "PASS: Pattern '%s' %s with domain '%s'\n",
               pattern, match_to_str(expecation), domain);
    }
}

int
main(void)
{
    // Blue sky test cases
    rwd_match_test("www.google.com", "www.google.com", RWD_MATCH);
    rwd_match_test("*.google.com",   "www.google.com", RWD_MATCH);
    rwd_match_test("www.google.*",   "www.google.com", RWD_MATCH);
    rwd_match_test("www.*.com",      "www.google.com", RWD_MATCH);
    rwd_match_test("*.google.*",     "www.google.com", RWD_MATCH);

    // Basic negative test cases
    rwd_match_test("ttt.google.com", "www.google.com", RWD_NO_MATCH);
    rwd_match_test("www.tttttt.com", "www.google.com", RWD_NO_MATCH);
    rwd_match_test("www.google.ttt", "www.google.com", RWD_NO_MATCH);
    rwd_match_test("ttt.*.com",      "www.google.com", RWD_NO_MATCH);
    rwd_match_test("*.tttttt.com",   "www.google.com", RWD_NO_MATCH);
    rwd_match_test("*.tttttt.*",     "www.google.com", RWD_NO_MATCH);
    rwd_match_test("*.google.ttt",   "www.google.com", RWD_NO_MATCH);
    rwd_match_test("www.*.ttt",      "www.google.com", RWD_NO_MATCH);

    // Special wild cases
    rwd_match_test("*",       "www.google.com", RWD_MATCH);
    rwd_match_test("*.*",     "www.google.com", RWD_MATCH);
    rwd_match_test("*.*.*",   "www.google.com", RWD_MATCH);
    rwd_match_test("*.*.*.*", "www.google.com", RWD_NO_MATCH);

    // More negative stuff
    rwd_match_test("abc.def.com", "bc.def.com",  RWD_NO_MATCH);
    rwd_match_test("bc.def.com",  "abc.def.com", RWD_NO_MATCH);
    rwd_match_test("abc.def.com", "abc.df.com",  RWD_NO_MATCH);
    rwd_match_test("abc.df.com",  "abc.def.com", RWD_NO_MATCH);
    rwd_match_test("abc.def.co",  "abc.def.com", RWD_NO_MATCH);
    rwd_match_test("abc.def.com", "abc.def.co",  RWD_NO_MATCH);

    // input validation
    rwd_match_test(NULL,             "www.google.com", RWD_NO_MATCH);
    rwd_match_test("www.google.com", NULL,             RWD_NO_MATCH);
    rwd_match_test(NULL,             NULL,             RWD_NO_MATCH);

    // wild card matches across multiple labels

    return return_code;
}
