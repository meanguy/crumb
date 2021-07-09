CC := gcc
TARGET := main
CFLAGS := -g -std=c17 -fsanitize=address
IFLAGS := -Iinclude/ -Ideps/xxHash/

_obj_files ?= list.o math.o strings.o
obj_files ?= $(patsubst %,build/%, $(_obj_files))

_src_files ?= list.c math.c strings.c
src_files ?= $(patsubst %,src/%, $(_src_files))

_test_files ?= list_test.c strings_test.c
test_files ?= $(patsubst %,tests/%, $(_test_files))

test_results ?= $(patsubst %.c,build/tests/results/%.txt, $(_test_files))

.PHONY: default all clean

default: deps build/$(TARGET).out

all: default

clean:
	-find build/ -type f \( -name '*.o' -or -name '*.out' -or -name '*.txt' \) -print -exec rm -f {} \;

clean-all: clean clean-deps

clean-deps:
	-rm -rf deps/*

deps: deps/Unity deps/xxHash

deps/Unity:
	git clone git@github.com:ThrowTheSwitch/Unity.git $@

deps/xxHash:
	git clone git@github.com:Cyan4973/xxHash.git $@

build/%.o:: src/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

build/$(TARGET).o:: bin/$(TARGET).c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

build/deps/%.o:: deps/Unity/src/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ -Ideps/Unity/src

build/tests/%.o:: tests/%.c deps
	$(CC) $(CFLAGS) $(IFLAGS) -Ideps/Unity/src -c $< -o $@

build/$(TARGET).out: $(obj_files) build/main.o
	$(CC) $(CFLAGS) $(IFLAGS) $(obj_files) build/main.o -Wall -o $@

build/tests/%_test.out: build/deps/unity.o build/tests/%_test.o $(obj_files)
	$(CC) $(CFLAGS) -o $@ $^

build/tests/results/%.txt: build/tests/%.out
	-./$< > $@ 2>&1 || true

test: deps $(test_results) build/ build/deps/ build/tests/results/ 
	@cat build/tests/results/*.txt | ./tests/bin/test_report.py

.PRECIOUS: build/%.d
.PRECIOUS: build/%.o
.PRECIOUS: build/tests/%.o
.PRECIOUS: build/tests/%.out
.PRECIOUS: build/tests/results/%.txt
