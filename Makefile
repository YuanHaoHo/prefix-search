CC := gcc
TESTS = \
    test_cpy \
    test_ref

TEST_D = s Tai

CFLAGS = -Wall -Werror -g

GIT_HOOKS := .git/hooks/applied
.PHONY: all
all: $(GIT_HOOKS) $(TESTS)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

# Control the build verbosity                                                   
ifeq ("$(VERBOSE)","1")
    Q :=
    VECHO = @true
else
    Q := @
    VECHO = @printf
endif

.PHONY: all clean

all: $(GIT_HOOKS) $(TESTS)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

OBJS_LIB = \
    tst.o \
    bench.o \

CAL = \
    calculate_pref \

OBJS := \
    $(OBJS_LIB) \
    test_cpy.o \
    test_ref.o

BENTXT := \
    bench_cpy.txt \
    bench_ref.txt \
    calculate_bench.txt \
    calculate_pref.txt \
    pref_cpy.txt \
    pref_ref.txt

BEN = \
	test_cpy \
	test_ref

deps := $(OBJS:%.o=.%.o.d)

test_%: test_%.o $(OBJS_LIB)
	$(VECHO) "  LD\t$@\n"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(VECHO) "  CC\t$@\n"
	$(Q)$(CC) -o $@ $(CFLAGS) -c -MMD -MF .$@.d $<

pref:  $(TESTS)
	echo 3 | sudo tee /proc/sys/vm/drop_caches;
	perf stat --repeat 1000 \
                -e cache-misses,cache-references,instructions,cycles \
				./test_ref --bench $(TEST_D)
	perf stat --repeat 1000 \
                -e cache-misses,cache-references,instructions,cycles \
                ./test_cpy --bench $(TEST_D)

bench: $(BEN)
	./test_cpy --bench; 
	./test_ref --bench;

calculate: $(CAL)
	$(CC) -c $^ -o $@  & ./calculate_pref 

plot: 
	gnuplot scripts/runtime.gp
	gnuplot scripts/calculate.gp

clean:
	$(RM) $(TESTS) $(OBJS)
	$(RM) $(deps) $(BENTXT)
	$(RM) $(CAL)

-include $(deps)