CC=gcc
FLAGS=-std=c17 -ggdb 
OUT=hprint

all: hprint

hprint: main.c
	${CC} main.c ${FLAGS} -o ${OUT} 

clean: 
	rm -f hprint

install:
	cp ./hprint /usr/local/bin/