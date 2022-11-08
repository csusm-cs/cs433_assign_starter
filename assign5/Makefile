###################################
# OS COURSE - CS 433 example
# 
###################################
CC = g++			# use g++ for compiling c++ code or gcc for c code
CFLAGS = -g -Wall -std=c++11		# compilation flags: -g for debugging. Change to -O or -O2 for optimized code.
LIB = -lm			# linked libraries	
LDFLAGS = -L.			# link flags
PROG = prog5			# target executable (output)
SRCS = main.cpp pagetable.cpp replacement.cpp fifo_replacement.cpp lifo_replacement.cpp lru_replacement.cpp     # .c or .cpp source files.
OBJ = $(SRCS:.cpp=.o) 	# object files for the target. 
DEPS = $(SRCS:.cpp=.d)

all : $(PROG)

$(PROG): $(OBJ) 
	$(CC) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

# cleanup
clean:
	rm -f *.o $(PROG) 

# DO NOT DELETE
