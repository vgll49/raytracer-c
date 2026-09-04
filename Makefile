CC      ?= gcc
RAYLIB   = ../raylib/src
RAYLIB_WEB = ../raylib-web/src


CFLAGS   = -std=c11 -Wall -Wextra -Werror -I$(RAYLIB)
LDFLAGS  = -L$(RAYLIB) -Wl,-rpath,'$$ORIGIN/$(RAYLIB)' -lraylib -lm
SAN      = -fsanitize=address,undefined -fno-omit-frame-pointer

raytracer: main.c vec3.c vec3.h ray.c ray.h sphere.c sphere.h
	$(CC) $(CFLAGS) -g -O0 $(SAN) main.c vec3.c ray.c sphere.c $(LDFLAGS) -o $@

release: main.c vec3.c vec3.h ray.c ray.h sphere.c sphere.h
	$(CC) $(CFLAGS) -O2 main.c vec3.c ray.c sphere.c $(LDFLAGS) -o raytracer

run: raytracer
	ASAN_OPTIONS=detect_leaks=0 ./raytracer

clean:
	rm -f raytracer

.PHONY: release run clean 