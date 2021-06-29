CFLAGS= -I. -g3 -O3 -Wall -Wextra -Wno-unused-variable -D _GNU_SOURCE
LIBS=
SRC=$(wildcard *.c)
HDR=$(wildcard *.h)
OBJS=$(patsubst %.c, obj/%.o, $(SRC))

.PHONY: all clean

all: clean obj monyhar-greasy format

format:
	$(foreach n, $(SRC), clang-format -style=google -i $(n); )
	$(foreach n, $(HDR), clang-format -style=google -i $(n); )

monyhar-greasy: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	$(RM) -r obj monyhar-greasy

obj/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

obj:
	mkdir -p obj

