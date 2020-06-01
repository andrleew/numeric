CXX = clang++
FLAGS = -std=c++17 -pedantic
OPTIMIZE = -O2 -march='native'
INC = -I ../general -I ../numeric
LD = $(CXX) $(FLAGS) $(OPTIMIZE) $(WARNINGS) $(INC)
CC = $(LD) -c $< -o ../objects/$(@F) -Wall -Wextra


LAB_HEADERS =	../numeric/matrix.h \
		../numeric/vector.h \
		../general/opts.h \
		../general/solution.h \
		../general/run_solution.h \
		../general/reader.h \
		../general/writer.h \
		../general/logger.h
	
../objects/lab1.4.o: lab1.4.cpp lab1.4.h $(LAB_HEADERS)
	$(CC)
