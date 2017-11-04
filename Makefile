CC = g++
CC_FLAGS = -Wall -Werror -ansi -pedantic
all:main cmdExec
		mkdir -p bin
			$(CC) $(CCFLAGS) main.o cmdExec.o -o ./bin/rshell
main:
		$(CC) $(CCFLAGS) -c ./src/main.cpp
cmdExec:
		$(CC) $(CCFLAGS) -c ./src/cmdExec.cpp
clean:
		rm -r *.o
