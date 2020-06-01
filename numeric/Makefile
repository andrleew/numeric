CXX = clang++
FLAGS = -std=c++17 -pedantic
OPTIMIZE = -O2 -march='native'
LD = $(CXX) $(FLAGS) $(OPTIMIZE) $(WARNINGS)
OBJ=-o ../objects/$(@F)
INC = -I ../general/ -I ../1.1/ -I ../1.2/ -I ../1.3/ -I ../1.4/ -I ../1.5/
CC = $(LD) $< -c $(OBJ) $(INC)


../objects/main.o: main.cpp ../*/*.h
	$(CC)