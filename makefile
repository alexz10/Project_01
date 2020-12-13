all: main.o parser.o extra_commands.o homebase.o
	gcc -o prgrm main.o parser.o extra_commands.o homebase.o

main.o: main.c parser.h homebase.h
	gcc -c main.c

parser.o: parser.c parser.h
	gcc -c parser.c

extra_commands.o: extra_commands.c extra_commands.h
	gcc -c extra_commands.c

homebase.o: homebase.c homebase.h parser.h
	gcc -c homebase.c

.PHONY: run clean
run: prgrm
	./prgrm
clean:
	rm *.o
