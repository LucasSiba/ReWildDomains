CPPFLAGS = -I ./src/

CFLAGS   = -O2 -g -rdynamic \
           -fPIC -fstack-protector -fno-strict-aliasing -fno-omit-frame-pointer \
           -Wall -Werror -Wextra -Wcast-align -Wcast-qual -Wformat=2 -Wformat-security \
           -Wmissing-prototypes -Wnested-externs -Wredundant-decls -Wshadow \
           -Wstrict-prototypes -Wno-unknown-pragmas -Wunused -Wno-unused-result \
           -Wwrite-strings -Wno-attributes -Wduplicated-cond -Wlogical-op -Wnull-dereference \
           -Wjump-misses-init -Wdouble-promotion

LDFLAGS  = 
LDLIBS   = 

SOURCES  = src/WildDomains.c
TESTS    = test/test-use-cases.c test/test-fuzzing.c

all: src/WildDomains.o

test: all
test: $(TESTS:.c=.t.pass)

%.t: $(SOURCES:.c=.o) %.o
	$(CC) $(LDFLAGS) $(LOADLIBS) $^ $(LDLIBS) -o $@
%.t.pass: %.t
	./$*.t > $*.t.fail 2>&1 ; if [ $$? != 0 ]; then cat $*.t.fail ; false ; else mv $*.t.fail $*.t.pass ; fi

.PHONY: clean check
.PRECIOUS: %.o %.t

clean:
	rm -f ./src/*.o ./test/*.t ./test/*.t.fail ./test/*.t.pass

check:
	make clean && make test && make clean
	echo
	scan-build-7 make
	rm -rf /tmp/scan-build-202*
	make clean
	echo
	clang-tidy-7 ./src/*.c -header-filter=.* -checks="*,-llvm-header-guard" -- ${CPPFLAGS}
	make clean

# n.o: n.c
# 	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
# n: n.o
#	$(CC) $(LDFLAGS) n.o $(LDLIBS)

# $@ - The file name of the target of the rule
# $< - The name of the first prerequisite
# $^ - The names of all the prerequisites, with spaces between them.
# $* - The stem with which an implicit rule matches
