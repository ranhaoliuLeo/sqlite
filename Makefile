build: main.o memstore.o input.o execute.o
	gcc -o sql main.o memstore.o input.o execute.o

main.o: main.c global.h
	gcc -c main.c

memstore.o: memstore.c memstore.h
	gcc -c memstore.c

input.o: input.c input.h
	gcc -c input.c

execute.o: execute.c execute.h
	gcc -c execute.c

clean:
	rm -f main.o memstore.o input.o execute.o 

uninstall:
	rm -f sql 