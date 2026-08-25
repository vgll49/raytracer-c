CC      ?= gcc
RAYLIB   = ../raylib/src
RAYLIB_WEB = ../raylib-web/src


CFLAGS   = -std=c11 -Wall -Wextra -Werror -I$(RAYLIB)
LDFLAGS  = -L$(RAYLIB) -Wl,-rpath,'$$ORIGIN/$(RAYLIB)' -lraylib -lm
SAN      = -fsanitize=address,undefined -fno-omit-frame-pointer

raytracer: main.c
	$(CC) $(CFLAGS) -g -O0 $(SAN) $< $(LDFLAGS) -o $@

release: main.c
	$(CC) $(CFLAGS) -O2 $< $(LDFLAGS) -o raytracer

run: raytracer
	ASAN_OPTIONS=detect_leaks=0 ./raytracer

clean:
	rm -f raytracer

.PHONY: release run clean 