CXX=clang++
WARNINGS=-Wall -pedantic -Werror -Wextra
OPTIMIZE=-O2 -march=native
COMPILE=$(CXX) $(WARNINGS) $(OPTIMIZE) -c
LINK=$(CXX) $(WARNINGS) $(OPTIMIZE)

matr: Main.o LU.o Matrix.o Vector.o
	$(LINK) Matrix.o LU.o Main.o Vector.o -o matr

Main.o: Main.cpp LU.h Matrix.h Vector.h
	$(COMPILE) Main.cpp
LU.o: LU.cpp LU.h Matrix.h
	$(COMPILE) LU.cpp
Matrix.o: Matrix.cpp Matrix.h Vector.h
	$(COMPILE) Matrix.cpp
Vector.o: Vector.cpp Vector.h
	$(COMPILE) Vector.cpp

clean:
	rm matr *.o