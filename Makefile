CC = gcc
CFLAGS = -Wall -g -lm

SRC = Chaine.c MainChaine.c SVGwriter.c Reseau.c
OBJS = ${SRC:.c=.o}
SRC_RES= Reseau.c ReconstitueReseau.c Chaine.c SVGwriter.c Hachage.c ArbreQuat.c
OBJS_RES = ${SRC_RES:.c=.o}
SRC_B= Reseau.c MainComp.c Chaine.c SVGwriter.c Hachage.c ArbreQuat.c
OBJS_B = ${SRC_B:.c=.o}

all: cha res comp

res: ${OBJS_RES}
	${CC} -o res ${CFLAGS} ${OBJS_RES}

cha: ${OBJS}
	${CC} -o cha ${CFLAGS} ${OBJS}

comp: ${OBJS_B}
	${CC} -o comp ${CFLAGS} ${OBJS_B}


.c.o:
	${CC} -c ${CFLAGS} $<


clean:
	rm -f *.o  *.html res cha
