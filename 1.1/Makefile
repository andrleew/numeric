CXX = clang++
FLAGS = -std=c++17 -pedantic
OPTIMIZE = -O2 -march='native'
LD = $(CXX) $(FLAGS) $(OPTIMIZE) $(WARNINGS)
CC = $(LD) -c $< -o ../objects/$@


LAB_HEADERS = ../numeric/matrix.h \
		      ../numeric/vector.h \
			  ../general/opts.h \
			  ../general/solution.h \
			  ../general/run_solution.h \
			  ../general/reader.h \
			  ../general/writer.h
			  
../objects/lab1.1.o: lab1.1.cpp lab1.1.h $(LAB_HEADERS)
	$(CC) -I ../general -I ../numeric