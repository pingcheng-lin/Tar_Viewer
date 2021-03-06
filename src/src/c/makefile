all: dep
	gcc main.c stack.o -o output1
	gcc main2.c stack.o -o output2
dep:
	gcc -c stack.c -o stack.o
clean: 
	rm -f *.o output1 output2
