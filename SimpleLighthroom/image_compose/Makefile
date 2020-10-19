CC	= g++

OIIO_INC = -I/
OIIO_LIB = -lOpenImageIO
OPENGL_LIB = -lglut -lGL -lGLU

LDFLAGS = $(OPENGL_LIB) $(OIIO_LIB)
CFLAGS = -g $(OIIO_INC)


compose : compose.o
	${CC} -o compose compose.o ${LDFLAGS}

compose.o : compose.cpp
	${CC} -c ${CFLAGS} compose.cpp

all : compose


clean:
	rm -f core.* *.o compose
