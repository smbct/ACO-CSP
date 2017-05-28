.PHONY: clean
CC= g++
CFLAGS= -std=c++11 -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra -O3

OBJECTS_FILES= src/main.o src/Instance.o src/Solution.o src/AntColony.o src/MaxMin.o src/ACS.o src/Utils.o


aco_csp: $(OBJECTS_FILES)
	$(CC) $(CFLAGS) $(OBJECTS_FILES) -o aco_csp

# object files compilation
%.o: %.cpp %.h
	$(CC) $(CFLAGS) $< -c -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	@rm -rf src/*.o aco_csp
