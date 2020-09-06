output: main.o fileio.o helpers.o linked_list.o menu.o array_list.o shared.o
	gcc main.o fileio.o helpers.o linked_list.o menu.o array_list.o shared.o -o list_comp

main.o: main.c
	gcc -ansi -Wall -pedantic -g -c main.c

array_list.o: array_list.c array_list.h
	gcc -ansi -Wall -pedantic -g -c array_list.c

fileio.o: fileio.c fileio.h
	gcc -ansi -Wall -pedantic -g -c fileio.c

helpers.o: helpers.c helpers.h
	gcc -ansi -Wall -pedantic -g -c helpers.c

menu.o: menu.c menu.h
	gcc -ansi -Wall -pedantic -g -c menu.c

linkedlist.o: linked_list.c linked_list.h
	gcc -ansi -Wall -pedantic -g -c linkedlist.c

shared.o: shared.c shared.h
	gcc -ansi -Wall -pedantic -g -c shared.c

clean:
	rm *.o list_comp
