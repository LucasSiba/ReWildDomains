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
        printf("\033[31m" "FAIL: Expected pattern '%s' to %s with domain '%s'" "\033[0m"" \n",
               pattern, match_to_str(expecation), domain);
        return_code++;
    } else {
        printf("PASS: Pattern '%s' %s with domain '%s'\n",
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

    // Partial label wildcards
    wd_match_test("*ww.google.com", "www.google.com", WD_MATCH);
    wd_match_test("w*w.google.com", "www.google.com", WD_MATCH);
    wd_match_test("ww*.google.com", "www.google.com", WD_MATCH);
    wd_match_test("www.*oogle.com", "www.google.com", WD_MATCH);
    wd_match_test("www.*gle.com",   "www.google.com", WD_MATCH);
    wd_match_test("www.goo*le.com", "www.google.com", WD_MATCH);
    wd_match_test("www.goo*e.com",  "www.google.com", WD_MATCH);
    wd_match_test("www.goo*.com",   "www.google.com", WD_MATCH);
    wd_match_test("www.goog*e.com", "www.google.com", WD_MATCH);
    wd_match_test("www.googl*.com", "www.google.com", WD_MATCH);
    wd_match_test("www.google.*om", "www.google.com", WD_MATCH);
    wd_match_test("www.google.**m", "www.google.com", WD_MATCH);
    wd_match_test("www.google.***", "www.google.com", WD_MATCH);
    wd_match_test("www.google.c**", "www.google.com", WD_MATCH);
    wd_match_test("www.google.c*m", "www.google.com", WD_MATCH);
    wd_match_test("www.google.**m", "www.google.com", WD_MATCH);
    wd_match_test("www.google.*o*", "www.google.com", WD_MATCH);

    // negative partial label wildcards
    wd_match_test("www.google.*z",  "www.google.com", WD_NO_MATCH);
    wd_match_test("www.googl*.zom", "www.google.com", WD_NO_MATCH);
    wd_match_test("www.google*com", "www.google.com", WD_NO_MATCH);

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

    // special case of trailing wildcard
    wd_match_test("*",               "www.google.com", WD_MATCH);
    wd_match_test("w*",              "www.google.com", WD_MATCH);
    wd_match_test("ww*",             "www.google.com", WD_MATCH);
    wd_match_test("www*",            "www.google.com", WD_MATCH);
    wd_match_test("www.*",           "www.google.com", WD_MATCH);
    wd_match_test("www.g*",          "www.google.com", WD_MATCH);
    wd_match_test("www.google*",     "www.google.com", WD_MATCH);
    wd_match_test("www.google.*",    "www.google.com", WD_MATCH);
    wd_match_test("www.google.c*",   "www.google.com", WD_MATCH);
    wd_match_test("www.google.co*",  "www.google.com", WD_MATCH);
    wd_match_test("www.google.com*", "www.google.com", WD_NO_MATCH); // ***

    if (return_code) {
        printf("\033[31m" "Failure count: %d\n", return_code);
    }
    printf("Done\n");
    return return_code;
}
