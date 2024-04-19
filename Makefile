CC = gcc
CFLAGS = -Wall -g -lm

SRC = Chaine.c MainChaine.c SVGwriter.c Reseau.c
OBJS = ${SRC:.c=.o}
SRC_RES= Reseau.c ReconstitueReseau.c Chaine.c SVGwriter.c
OBJS_RES = ${SRC_RES:.c=.o}


all: cha res

res: ${OBJS_RES}
	${CC} -o res ${CFLAGS} ${OBJS_RES}

cha: ${OBJS}
	${CC} -o cha ${CFLAGS} ${OBJS}


.c.o:
	${CC} -c ${CFLAGS} $<


clean:
	rm -f *.o res cha
