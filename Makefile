CC = gcc
CFLAGS = -Os -g -Wall -Werror -Idudect -I.

# Emit a warning should any variable-length array be found within the code.
CFLAGS += -Wvla

all: main

tid := 0

# Control test case option of valgrind
ifeq ("$(tid)","0")
    TCASE :=
else
    TCASE := -t $(tid)
endif

# Control the build verbosity
ifeq ("$(VERBOSE)","1")
    Q :=
    VECHO = @true
else
    Q := @
    VECHO = @printf
endif

# Enable sanitizer(s) or not
ifeq ("$(SANITIZER)","1")
    # https://github.com/google/sanitizers/wiki/AddressSanitizerFlags
    CFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-common
    LDFLAGS += -fsanitize=address
endif


OBJS := main.o q1.o q2.o q1q2.o

deps := $(OBJS:%.o=.%.o.d)

main: $(OBJS)
	$(VECHO) "  LD\t$@\n"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^ -lm

%.o: %.c
	@mkdir -p .$(DUT_DIR)
	$(VECHO) "  CC\t$@\n"
	$(Q)$(CC) -o $@ $(CFLAGS) -c -MMD -MF .$@.d $<

clean:
	rm -f $(OBJS) $(deps) *~ main
	rm -rf *.dSYM

-include $(deps)
