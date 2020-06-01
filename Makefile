CXX = clang++
FLAGS = -std=c++17 -pedantic -ltbb
OPTIMIZE = -O2 -march='native'
LD = $(CXX) $(FLAGS) $(OPTIMIZE) $(WARNINGS)
CC = $(LD) -c

DEPS=objects/lab1.1.o \
	 objects/lab1.2.o \
	 objects/lab1.3.o \
	 objects/lab1.4.o \
	 objects/lab1.5.o \
	 objects/main.o \
	 objects/mod.o \
	 objects/opts.o \
	 objects/reader.o \
	 objects/writer.o \
	 objects/logger.o

lab: $(DEPS)
	$(LD) objects/*.o -o $@

objects/lab1.1.o: 1.1/*
	$(MAKE) -C 1.1/
objects/lab1.2.o: 1.2/*
	$(MAKE) -C 1.2/
objects/lab1.3.o: 1.3/*
	$(MAKE) -C 1.3/
objects/lab1.4.o: 1.4/*
	$(MAKE) -C 1.4/
objects/lab1.5.o: 1.5/*
	$(MAKE) -C 1.5
objects/main.o: numeric/*
	$(MAKE) -C numeric/
objects/mod.o objects/opts.o objects/reader.o objects/writer.o objects/logger.o: general/*
	$(MAKE) -C general/

clean:
	rm objects/*.o lab
