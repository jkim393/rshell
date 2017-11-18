CC = g++
CC_FLAGS = -Wall -Werror -ansi -pedantic
all:main cmdExec cmdAnd cmdOr cmdSemi
		mkdir -p bin
			$(CC) $(CCFLAGS) main.o cmdExec.o cmdAnd.o cmdOr.o cmdSemi.o -o ./bin/rshell
main:
		$(CC) $(CCFLAGS) -c ./src/main.cpp
cmdExec:
		$(CC) $(CCFLAGS) -c ./src/cmdExec.cpp
cmdAnd:
		$(CC) $(CCFLAGS) -c ./src/cmdAnd.cpp 
cmdOr:
		$(CC) $(CCFLAGS) -c ./src/cmdOr.cpp 
cmdSemi:
		$(CC) $(CCFLAGS) -c ./src/cmdSemi.cpp 
clean:
		rm -r *.o
