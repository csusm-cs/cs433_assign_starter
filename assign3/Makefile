###################################
# OS COURSE - CS 433 example
# 
###################################
CC = g++			# use g++ for compiling c++ code or gcc for c code
CFLAGS = -g -Wall -std=c++11 # compilation flags: -g for debugging. Change to -O or -O2 for optimized code.
LIB = -lm			# linked libraries	
LDFLAGS = -L.			# link flags
PROG = sjf fcfs rr priority		# target executables (output)
SRCS = scheduler_fcfs.cpp scheduler_rr.cpp scheduler_sjf.cpp scheduler_priority.cpp scheduler_priority_rr.cpp \
	driver_fcfs.cpp driver_rr.cpp driver_sjf.cpp driver_priority.cpp driver_priority_rr.cpp # .c or .cpp source files.
OBJ = $(SRCS:.cpp=.o) 	# object files for the target. Add more to this and next lines if there are more than one source files.
DEPS = $(SRCS:.cpp=.d)

all : $(PROG) 

fcfs: scheduler_fcfs.o driver_fcfs.o
	$(CC) -o fcfs scheduler_fcfs.o driver_fcfs.o $(LDFLAGS) $(LIB)

rr: scheduler_rr.o driver_rr.o
	$(CC) -o rr scheduler_rr.o driver_rr.o $(LDFLAGS) $(LIB)

sjf: scheduler_sjf.o driver_sjf.o
	$(CC) -o sjf scheduler_sjf.o driver_sjf.o  $(LDFLAGS) $(LIB)

priority: scheduler_priority.o driver_priority.o
	$(CC) -o priority scheduler_priority.o driver_priority.o $(LDFLAGS) $(LIB)

priority_rr: scheduler_priority_rr.o driver_priority_rr.o
	$(CC) -o priority_rr scheduler_priority_rr.o driver_priority_rr.o $(LDFLAGS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@
	
# cleanup
clean:
	rm -f *.o $(PROG) 

# DO NOT DELETE
