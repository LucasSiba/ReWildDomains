# WildDomains
WildDomains is a simple (one function) library for matching domains to a pattern.

Aside from a single character-for-charcter match, it also supports ```*``` as a domain label wildcard.
The ```*``` wildcard is non-greedy, up to a domain label (where domain labels are seperated by a ```.```).
There is an additional special case where a trailing ```*``` becomes a greedy match-anything including multiple labels.

See the unit tests for clarifying examples.
