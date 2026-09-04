CC        ?= gcc
RAYLIB     = ../raylib/src
RAYLIB_WEB = ../raylib-web/src

SRCDIR = src
INCDIR = include

SRCS = $(SRCDIR)/main.c $(SRCDIR)/vec3.c $(SRCDIR)/ray.c $(SRCDIR)/sphere.c
HDRS = $(INCDIR)/vec3.h $(INCDIR)/ray.h $(INCDIR)/sphere.h

CFLAGS  = -std=c11 -Wall -Wextra -Werror -I$(RAYLIB) -I$(INCDIR)
LDFLAGS = -L$(RAYLIB) -Wl,-rpath,'$$ORIGIN/$(RAYLIB)' -lraylib -lm
SAN     = -fsanitize=address,undefined -fno-omit-frame-pointer

raytracer: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -g -O0 $(SAN) $(SRCS) $(LDFLAGS) -o $@

release: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -O2 $(SRCS) $(LDFLAGS) -o raytracer

run: raytracer
	ASAN_OPTIONS=detect_leaks=0 ./raytracer

clean:
	rm -f raytracer

.PHONY: release run clean