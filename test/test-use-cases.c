#include <stdio.h>

#include "WildDomains.h"

int return_code = 0;

const char* match_to_str(int match);
void        wd_match_test(const char *pattern, const char *domain, int expecation);

const char*
match_to_str(int match) { return match ? "NO-MATCH" : "MATCH"; }

void
wd_match_test(const char *pattern, const char *domain, int expecation)
{
    if (wd_match(pattern, domain) != expecation) {
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
    wd_match_test("www.google.com", "www.google.com", WD_MATCH);
    wd_match_test("*.google.com",   "www.google.com", WD_MATCH);
    wd_match_test("www.google.*",   "www.google.com", WD_MATCH);
    wd_match_test("www.*.com",      "www.google.com", WD_MATCH);
    wd_match_test("*.google.*",     "www.google.com", WD_MATCH);

    // Basic negative test cases
    wd_match_test("ttt.google.com", "www.google.com", WD_NO_MATCH);
    wd_match_test("www.tttttt.com", "www.google.com", WD_NO_MATCH);
    wd_match_test("www.google.ttt", "www.google.com", WD_NO_MATCH);
    wd_match_test("ttt.*.com",      "www.google.com", WD_NO_MATCH);
    wd_match_test("*.tttttt.com",   "www.google.com", WD_NO_MATCH);
    wd_match_test("*.tttttt.*",     "www.google.com", WD_NO_MATCH);
    wd_match_test("*.google.ttt",   "www.google.com", WD_NO_MATCH);
    wd_match_test("www.*.ttt",      "www.google.com", WD_NO_MATCH);

    // Special wild cases
    wd_match_test("*",       "www.google.com", WD_MATCH);
    wd_match_test("*.*",     "www.google.com", WD_MATCH);
    wd_match_test("*.*.*",   "www.google.com", WD_MATCH);
    wd_match_test("*.*.*.*", "www.google.com", WD_NO_MATCH);

    // More negative stuff
    wd_match_test("abc.def.com", "bc.def.com",  WD_NO_MATCH);
    wd_match_test("bc.def.com",  "abc.def.com", WD_NO_MATCH);
    wd_match_test("abc.def.com", "abc.df.com",  WD_NO_MATCH);
    wd_match_test("abc.df.com",  "abc.def.com", WD_NO_MATCH);
    wd_match_test("abc.def.co",  "abc.def.com", WD_NO_MATCH);
    wd_match_test("abc.def.com", "abc.def.co",  WD_NO_MATCH);

    // input validation
    wd_match_test(NULL,             "www.google.com", WD_NO_MATCH);
    wd_match_test("www.google.com", NULL,             WD_NO_MATCH);
    wd_match_test(NULL,             NULL,             WD_NO_MATCH);

    // wild card matches across multiple labels

    return return_code;
}
