monyhar-lite: main.c
	${CC} -std=c89 -Wall -Wextra $< -o $@

all: monyhar-lite

clean:
	rm -f monyhar-lite
