CC	= g++
CFLAGS = -g
LFLAGS = -g

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -lOpenImageIO -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -L /usr/lib64/ -lglut -lGL -lGLU -lOpenImageIO -lm
  endif
endif

PROJECT	= adjust

OBJS = main.o colorwindow.o fileio.o imageprocess.o manager.o myimage.o

${PROJECT}: ${OBJS}
	${CC} ${LFLAGS} -o ${PROJECT} ${OBJS} ${LDFLAGS}

%.o: %.cpp
	${CC} -c ${CFLAGS} *.cpp

clean:
	rm -f core.* *.o *~ ${PROJECT}
