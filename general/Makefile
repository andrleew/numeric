CXX = clang++
FLAGS = -std=c++17 -pedantic
OPTIMIZE = -O2 -march='native'
LD = $(CXX) $(FLAGS) $(OPTIMIZE) $(WARNINGS)
OBJ=-o ../objects/$(@F)
CC = $(LD) $< -c $(OBJ)

all: ../objects/mod.o ../objects/opts.o ../objects/reader.o ../objects/writer.o ../objects/logger.o

../objects/mod.o: mod.cpp mod.h
	$(CC)
../objects/opts.o: opts.cpp opts.h general.h
	$(CC)
../objects/reader.o: reader.cpp reader.h
	$(CC)
../objects/writer.o: writer.cpp writer.h
	$(CC)
../objects/logger.o: logger.cpp logger.h
	$(CC)
