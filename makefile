all: work18.o
	gcc -o work18 work18.o
work18.o: work18.c
	gcc -c work18.c
run:
	./work18
clean:
	rm *.o
	rm work18
