CC := gcc
DEV ?=
TARGET := main
CFLAGS := -g -std=c17
IFLAGS := -Iinclude/ -Ideps/xxHash/

ifdef DEV
	CFLAGS := $(CFLAGS) -fsanitize=address
endif

_obj_files ?= list.o map.o math.o cstrings.o tuple.o
obj_files ?= $(patsubst %,build/%, $(_obj_files))

_src_files ?= list.c map.c math.c cstrings.c tuple.c
src_files ?= $(patsubst %,src/%, $(_src_files))

_test_files ?= list_test.c map_test.c cstrings_test.c tuple_test.c
test_exes ?= $(patsubst %.c,build/tests/%.out, $(_test_files))
test_files ?= $(patsubst %,tests/%, $(_test_files))
test_objs ?= $(patsubst %.c,build/tests/%.o, $(_test_files))

deps_objs ?= build/deps/xxhash.o
test_deps ?= build/deps/unity.o

test_results ?= $(patsubst %.c,build/tests/results/%.txt, $(_test_files))

.PHONY: default
default: deps run

.PHONY: all
all: default

.PHONY: clean
clean:
	-find build/ -type f \( -name '*.o' -or -name '*.out' -or -name '*.txt' \) -exec rm -f {} \;
	rm -rf docs/*

.PHONY: clean-all
clean-all: clean clean-deps

.PHONY: clean-deps
clean-deps:
	-rm -rf deps/*

.PHONY: clean-docker
clean-docker:
	@docker stop crumb-docs-nginx && docker rm crumb-docs-nginx || true

.PHONY: deps
deps: $(deps_objs)

.PHONY: dist
dist: deps build/crumb.o

.PHONY: docs
docs:
	doxygen

.PHONY: run
run: build/$(TARGET).out
	./$<

.PHONY: serve-docs
serve-docs: clean-docker docs
	docker run --name crumb-docs-nginx -v $(shell pwd)/docs/html:/usr/share/nginx/html:ro -p 8080:80 nginx || true

.PHONY: test-deps
test-deps: $(test_deps)

deps/Unity:
	[ -d $@ ] || git clone git@github.com:ThrowTheSwitch/Unity.git $@

deps/xxHash:
	[ -d $@ ] || git clone git@github.com:Cyan4973/xxHash.git $@

build/%.o:: src/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

build/$(TARGET).o:: bin/$(TARGET).c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

build/crumb.o: $(obj_files) $(deps_objs)
	ld -relocatable $^ -o $@

build/deps/unity.o:: deps/Unity
	$(CC) $(CFLAGS) $(IFLAGS) -c deps/Unity/src/*.c -o $@ -Ideps/Unity/src

build/deps/xxhash.o: deps/xxHash
	$(CC) $(CFLAGS) $(IFLAGS) -c deps/xxHash/xxhash.c -o $@

build/tests/%.o: tests/%.c deps
	$(CC) $(CFLAGS) $(IFLAGS) -Ideps/Unity/src -c $< -o $@

build/$(TARGET).out: build/$(TARGET).o $(obj_files) $(deps_objs)
	$(CC) $(CFLAGS) $(IFLAGS) $^ -Wall -o $@

build/tests/%.out: build/tests/%.o $(obj_files) deps test-deps
	$(CC) $(CFLAGS) $< $(obj_files) $(deps_objs) $(test_deps) -o $@

.PHONY: build/tests/results/%.txt
build/tests/results/%.txt: build/tests/%.out
	@./$< > $@ || true

.PHONY: test
test: deps $(test_results) build/ build/deps/ build/tests/results/
	@find build/tests/results -type f -name '*.txt' -print | xargs -I {} bash -c 'cat {} | ./tests/bin/test_report.py'

.PHONY: %_test
%_test: build/tests/%_test.out
	@./$< | ./tests/bin/test_report.py

.PRECIOUS: build/%.o
.PRECIOUS: build/%.out
.PRECIOUS: build/tests/%.o
.PRECIOUS: build/tests/%.out
.PRECIOUS: build/tests/results/%.txt
