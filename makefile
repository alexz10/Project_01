all: main.o parser.o extra_commands.o
	gcc -o prgrm main.o parser.o extra_commands.o

main.o: main.c parser.h extra_commands.h
	gcc -c main.c

parser.o: parser.c parser.h
	gcc -c parser.c

extra_commands.o: extra_commands.c extra_commands.h
	gcc -c extra_commands.c

.PHONY: run clean
run: prgrm
	./prgrm
clean:
	rm *.o
