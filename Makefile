# Chinookpack Makefile
# Copyright (C) 2011 Pierre-Alexandre St-Jean <pierrealexandre dot stjean at gmail dot com>
# ideas taken from Salvatore Sanfilippo's redis Makefile https://github.com/antirez/redis


OPTIMIZATION?=-O2
CFLAGS?=-std=c99 -Wall
CFLAGS+= $(OPTIMIZATION)
CCLINK?=
CCLINK+=-lm -lc

# Always debug since this library is made to be small and compiled by embeded compiler and not linked
DEBUG= -g -ggdb -D DEBUG


CCCOLOR="\033[34m"
LINKCOLOR="\033[34;1m"
SRCCOLOR="\033[33m"
BINCOLOR="\033[37;1m"
MAKECOLOR="\033[32;1m"
ENDCOLOR="\033[0m"

# To have the output and disable the QUIET functions just say
# VERBOSE=true make
ifeq ($(VERBOSE),true)
	V=@
endif

# Silent functions which ouputs colors and happy things :)
ifndef V
QUIET_CC = @printf '    %b %b\n' $(CCCOLOR)CC$(ENDCOLOR) $(SRCCOLOR)$@$(ENDCOLOR);
QUIET_LINK = @printf '    %b %b\n' $(LINKCOLOR)LINK$(ENDCOLOR) $(BINCOLOR)$@$(ENDCOLOR);
QUIET_MAKE = @printf '    %b %b\n' $(MAKECOLOR)---$(ENDCOLOR) $(BINCOLOR)$@$(ENDCOLOR);
endif


all: test


# ---------------------------------------------------------------------
# Compile the library itself
# ---------------------------------------------------------------------

CHINOOKPACK_OBJ := $(patsubst src/%,src/obj/%,$(patsubst %.c, %.o,$(wildcard src/*.c)))
INCLUDES=-Isrc


-include $(wildcard src/obj/*.d)

src/obj:
	mkdir src/obj

src/obj/%.o: src/%.c src/obj
	$(QUIET_CC) $(CC) $(CFLAGS) $(DEBUG) -MMD -c $< -o $@  $(INCLUDES)

# ---------------------------------------------------------------------
# Compile the library and the tests
# ---------------------------------------------------------------------

TEST_OBJ := $(patsubst test/%,test/obj/%,$(patsubst %.c, %.o,$(wildcard test/*.c)))

-include $(wildcard test/obj/*.d)

test/obj:
	@mkdir test/obj

test/obj/%.o: test/%.c test/obj
	$(QUIET_CC) $(CC) $(CFLAGS) $(DEBUG) -MMD -c $< -o $@  $(INCLUDES)

# ---------------------------------------------------------------------
# TEST RUNNER
# ---------------------------------------------------------------------

TEST_BIN := test-chinookpack
# Task that runs the tests
test: $(TEST_BIN)
	$(QUIET_MAKE) ./$(TEST_BIN)

# Task that compiles the test runner
$(TEST_BIN): $(CHINOOKPACK_OBJ) $(TEST_OBJ)
	@echo $(MAKECOLOR)MAKE$(ENDCOLOR) $(BINCOLOR)test-chinookpack$(ENDCOLOR)
	$(QUIET_LINK) $(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_OBJ) $(INCLUDES) $(FUJIN_LIB_DEPS)


clean:
	rm -rf src/obj test/obj $(TEST_BIN)


.PHONY: test
