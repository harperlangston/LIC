PROGRAM = ./main

INCLUDES = 

LIBS = -lstdc++

CPPFLAGS = ${INCLUDES} ${LIBS}

CPPFILES = Pixel.cpp \
	   Velocity.cpp \
	   Cmdlineopts.cpp \
	   LIC.cpp

OFILES = ${CPPFILES:.cpp=.o}

.c++.o :
	gcc -o $@ -c $<

.cpp.o :
	gcc -o $@ -c $<

default: $(PROGRAM)

$(PROGRAM) : $(OFILES)
	cc $(OFILES) $(CPPFLAGS) -o $@ main.cpp

rand: Random.o Cmdlineopts.o
	cc Random.o Cmdlineopts.o $(CPPFLAGS) -o $@ rand.cpp

clean :
	rm -f *.o *~ main

#DO NOT DELETE
